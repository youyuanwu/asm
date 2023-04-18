#include "asm.h"
#include <functional>

void saveAndRun(std::function<void(void)> f){

int i = 99;

// save registers
asm (
    // "push $0\n\t"
    "push %r15\n\t"
    "push %r14\n\t"
    "push %r13\n\t"
    "push %r12\n\t"
    "push %r11\n\t"
    "push %r10\n\t"
    "push %r9\n\t"
    "push %r8\n\t"
    "push %rbp\n\t"
    "push %rdi\n\t"
    "push %rsi\n\t"
    "push %rdx\n\t"
    "push %rcx\n\t"
    "push %rbx\n\t"
    "push %rax\n\t"
    // rsp is ignored 
);


// do work
    f();

// restore registers
asm (
    "pop %rax\n\t"
    "pop %rbx\n\t"
    "pop %rcx\n\t"
    "pop %rdx\n\t"
    "pop %rsi\n\t"
    "pop %rdi\n\t"
    "pop %rbp\n\t"
    "pop %r8\n\t"
    "pop %r9\n\t"
    "pop %r10\n\t"
    "pop %r11\n\t"
    "pop %r12\n\t"
    "pop %r13\n\t"
    "pop %r14\n\t"
    "pop %r15\n\t"
);

}



