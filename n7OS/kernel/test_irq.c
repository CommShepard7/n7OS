#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>

extern void handler_IT();

void handler_en_C() {
    printf("Interruption 500");
}


