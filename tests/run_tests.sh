#!/usr/bin/env bash
# Builds the program and checks its output against every expected result.
# Usage: ./tests/run_tests.sh   (run from the repository root)

cd "$(dirname "$0")/.." || exit 1

g++ -std=c++17 src/*.cpp -o library || exit 1

passed=0
failed=0

for input in tests/inputs/*.txt; do
    name=$(basename "$input" .txt)
    for algorithm in FCFS PRIORITY; do
        expected="tests/expected/${name}_${algorithm}.out"
        if diff -u "$expected" <(./library "$input" "$algorithm"); then
            passed=$((passed + 1))
        else
            echo "FAIL: $name $algorithm"
            failed=$((failed + 1))
        fi
    done
done

echo "Passed: $passed  Failed: $failed"
[ "$failed" -eq 0 ]
