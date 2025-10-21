#!/usr/bin/env bash

clear
echo

set -euo pipefail

# ========================================
# CONFIGURATION
# ========================================

BUILD_MODE="release"
if [[ "${1:-}" == "--debug" ]]; then
    BUILD_MODE="debug"
fi

USE_CCACHE=true
CXX=${CXX:-g++}
CXX_CMD=($CXX)
if $USE_CCACHE && command -v ccache >/dev/null 2>&1; then
    CXX_CMD=(ccache "$CXX")
fi

CORES=$(nproc)
MAX_JOBS=$((CORES * 2))

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

MODULES_DIR="./Modules"
MAIN_FILE="controller.cxx"
OUTPUT_EXE="main"

RAM_BASE="/dev/shm/fullbuild"
mkdir -p "$RAM_BASE"

# ========================================
# RAM CHECK
# ========================================

total_ram_kb=$(grep MemTotal /proc/meminfo | awk '{print $2}')
free_ram_kb=$(grep MemAvailable /proc/meminfo | awk '{print $2}')
free_ram_mb=$((free_ram_kb / 1024))
MIN_RAM_MB=2048

if (( free_ram_mb < MIN_RAM_MB )); then
    echo "Not enough free RAM (${free_ram_mb} MB). Minimum required: ${MIN_RAM_MB} MB."
    exit 1
fi

# ========================================
# PREPARE RAM BUILD ENVIRONMENT
# ========================================

echo "Copying source tree to RAM..."
rsync -a --delete --exclude=".git" --exclude="*.o" --exclude="main" ./ "$RAM_BASE/" >/dev/null
cd "$RAM_BASE"

BUILD_DIR="$RAM_BASE/.build"
LINK_TMP_DIR="$RAM_BASE/linktmp"
mkdir -p "$BUILD_DIR" "$LINK_TMP_DIR"

echo "Compiler: ${CXX_CMD[*]}"
echo "Parallel jobs: $MAX_JOBS"
echo "Mode: $BUILD_MODE"
echo "Running fully in RAM: $RAM_BASE"
echo
echo "--------------------------------------"
echo

# ========================================
# COMPILER FLAGS
# ========================================

if [[ "$BUILD_MODE" == "debug" ]]; then
    CXXFLAGS="-std=c++23 -O0 -g -Wall -Wextra"
else
    CXXFLAGS="-std=c++23 -O3 -march=native -flto=$MAX_JOBS -funroll-loops -fomit-frame-pointer -pipe -DNDEBUG -Wall -Wextra"
fi

MODULE_FLAGS="-fmodules-ts"
DEPFLAGS="-MMD -MP"

# ========================================
# FUNCTIONS
# ========================================

elapsed_time() { awk '{print $2 - $1}'; }

deps_newer() {
    local obj="$1" dep="$2"
    [[ ! -f "$dep" ]] && return 0
    while IFS= read -r f; do
        [[ "$f" -nt "$obj" ]] && return 0
    done < <(awk '/:/{sub(/:/,""); next} {print}' "$dep")
    return 1
}

# ========================================
# MODULE DISCOVERY
# ========================================

