#!/bin/bash

# Compile the C files
gcc -o tester test.c get_next_line.c get_next_line_utils.c

# Define test cases
test_cases=(
  "test_file1.txt"
  "test_file2.txt"
  "test_file3.txt"
)

# Run the tests
for test_file in "tests/${test_cases[@]}"; do
  echo "Running test case: $test_file"
  
  # Run the program with the test file and capture the output
  output=$(./tester "$test_file")
  
  # Print the output
  echo "$output"
done

# Clean up compiled files
rm tester