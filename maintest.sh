#!/bin/bash
BUILD_DIR="build"
PROGRAM_PATH="./build/myrobot"
DIR="./test/examples"
VALID_FILE_PATH="$DIR/house.txt"

# Function to run a specific test
run_test() {
    local input_file=$1
    local output_file=$2
    local expected_file=$3
    $PROGRAM_PATH "$input_file" 0 > /dev/null 
    # Check if the output matches the expected output
    if cmp "$output_file" "$expected_file" &&  [ $? -eq 0 ]; then
        echo -e "\e[32mTest $input_file passed.\e[0m"
    else
        echo -e "\e[31mTest $input_file failed.\e[0m"
    fi
}
check_failed() {
    local input_file=$1
    $PROGRAM_PATH "$input_file" 0 > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "\e[32mTest $input_file passed. we got 1 \e[0m"
    else
        echo -e "\e[31mTest $input_file failed. we should have failed \e[0m"
    fi
}
run_invalid_args_test() {
    local input_file=$1
    echo "Running: $input_file"
    $PROGRAM_PATH $input_file 2>&1 >/dev/null

    # Check if the program exited with status 1
    if [ $? -eq 1 ]; then
        echo -e "\e[32mTest $input_file passed. we got 1 \e[0m"
    else
        echo -e "\e[31mTest $input_file failed. we should have failed \e[0m"
    fi
    echo
}

run_invalid_args_test_rand() {
    local input_args=$1
    echo "Running: $input_args"
    stderr_output=$($PROGRAM_PATH $input_args 2>&1 >/dev/null)
    echo $stderr_output
    if [ $? -eq 0 ] && [[ $stderr_output == *"Selecting Randomness=TRUE as default"* ]]; then
        echo -e "\e[32mTest $input_file passed.\e[0m"
    else
        echo -e "\e[31mTest $input_file failed.\e[0m"
    fi
}

test_no_memory_leaks() {
    local input_args=$1

    # Run valgrind with the appropriate options
    valgrind --leak-check=full \
              --log-file=valgrind.log \
              --error-exitcode=100 \
             $PROGRAM_PATH $input_args 0 > /dev/null 2>&1

    valgrind_exit=$?
    if [ $valgrind_exit -ne 100 ]; then
        echo -e "\e[32mValgrind passed. No memory leaks detected in $input_args\e[0m"
    else
        echo -e "\e[31mValgrind detected errors or leaks in $input_args\e[0m"
        cat valgrind.log  # Print valgrind output for debugging
    fi
}


# Run CMake to generate Makefiles
cmake -B "$BUILD_DIR" -S .
cmake --build build

# <<< Using test GT to validate ete scenario >>> <<< Find >>>

dir_gt="$DIR/gt"
dir_failtests="$DIR/failtests"
input_files=()
for expected_file in "$dir_gt"/output_* ; do
    base_filename=$(basename "$expected_file")
    input_file="$DIR/${base_filename#output_}"
    input_files+=("$input_file")
    output_file="$DIR/${base_filename}"
    echo "Running test $input_file"
    run_test "$input_file" "$output_file" "$expected_file"
done

for file in "$dir_failtests"/*; do
    echo "Running Fail test $file"
    check_failed "$file"
done

incorrect_inputs=(
    ""  # No arguments
    "invalid_path"  # Only one argument, not a valid file path
    "\"\""  # Only one argument, empty string
)

for input in "${incorrect_inputs[@]}"; do
    run_invalid_args_test "$input"
done


rand_incorrect_inputs=(
    "$VALID_FILE_PATH 2"  # Valid file path, second argument not 0 or 1
    "$VALID_FILE_PATH \"\""  # Valid file path, second argument empty string
    "$VALID_FILE_PATH -1"  # Valid file path, second argument negative number
    "$VALID_FILE_PATH abc"  # Valid file path, second argument non-integer
    "$VALID_FILE_PATH @"  # Valid file path, second argument special character
)

for input in "${rand_incorrect_inputs[@]}"; do
    run_invalid_args_test_rand "$input"
done
all_runs=(
    "${rand_incorrect_inputs[@]}"
    "${incorrect_inputs[@]}"
    "${input_files[@]}"
)
for input in "${all_runs[@]}"; do
    test_no_memory_leaks "$input"
done