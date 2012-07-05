
#include "HardSerial.h"
#include "Serial.h"
#include "Command.h"

char command [16];

void Serial_Init(void) {
	hs_init();
	hs_start(9600);
	Command_Init(command);
}

void Serial_Service(Blinker_t * blinker) {
	int16_t c = hs_read();
	
	if (c != -1)
	{
		// if line-feed or carriage-return
		if ( (c == 0x0A) || (c == 0x0D) || (c == 'Q') )
		{
			// process the current expression
			if (Command_Parse(command, blinker) == 1)
			{
				// successful command
				hs_write('O');
				hs_write('K');
			}
			else
			{
				// failed command
				hs_write('N');
				hs_write('O');
			}
			// reset command
			Command_Init(command);
		}
		else
		{
			// add to the current expression
			Command_Append(command, c);
		}
	}
}

