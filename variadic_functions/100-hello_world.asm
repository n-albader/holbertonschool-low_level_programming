section .data
  hello: db "hello, World", 10
  len: equ $ - hello

section .text
  global main

min:
  ;start
  mov rax, 1
  mov rdi, 1
  mov rsi, hello
  mov rdx, len

  ;end
  mov rax, 60
  mov rdi,0
  syscall
