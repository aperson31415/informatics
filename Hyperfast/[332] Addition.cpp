// ~5 attempts

#include <sys/syscall.h>
 
// Global table - needs to be static to ensure it's in the data segment
static const char digits[] = 
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";
 
extern "C" __attribute__((naked)) int main() {
    __asm__ volatile (
        "sub $128, %%rsp\n\t"        // Stack buffer
 
        // --- SYS_READ ---
        "xor %%rax, %%rax\n\t"       // syscall 0
        "xor %%rdi, %%rdi\n\t"       // fd 0
        "mov %%rsp, %%rsi\n\t"       // buf
        "mov $128, %%rdx\n\t"        // len
        "syscall\n\t"
        "test %%rax, %%rax\n\t"
        "jle .L_done\n\t"
 
        "mov %%rsp, %%r8\n\t"        // current p
        "lea (%%rsp, %%rax), %%r13\n\t" // end p
        "xor %%r9, %%r9\n\t"         // num A
        "xor %%r10, %%r10\n\t"        // num B
 
        // --- PARSE A ---
        ".L_skip_a:\n\t"
        "cmp %%r13, %%r8\n\t"
        "jae .L_add\n\t"
        "movzbl (%%r8), %%eax\n\t"
        "inc %%r8\n\t"
        "sub $48, %%al\n\t"
        "cmp $9, %%al\n\t"
        "ja .L_skip_a\n\t"
        ".L_read_a:\n\t"
        "imul $10, %%r9\n\t"
        "add %%rax, %%r9\n\t"
        "movzbl (%%r8), %%eax\n\t"
        "inc %%r8\n\t"
        "sub $48, %%al\n\t"
        "cmp $9, %%al\n\t"
        "jbe .L_read_a\n\t"
 
        // --- PARSE B ---
        ".L_skip_b:\n\t"
        "cmp %%r13, %%r8\n\t"
        "jae .L_add\n\t"
        "movzbl (%%r8), %%eax\n\t"
        "inc %%r8\n\t"
        "sub $48, %%al\n\t"
        "cmp $9, %%al\n\t"
        "ja .L_skip_b\n\t"
        ".L_read_b:\n\t"
        "imul $10, %%r10\n\t"
        "add %%rax, %%r10\n\t"
        "movzbl (%%r8), %%eax\n\t"
        "inc %%r8\n\t"
        "sub $48, %%al\n\t"
        "cmp $9, %%al\n\t"
        "jbe .L_read_b\n\t"
 
        ".L_add:\n\t"
        "add %%r10, %%r9\n\t"         // r9 = sum
 
        // --- STRINGIFY ---
        "mov %%rsp, %%rdi\n\t"
        "add $127, %%rdi\n\t"
        "movb $10, (%%rdi)\n\t"      // \n
        "mov %%r9, %%rax\n\t"
        "mov $10, %%rcx\n\t"
 
        ".L_digit_loop:\n\t"
        "xor %%rdx, %%rdx\n\t"
        "div %%rcx\n\t"
        "add $48, %%dl\n\t"
        "dec %%rdi\n\t"
        "mov %%dl, (%%rdi)\n\t"
        "test %%rax, %%rax\n\t"
        "jnz .L_digit_loop\n\t"
 
        // --- SYS_WRITE ---
        "mov %%rdi, %%rsi\n\t"
        "mov %%rsp, %%rdx\n\t"
        "add $128, %%rdx\n\t"
        "sub %%rdi, %%rdx\n\t"       // length
        "mov $1, %%rax\n\t"          // sys_write
        "mov $1, %%rdi\n\t"          // fd 1
        "syscall\n\t"
 
        ".L_done:\n\t"
        "add $128, %%rsp\n\t"
        "mov $60, %%rax\n\t"         // sys_exit
        "xor %%rdi, %%rdi\n\t"
        "syscall\n\t"
        :
        : 
        : "rax", "rcx", "rdx", "rdi", "rsi", "r8", "r9", "r10", "r13", "memory"
    );
}