# Simple Calculator

## Compile Command

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 calculator.c -o calculator

## Run 

./calculator

## Supported Operations

- Display the menu
- Quit using option 0
- Validate menu choices
- Addition
- Subtraction
- Multiplication
- Division
- Recovery from invalid (non-numeric) input

## Numeric Behavior

- The program reads integer input using 'scanf'
- Addition, subtraction, and multiplication use integers
- Division returns a decimal result
- Invalid menu choices are rejected
- Non-numeric input is detected and the user is prompted again

## Known Limitations

- Only integer input is supported
- Division by zero prints an error message
