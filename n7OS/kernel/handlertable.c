#include "handlertable.h"

void addHandler(int itNumber, hPtr handler) {
    handlerPtr[itNumber] = handler;
}