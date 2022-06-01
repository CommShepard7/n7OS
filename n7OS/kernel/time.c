#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>
#include <n7OS/console.h>
#include <n7OS/time.h>

Time currentTime = {.hours = 0, .minutes = 0, .seconds = 0};

extern void handlerTime();
int clockCounter = 0;

void initTimer() {
    int clockFrequency = 0x1234BD/0x3E8;
    init_irq_entry(0x20, (uint32_t) handlerTime);
    outb(0x34,0x43);
    outb(clockFrequency&0xFF,0x40);
    outb(clockFrequency>>8,0x40);
    outb(inb(0x21)&0xfe, 0x21);
    consolePutTime(&currentTime);
}

void updateTime() {
    clockCounter++;
    if(clockCounter == 1000) {
        clockCounter = 0;
        currentTime.seconds++;
        consolePutTime(&currentTime);
        if(currentTime.seconds == 60) {
            currentTime.seconds = 0;
            currentTime.minutes++;
            printf("\f");
            if(currentTime.minutes == 60) {
                currentTime.minutes = 0;
                currentTime.hours++;
            }
        }
    }
}

void resetTime() {
    currentTime.seconds = 0;
    currentTime.minutes = 0;
    currentTime.hours = 0;
}

Time * getTime() {
    return &currentTime;
}

void timeUpdate() {
    outb(0x20, 0x20);
    outb(inb(0x21 )|1, 0x21);
    updateTime();
    outb(inb(0x21)&0xfe, 0x21);
}