mapfile -t MODULES < <(find "$MODULES_DIR" -type f -name '*.cxx' | sort)
MODULE_COUNT=${#MODULES[@]}
echo "Found $MODULE_COUNT module(s)."

declare -A MODULE_TIMES=()
updated_modules=()

for src in "${MODULES[@]}"; do
    base=$(basename "$src" .cxx)
    obj="$BUILD_DIR/$base.o"
    dep="$BUILD_DIR/$base.d"

    needs_rebuild=false
    if [[ ! -f "$obj" || "$src" -nt "$obj" || ! -f "$dep" ]]; then
        needs_rebuild=true
    elif deps_newer "$obj" "$dep"; then
        needs_rebuild=true
    fi

    if $needs_rebuild; then
        updated_modules+=("$src")
    fi
done

if [[ ${#updated_modules[@]} -eq 0 ]]; then
    echo "All modules up to date."
else
    echo "===> Compiling ${#updated_modules[@]} updated module(s)"
    echo
fi

# ========================================
# MODULE COMPILATION
# ========================================

COMPILE_PIDS=()
TMP_TIMES="$RAM_BASE/.times"
rm -f "$TMP_TIMES"

for src in "${updated_modules[@]}"; do
    base=$(basename "$src" .cxx)
    obj="$BUILD_DIR/$base.o"
    dep="$BUILD_DIR/$base.d"

    (
        start=$(date +%s.%N)
        echo "[BUILD] Compiling $base.cxx"
        "${CXX_CMD[@]}" $CXXFLAGS $MODULE_FLAGS $DEPFLAGS -c "$src" -o "$obj" -MF "$dep" >/dev/null 2>&1
        end=$(date +%s.%N)
        t=$(echo "$start $end" | elapsed_time)
        printf "%s %.3f\n" "$base" "$t" >>"$TMP_TIMES"
        ##echo "[DONE]  $base.cxx (${t}s)"
    ) &
    COMPILE_PIDS+=($!)

    # Limit concurrency
    while (( $(jobs -rp | wc -l) >= MAX_JOBS )); do
        sleep 0.05
    done
done

wait "${COMPILE_PIDS[@]}" || true

if [[ -f "$TMP_TIMES" ]]; then
    while read -r mod time; do
        MODULE_TIMES["$mod"]="$time"
    done <"$TMP_TIMES"
    rm -f "$TMP_TIMES"
fi

# ========================================
# MAIN CONTROLLER
# ========================================

main_obj="$BUILD_DIR/controller.o"
main_dep="$BUILD_DIR/controller.d"

echo
echo "--------------------------------------"
echo

echo "===> Compiling main controller..."
main_start=$(date +%s.%N)
"${CXX_CMD[@]}" $CXXFLAGS $MODULE_FLAGS $DEPFLAGS -c "$MAIN_FILE" -o "$main_obj" -MF "$main_dep"
main_end=$(date +%s.%N)
main_compile_time=$(echo "$main_start $main_end" | elapsed_time)
echo "  controller.cxx             $(printf '%.3fs' "$main_compile_time")"

# ========================================
# MODULE TIME SUMMARY
# ========================================

if [[ ${#MODULE_TIMES[@]} -gt 0 ]]; then
    echo
    echo "===> Module compile times:"
    for mod in "${!MODULE_TIMES[@]}"; do
        printf "  %-25s %8.3fs\n" "$mod.cxx" "${MODULE_TIMES[$mod]}"
    done | sort
fi

# ========================================
# LINKING
# ========================================

##echo "===> Linking all objects (RAM-based)..."
link_start=$(date +%s.%N)
TMPDIR="$LINK_TMP_DIR" "${CXX_CMD[@]}" $CXXFLAGS "$BUILD_DIR"/*.o -o "$BUILD_DIR/$OUTPUT_EXE"
link_end=$(date +%s.%N)
link_time=$(echo "$link_start $link_end" | elapsed_time)
total_time=$(echo "$main_start $link_end" | elapsed_time)

# ========================================
# STATS (RAM ONLY)
# ========================================

exe_size=$(stat -c%s "$BUILD_DIR/$OUTPUT_EXE")
if (( exe_size >= 1048576 )); then
    exe_human="$(awk "BEGIN {printf \"%.2f MB\", $exe_size/1048576}")"
else
    exe_human="$(awk "BEGIN {printf \"%.2f KB\", $exe_size/1024}")"
fi

peak_cpu=$(ps -eo %cpu --sort=-%cpu | head -2 | tail -1)
peak_mem_kb=$(ps -eo rss --sort=-rss | head -2 | tail -1)
peak_mem_mb=$(awk "BEGIN {printf \"%.2f\", $peak_mem_kb/1024}")

echo
echo "--------------------------------------"
echo
echo "===> Build complete (in RAM)"
echo "Compile time:   $(printf '%.3fs' "$main_compile_time")"
echo "Link time:      $(printf '%.3fs' "$link_time")"
echo "Total time:     $(printf '%.3fs' "$total_time")"
echo "Peak CPU usage: ${peak_cpu}%"
echo "Peak RAM usage: ${peak_mem_mb} MB"
echo "Executable size: ${exe_human}"
echo

# ========================================
# SYNC BACK TO DISK AFTER SUCCESS
# ========================================

echo "===> Syncing to disk"
rsync -a "$BUILD_DIR/$OUTPUT_EXE" "$OLDPWD/" >/dev/null
rsync -a "$BUILD_DIR"/*.o "$OLDPWD/.build/" >/dev/null 2>/dev/null || true
rsync -a "$BUILD_DIR"/*.d "$OLDPWD/.build/" >/dev/null 2>/dev/null || true
cd "$OLDPWD"
echo

# ========================================
# CLEAN UP RAMDISK
# ========================================

echo "Cleaning up RAM build directory..."
rm -rf "$RAM_BASE"
echo "RAM disk cleared."