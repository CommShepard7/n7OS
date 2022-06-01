#include <n7OS/console.h>
#include <inttypes.h>
#include <n7OS/cpu.h>
#include <n7OS/time.h>
#include <stdio.h>

#define MAX_WIDTH 79
#define MAX_LENGTH 24

typedef struct {
    uint16_t * scr_tab;
    int line;
    int column;
} Console;

typedef struct {
    uint8_t bl;
    uint8_t background;
    uint8_t color;
} Visual;

Console console = {.scr_tab = (uint16_t *) 0xB8000, .line = 1, .column = 0};
Visual visual = {.bl = 1, .background = 0, .color = 15};


void lineShift() {
    for(int line = 0; line <= MAX_LENGTH; line++) {
        for(int column = 0; column <= MAX_WIDTH; column++) {
            int posUpper = 80*(line+1) + column;
            int posLower = 80*line + column;
            console.scr_tab[posLower] = console.scr_tab[posUpper];
        }
    }
}

void lineClear(int lineNumber) {
    for(int k = 0; k <= MAX_WIDTH; k++) {
        int pos = (80*lineNumber + k);
        console.scr_tab[pos]= ((visual.bl*256 + (visual.background<<4) + visual.color) << 8) + '\0';
    }
}

char * timeCharArray(int t) {
    char * timeVal = "00";
    if(t < 10) {
        timeVal[0] = t + '0';
        timeVal[1] = 0 + '0';
    } else {
        timeVal[0] = t - (t/10)*10 + '0';
        timeVal[1] = t/10 + '0';
    }
    return timeVal;
}

void consolePutTime(Time* t) {
    lineClear(0);
    char* s = timeCharArray(t->seconds);
    console.scr_tab[77] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + s[1];
    console.scr_tab[78] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + s[0];
    console.scr_tab[79] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + 's';   
    char* m = timeCharArray(t->minutes);
    console.scr_tab[74] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + m[1];
    console.scr_tab[75] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + m[0];
    console.scr_tab[76] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + 'm';
    char* h = timeCharArray(t->hours);
    console.scr_tab[71] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + h[1];
    console.scr_tab[72] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + h[0];
    console.scr_tab[73] = ((visual.bl*256 + (visual.background<<4) + 10) << 8) + 'h';     
}

void charUpdatePos() {
    if (console.column < MAX_WIDTH) {
        console.column++;
    } else {
        console.column = 0;
        if(console.line < MAX_LENGTH) {
            console.line ++;
        } else {
            lineShift();
        }
    }
}

void bpUpdatePos() {
    if(console.column > 0) {
        console.column--;
    } else {
        if(console.line > 0) {
            console.line--;
            console.column = MAX_WIDTH;
        }
    }
}

void htUpdatePos() {
    char tabSpace[8];
    for(int k = 0; k <= 8; k++) {
        tabSpace[k] = ' ';
    }
    console_putbytes(tabSpace,8);
}

void lfUpdatePos() {
    if(console.line < MAX_LENGTH) {
        console.line++;
    } else {
        lineShift();
    }
    console.column = 0;
}

void ffUpdatePos() {
    console.line = 1;
    console.column = 0;
    char emptyStr[(MAX_LENGTH)*(MAX_WIDTH+1)];
    for(int k; k < (MAX_LENGTH)*(MAX_WIDTH+1); k++) {
        emptyStr[k] = '\0';
    }
    console_putbytes(emptyStr,(MAX_LENGTH)*(MAX_WIDTH+1));
    console.line = 1;
    console.column = 0;
}

void crUpdatePos() {
    console.column = 0;
}

void updateCursor() {
    uint16_t pos = (80*console.line + console.column);
    outb(0x0F,0x3D4);
	outb((uint8_t) pos & 0xFF,0x3D5);
	outb(0x0E,0x3D4);
	outb( (uint8_t) (pos >> 8) & 0xFF,0x3D5);
}

void setVisual(uint8_t bl, uint8_t color, uint8_t background) {
    visual.bl = bl;
    visual.color = color;
    visual.background = background;
}

void resetVisual() {
    visual.bl = 1;
    visual.color = 15;
    visual.background = 0;
}

void console_putchar(char c) {
    if ((c == 0) || (c > 31 && c < 127)) {
        int pos = (80*console.line + console.column);
        console.scr_tab[pos]= ((visual.bl*256 + (visual.background<<4) + visual.color) << 8) + c;
        charUpdatePos();
    } else {
        switch (c) {
            case '\b' : 
               bpUpdatePos();
            break;

            case '\t' : 
                htUpdatePos();
            break;

            case '\n' : 
                lfUpdatePos();
            break;

            case '\f' : 
                ffUpdatePos();
            break;

            case '\r' : 
                crUpdatePos();
            break;
        }
    }
    updateCursor();
}

void console_putbytes(const char *s, int len) {
    int strLen = 0;
    while(strLen < len) {
        console_putchar(s[strLen++]);
    }
}
