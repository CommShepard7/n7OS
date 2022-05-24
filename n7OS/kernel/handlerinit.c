#include "handlertable.h"
#include <stdio.h>

void handlerIT20() {
    printf("Interruption 20");
}

void handlerIT49() {
    printf("Interruption 49");
}

void handlerIT50() {
    printf("Interruption 50");
}

void handlerInit(int itNum) {
    addHandler(itNum,handlerIT20);
}