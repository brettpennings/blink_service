#include "unity.h"
#include "Serial.h"
#include "mock_HardSerial.h"
#include "mock_Blinker.h"
#include "mock_Command.h"

#include <inttypes.h>
#include <string.h>

extern char command [16];

void setUp(void) {}
void tearDown(void) {}

void test_Serial_Init(void)
{
	hs_init_Expect();
	hs_start_Expect(9600);
	Command_Init_Expect(command);
	
	Serial_Init();
}

void test_Serial_Service_should_do_nothing_if_the_buffer_is_empty(void)
{
	Blinker_t blinker;
	
	hs_read_ExpectAndReturn(-1);
	
	Serial_Service(&blinker);
}

void test_Serial_Service_should_append_the_latest_character(void)
{
	Blinker_t blinker;
	
	hs_read_ExpectAndReturn('b');
	
	Command_Append_Expect(command, 'b');
	
	Serial_Service(&blinker);
}

void test_Serial_Service_parse_the_command_on_LF_and_serially_return_OK(void)
{
	Blinker_t blinker;
	
	hs_read_ExpectAndReturn(0x0A);
	
	Command_Parse_ExpectAndReturn(command, &blinker, 1);
	
	hs_write_Expect('O');
	hs_write_Expect('K');
	
	Command_Init_Expect(command);
	
	Serial_Service(&blinker);
}

void test_Serial_Service_parse_the_command_on_CR_and_serially_return_OK(void)
{
	Blinker_t blinker;
	
	hs_read_ExpectAndReturn(0x0D);
	
	Command_Parse_ExpectAndReturn(command, &blinker, 1);
	
	hs_write_Expect('O');
	hs_write_Expect('K');
	
	Command_Init_Expect(command);
	
	Serial_Service(&blinker);
}

void test_Serial_Service_parse_the_command_on_CR_and_serially_return_NO(void)
{
	Blinker_t blinker;
	
	hs_read_ExpectAndReturn(0x0D);
	
	Command_Parse_ExpectAndReturn(command, &blinker, 0);
	
	hs_write_Expect('N');
	hs_write_Expect('O');
	
	Command_Init_Expect(command);
	
	Serial_Service(&blinker);
}

