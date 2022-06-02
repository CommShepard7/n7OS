#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/time.h>
#include <n7OS/irq.h>


void kernel_start(void)
{
    // on ne doit jamais sortir de kernel_start
    printf("\f");
    initTimer();
    sti();
    while (1) {
        //__asm__ ("int $50"::);

        // cette fonction arrete le processeur
        hlt();
    }
}
