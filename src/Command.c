
#include "Command.h"

#include <string.h>

void Command_Init(char * command) {
	memset(command, 0, sizeof(command));
}

uint8_t Command_Parse(char * command, Blinker_t * blinker) {
	char c;
	unsigned int period = 0;
	unsigned int i = 6;
	const char prefix[7] = "blink ";
	
	// make sure first six characters are "blink " else fail
	if (memcmp(prefix, command, 6) != 0)
	{
		return 0;
	}
	
	// for the remaining chars
	while ((c = command[i]) != 0)
	{
		// if not a number (in ascii), return fail
		if (c < 0x30)
		{
			return 0;
		}
		else if (c > 0x39)
		{
			return 0;
		}
		else
		{
			period *= 10;       // base-10 shift
			period += c - 0x30; // add ascii-converted number to period
		}
		i++;
	}
	
	// update blink interval to be half of the new period
	Blinker_UpdateInterval(blinker, period/2);
	
	return 1;
}

void Command_Append(char * command, char c) {
	int len = strlen(command);
	command[len] = c;
	command[len+1] = '\0';
}

