#ifndef TIMER_H
#define TIMER_H
void initRTC(void);
unsigned long millis();
unsigned long seconds();
void delayMillis(unsigned int interval);
#endif
