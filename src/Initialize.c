#include "Initialize.h"
#include "Serial.h"

void Initialize(ProcessTasks_t * process_tasks)
{
	ProcessTasks_Init(process_tasks);
	Serial_Init();
}
