#!/usr/bin/env bash

clear
echo
echo "--------------------------------------"
echo

set -euo pipefail

# ==========================
# Build Configuration
# ==========================

# Default to release mode unless --debug is specified
BUILD_MODE="release"
if [[ "${1:-}" == "--debug" ]]; then
    BUILD_MODE="debug"
fi

# Detect CPU cores and double for concurrency
CORES=$(nproc)
MAX_JOBS=$((CORES * 2))

# Compiler setup
USE_CCACHE=true
CXX=${CXX:-g++}
CXX_CMD=($CXX)
if $USE_CCACHE && command -v ccache >/dev/null 2>&1; then
    CXX_CMD=(ccache "$CXX")
fi

# ==========================
# Flags by build mode
# ==========================

if [[ "$BUILD_MODE" == "debug" ]]; then
    echo "       Build mode: DEBUG"
    echo
    echo "--------------------------------------"
    echo
    CXXFLAGS="-std=c++23 -Ofast -g -DNDEBUG -Wall -Wextra"
else
    echo "       Build mode: RELEASE"
    echo
    echo "--------------------------------------"
    echo
    CXXFLAGS="-std=c++23 -O3 -march=native -flto=$MAX_JOBS -funroll-loops -fomit-frame-pointer -pipe"
fi

MODULE_FLAGS="-fmodules-ts"
DEPFLAG_BASE="-MMD -MP"

# ==========================
# Paths
# ==========================

BUILD_DIR=".build"
MODULES_DIR="./Modules"
MAIN_FILE="controller.cxx"
OUTPUT_EXE="main"

mkdir -p "$BUILD_DIR"

# ==========================
# Utility Functions
# ==========================

elapsed_time() { awk '{print $2 - $1}'; }

deps_newer() {
    local obj="$1" dep="$2"
    [[ ! -f "$dep" ]] && return 0
    while IFS= read -r f; do
        [[ "$f" -nt "$obj" ]] && return 0
    done < <(awk '/:/{sub(/:/,""); next} {print}' "$dep")
    return 1
}

# ==========================
# Start Build
# ==========================

echo "Compiler: ${CXX_CMD[*]}"
echo "Using ccache: $USE_CCACHE"
echo "Parallel jobs: $MAX_JOBS"
echo

mapfile -t MODULES < <(find "$MODULES_DIR" -type f -name '*.cxx' | sort)
MODULE_COUNT=${#MODULES[@]}

echo "--------------------------------------"
echo
echo "Found $MODULE_COUNT module(s)."

updated_modules=()

# Determine which modules need recompilation
for src in "${MODULES[@]}"; do
    base=$(basename "$src" .cxx)
    obj="$BUILD_DIR/$base.o"
    dep="$BUILD_DIR/$base.d"

    if [[ (! -f "$obj") || ("$src" -nt "$obj") || (! -f "$dep") || $(deps_newer "$obj" "$dep") ]]; then
        updated_modules+=("$src")
    fi
done

if [[ ${#updated_modules[@]} -eq 0 ]]; then
    echo "All modules up to date."
else
    echo "===> Compiling with $MAX_JOBS threads"
fi

echo

# Always declare the associative array — fixes unbound var issues
declare -A MODULE_TIMES=()
COMPILE_PIDS=()

TMPCOUNT=0

for src in "${updated_modules[@]}"; do
    base=$(basename "$src" .cxx)
    obj="$BUILD_DIR/$base.o"
    dep="$BUILD_DIR/$base.d"

    (
        start=$(date +%s.%N)
        echo "[BUILD] Compiling $base.cxx"
        "${CXX_CMD[@]}" $CXXFLAGS $MODULE_FLAGS $DEPFLAG_BASE -c "$src" -o "$obj" -MF "$dep" >/dev/null 2>&1
        end=$(date +%s.%N)
        t=$(echo "$start $end" | elapsed_time)
        echo "$base $t" >>"$BUILD_DIR/.module_times.tmp"
        ##echo "[DONE]  $base.cxx (${t}s)"
    ) &
    COMPILE_PIDS+=($!)

    # Limit concurrent jobs
    while (( $(jobs -rp | wc -l) >= MAX_JOBS )); do
        sleep 0.1
    done

    TMPCOUNT=1
done

wait "${COMPILE_PIDS[@]}" || true

# Rebuild timing map safely
if [[ -f "$BUILD_DIR/.module_times.tmp" ]]; then
    while read -r name time; do
        MODULE_TIMES["$name"]="$time"
    done <"$BUILD_DIR/.module_times.tmp"
    rm -f "$BUILD_DIR/.module_times.tmp"
fi

# ==========================
# Main Compilation
# ==========================


main_obj="$BUILD_DIR/controller.o"
main_dep="$BUILD_DIR/controller.d"

if [[ $TMPCOUNT = 1 ]] ; then
echo
fi

echo "--------------------------------------"
echo
if [[ ${#MODULE_TIMES[@]} -gt 0 ]]; then
    echo "===> Module compile times:"
    for mod in "${!MODULE_TIMES[@]}"; do
        printf "  %-25s %8.3fs\n" "$mod.cxx" "${MODULE_TIMES[$mod]}"
    done | sort
    echo
fi

echo "===> Compiling main controller"
main_start=$(date +%s.%N)
"${CXX_CMD[@]}" $CXXFLAGS $MODULE_FLAGS $DEPFLAG_BASE -c "$MAIN_FILE" -o "$main_obj" -MF "$main_dep"
main_end=$(date +%s.%N)
main_compile_time=$(echo "$main_start $main_end" | elapsed_time)

# ==========================
# Module Compile Times Summary
# ==========================

echo "  controller.cxx             $(printf '%.3fs' "$main_compile_time")"
echo

# ==========================
# Linking Phase
# ==========================

##echo "===> Linking all objects..."
link_start=$(date +%s.%N)
"${CXX_CMD[@]}" $CXXFLAGS "$BUILD_DIR"/*.o -o "$OUTPUT_EXE"
link_end=$(date +%s.%N)
link_time=$(echo "$link_start $link_end" | elapsed_time)
total_time=$(echo "$main_start $link_end" | elapsed_time)

# ==========================
# Final Stats
# ==========================

# Get executable size (in bytes)
exe_size=$(stat -c%s "$OUTPUT_EXE")

# Convert to human readable form
if (( exe_size >= 1048576 )); then
    exe_human="$(awk "BEGIN {printf \"%.2f MB\", $exe_size/1048576}")"
else
    exe_human="$(awk "BEGIN {printf \"%.2f KB\", $exe_size/1024}")"
fi

peak_cpu=$(ps -eo %cpu --sort=-%cpu | head -2 | tail -1)
peak_mem=$(ps -eo %mem --sort=-%mem | head -2 | tail -1)

echo "--------------------------------------"
echo
echo "===> Build complete"
echo "Compile time:   $(printf '%.3fs' "$main_compile_time")"
echo "Link time:      $(printf '%.3fs' "$link_time")"
echo "Total time:     $(printf '%.3fs' "$total_time")"
echo "Peak CPU usage: ${peak_cpu}%"
echo "Peak RAM usage: ${peak_mem}%"
echo "Executable size: ${exe_human}"

echo
echo "--------------------------------------"
echo
