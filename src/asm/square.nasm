global _square

section .text
_square:
    mov rax, rdi
    mul rax
    ret
