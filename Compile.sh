#!/bin/bash
clear
# GPTComp.sh — Fully async + multithreaded incremental build with millisecond timing

set -e
shopt -s nullglob  # Avoid literal *.cxx when no matches

# --- Compiler settings ---
CXX=g++
CXXFLAGS="-std=c++23 -O3"

# --- Directories ---
SRC_DIR="."
MODULES_DIR="./Modules"
BUILD_DIR="./build"
mkdir -p "$BUILD_DIR"

# --- Source files ---
MAIN_FILE="$SRC_DIR/controller.cxx"
MODULE_FILES=($MODULES_DIR/*.cxx)
MAIN_OBJ="$BUILD_DIR/controller.o"
OUTPUT="main"
OBJECTS=()

# --- CPU threads for internal compiler parallelism ---
if command -v nproc &>/dev/null; then
    THREADS=$(nproc)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    THREADS=$(sysctl -n hw.ncpu)
else
    THREADS=4
fi

# --- High precision start time (in milliseconds) ---
start_time=$(($(date +%s%N)/1000000))

echo
echo " Silly wittle GPT GCC/C++ compiler"
echo "------------------------------------"
echo
echo " Compiler: $CXX"
echo " Comping with: $CXXFLAGS"
echo " Async & $THREADS-threads"
echo
echo "------------------------------------"
echo

# --- Compile modules asynchronously ---
for SRC in "${MODULE_FILES[@]}"; do
    OBJ="$BUILD_DIR/$(basename "${SRC%.cxx}.o")"
    OBJECTS+=("$OBJ")

    if [[ ! -f "$OBJ" || "$SRC" -nt "$OBJ" ]]; then
        echo "  [Async] $SRC"
        (
            $CXX $CXXFLAGS -pthread -pipe -ftree-parallelize-loops=$THREADS -c "$SRC" -o "$OBJ"
        ) &
    TMPCOUNT=1
    fi
done

if [[ $TMPCOUNT == 1 ]] ; then
    echo
    echo "------------------------------------"
    echo
fi

# --- Wait for all background compilation jobs to finish ---
wait

# --- Compile main file (synchronously) ---
if [[ ! -f "$MAIN_OBJ" || "$MAIN_FILE" -nt "$MAIN_OBJ" ]]; then
    echo " Building: $MAIN_FILE"
    $CXX $CXXFLAGS -pthread -pipe -ftree-parallelize-loops=$THREADS -c "$MAIN_FILE" -o "$MAIN_OBJ"
fi
OBJECTS+=("$MAIN_OBJ")

# --- Determine if relink is needed ---
RELINK=false
if [[ ! -f "$OUTPUT" ]]; then
    RELINK=true
else
    for OBJ in "${OBJECTS[@]}"; do
        if [[ "$OBJ" -nt "$OUTPUT" ]]; then
            RELINK=true
            break
        fi
    done
fi

# --- Link step ---
if $RELINK; then
    echo " Linking"
    $CXX "${OBJECTS[@]}" -pthread -o "$OUTPUT"
    echo " Build Finished"
else
    echo " No changes detected"
fi

# --- End timer ---
end_time=$(($(date +%s%N)/1000000))
elapsed=$((end_time - start_time))

echo
echo "------------------------------------"
echo

echo " Total build time: ${elapsed} ms"
du -sh build | awk '{print " Build dir size: " $1}'
    FILESIZE_BYTES=$(stat -c%s "$OUTPUT")
    FILESIZE_MB=$(echo "scale=2; $FILESIZE_BYTES/1024/1024" | bc)
    # If less than 1 MB, show in KB instead
    if (( $(echo "$FILESIZE_MB < 1" | bc -l) )); then
        FILESIZE_KB=$(echo "scale=2; $FILESIZE_BYTES/1024" | bc)
        echo " File size: ${FILESIZE_KB} KB"
    else
        echo " File size: ${FILESIZE_MB} MB"
    fi

echo ""
echo "------------------------------------"
echo ""
