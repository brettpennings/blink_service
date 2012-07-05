#include <string.h>

#include "unity.h"
#include "Initialize.h"
#include "mock_ProcessTasks.h"
#include "mock_Serial.h"

ProcessTasks_t process_tasks;

void setUp(void) { memset(&process_tasks, 0, sizeof(process_tasks)); }
void tearDown(void) { }

void test_Initialize(void)
{
  ProcessTasks_Init_Expect(&process_tasks);
  Serial_Init_Expect();

  Initialize(&process_tasks);
}
