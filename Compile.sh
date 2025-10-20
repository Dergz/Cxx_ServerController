#!/bin/bash

## Just a compiling script that uses specific compiler flags & a fancy output

clear

echo ""
echo "Silly wittle compiler script"
echo "----------------------------------"
echo ""

# Set compiler shterfs
CXX="g++"        # G++ is the compiler
STD=c++23               # C++ standard, should work with c++17 as well?
OPT_FLAGS="-O3 -flto"   # Compiler flags
OUTPUT=main             # Name of the executable file

# Source files
SRC="controller.cxx"

echo "Compiling with: $CXX & $STD"

echo "Compiling with flags: ($OPT_FLAGS)"

echo ""
echo "----------------------------------"
echo ""

start_time=$(date +%s%N)

TIME_LOG=$(mktemp)

# Compile and link in one step, measure resource usage if possible
if command -v /usr/bin/time &> /dev/null; then
    /usr/bin/time -v $CXX -std=$STD $OPT_FLAGS "$SRC" -o "$OUTPUT" 2> "$TIME_LOG"
    status=$?
else
    $CXX -std=$STD $OPT_FLAGS "$SRC" -o "$OUTPUT"
    status=$?
fi

end_time=$(date +%s%N)
duration_ns=$((end_time - start_time))
duration_s=$(awk "BEGIN {printf \"%.3f\", $duration_ns/1000000000}")

if [ $status -eq 0 ]; then
    echo "Build completed"
    echo ""
    echo "----------------------------------"
    echo ""
    echo "Compile and link time: ${duration_s}s"
else
    echo "Build failed."
    if [ -f "$TIME_LOG" ]; then
        cat "$TIME_LOG"
        rm "$TIME_LOG"
    fi
    exit $status
fi

if [ -f "$TIME_LOG" ]; then
    user_cpu=$(grep "User time (seconds):" "$TIME_LOG" | awk '{print $4}')
    sys_cpu=$(grep "System time (seconds):" "$TIME_LOG" | awk '{print $4}')
    max_mem_kb=$(grep "Maximum resident set size (kbytes):" "$TIME_LOG" | awk '{print $6}')
    max_mem_mb=$(awk "BEGIN {printf \"%.1f\", $max_mem_kb/1024}")

    echo "User CPU time:         ${user_cpu}s"
    echo "System CPU time:       ${sys_cpu}s"
    echo "Max memory usage:      ${max_mem_mb} MB"

    rm "$TIME_LOG"

    echo ""
    echo "----------------------------------"
    echo ""
fi