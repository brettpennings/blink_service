#ifndef Serial_H
#define Serial_H

#include "ProcessTasks.h"
#include "Blinker.h"

void Serial_Init(void);
void Serial_Service(Blinker_t * blinker);

#endif // Serial_H