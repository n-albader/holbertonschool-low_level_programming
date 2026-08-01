section .data
  hello db "Hello, World", 10
  len equ $ - hello

section .text
  global main

main:
  ;start
  mov rax, 1
  mov rdi, 1
  mov rsi, hello
  mov rdx, len
  syscall

  ;end
  mov rax, 60
  mov rdi,0
  syscall
