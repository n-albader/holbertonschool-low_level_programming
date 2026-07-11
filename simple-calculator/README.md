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

## Numeric Behavior

- The program reads integer input using 'scanf'
- Addition, subtraction, and multiplication use integers
- Division returns a decimal result

## Known Limitations

- Only integer input is supported
- Non-numeric input is not handled
- Division by zero prints an error message
