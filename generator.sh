#!/bin/bash

make all

# Generate a random number within the specified range
export ARG=$(shuf -i 0-700 -n 500)
echo $ARG > tmp
# Execute the push_swap and checker program with the generated number as an argument
echo "$(./push_swap $ARG | ./checker_linux $ARG) <- checker_linux"

# Print the numbers of operations
echo "number of operations: $(./push_swap $ARG | wc -l)"
