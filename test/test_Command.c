#include "unity.h"

#include "Command.h"
#include "mock_Blinker.h"

#include <inttypes.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_Command_Init(void) {
	char command[] = {'h', 'e', 'y', '\0'};
	
	Command_Init(command);
	
	TEST_ASSERT_EQUAL(0, command[0]);
	TEST_ASSERT_EQUAL(0, command[1]);
	TEST_ASSERT_EQUAL(0, command[2]);
	TEST_ASSERT_EQUAL(0, command[3]);
}

void test_Command_Parse_should_return_1_if_command_is_valid(void) {
	Blinker_t blinker;
	char command[] = {'b', 'l', 'i', 'n', 'k', ' ', '6', '0', '0', '\0'};
	
	Blinker_UpdateInterval_Expect(&blinker, 300);
	
	TEST_ASSERT_EQUAL(1, Command_Parse(command, &blinker));
}

void test_Command_Parse_should_return_0_if_command_is_invalid(void) {
	Blinker_t blinker;
	char command[] = {'b', 'l', 'n', 'k', ' ', '6', '0', '0', '\0'};
	
	TEST_ASSERT_EQUAL(0, Command_Parse(command, &blinker));
}

void test_Command_Append(void) {
	char command[] = {'h', 'i', '\0'};
	
	Command_Append(command, 'v');
	
	TEST_ASSERT_EQUAL( 'h', command[0]);
	TEST_ASSERT_EQUAL( 'i', command[1]);
	TEST_ASSERT_EQUAL( 'v', command[2]);
	TEST_ASSERT_EQUAL('\0', command[3]);
}

