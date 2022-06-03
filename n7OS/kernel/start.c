#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/time.h>
#include <n7OS/irq.h>
#include <unistd.h>
#include <n7OS/sys.h>


void kernel_start(void)
{
    // on ne doit jamais sortir de kernel_start
    init_syscall();
    sti();
    printf("\f");
    initTimer();
    while (1) {
        //__asm__ ("int $50"::);
        // cette fonction arrete le processeur
        hlt();
    }
}
