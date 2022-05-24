#ifndef __HANDLERTABLE_H__
#define __HANDLERTABLE_H__
#include "n7OS/processor_structs.h"

typedef void (*hPtr)();

hPtr handlerPtr[IDT_ENTRIES];

void addHandler(int itNumber, hPtr handler);

#endif