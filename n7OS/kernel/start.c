#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>

extern void handler_IT();

void kernel_start(void)
{
    // on ne doit jamais sortir de kernel_start
    printf("\f");
    init_irq_entry(50,(uint32_t) handler_IT);
    sti();
    while (1) {
        __asm__ ("int $50"::);
        // cette fonction arrete le processeur
        hlt();
    }
}
