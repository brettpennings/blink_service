#ifndef Command_H
#define Command_H

#include "Blinker.h"

/* Initialize command */
void Command_Init(char * command);

/* Determine how to handle command */
uint8_t Command_Parse(char * command, Blinker_t * blinker);

/* Add a character to the end of command */
void Command_Append(char * command, char c);

#endif // Command_H