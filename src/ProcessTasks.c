#include "ProcessTasks.h"
#include "Serial.h"

void ProcessTasks_Init(ProcessTasks_t * process_tasks)
{
	Blinker_Init(&process_tasks->blinker);
}

void ProcessTasks(ProcessTasks_t * process_tasks)
{
	Blinker_Service(&process_tasks->blinker);
	Serial_Service(&process_tasks->blinker);
}

