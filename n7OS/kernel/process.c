#include <n7OS/process.h>


void addPID(PROCESS_ID pid) {
    pidTable[processNumber] = pid;
}

void addStack(PROCESS_STACK stack) {
    processStackTable[processNumber] = stack;
}

PROCESS_ID createPID() {
   if(processNumber != MAXPROCESS) {
       processNumber++;
       addPID(processNumber);
       return processNumber;
   } 
}

void createProcess(fnptr processProgram,char* processName,PROCESS_PRIORITY priority) {
    PROCESS_ID pid = createPID();
    PROCESS newProcess;
    PROCESS_STACK newStack;
    PROCESS_CONTEXT newContext;
    newStack.stackTop = STACK_SIZE-5;
    newContext.registers[1] = &newStack.stackTop;
    newStack.executionStack[*newStack.stackTop] = newContext.registers;
    newProcess.programName = processName;
    newProcess.priority = priority;
    newProcess.processID = pid;
    newProcess.stack = newStack;
    newProcess.executionContext = newContext;

}