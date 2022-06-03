#include <inttypes.h>

#ifndef __PROCESS_H__
#define __PROCESS_H__

#define MAXPROCESS 255
#define STACK_SIZE 1024
#define REG_NUMBER 5
/**
 * PROCESS STATE
 * 
 */
typedef enum {
    CHOSEN, ACTIVE_READY, READY_SUSPENDED,
    BLOCKED_READY, BLOCKED_SUSPENDED
    } PROCESS_STATE;

typedef enum {
    HIGH,NORMAL,LOW
    } PROCESS_PRIORITY; 

typedef uint32_t PROCESS_ID;

typedef struct {
    uint32_t registers[REG_NUMBER];
} PROCESS_CONTEXT;


typedef struct PROCESS_STACK {
    PROCESS_CONTEXT processContext;
    uint32_t * stackTop;
    uint32_t executionStack[STACK_SIZE];
} PROCESS_STACK;

typedef struct {
    char* programName;
    PROCESS_ID processID;
    PROCESS_STATE state;
    PROCESS_PRIORITY priority;
    PROCESS_STACK stack;
    PROCESS_CONTEXT executionContext;
} PROCESS;

typedef void* (*fnptr)();

PROCESS_ID pidTable[MAXPROCESS];
PROCESS processTable[MAXPROCESS];
PROCESS_STACK processStackTable[MAXPROCESS];
uint32_t processNumber;

void addPID(PROCESS_ID newPID);
void addProcess(PROCESS newProcess);
void schedule();
PROCESS_ID createPID();
void createProcess(fnptr processProgram,char* processName,PROCESS_PRIORITY priority);


#endif