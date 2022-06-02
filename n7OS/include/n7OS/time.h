#ifndef __TIME_H__
#define __TIME_H__

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

void initTimer();
void updateTime();
void resetTime();
Time * getTime();

#endif