/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul
*/

#ifndef HARDSERIAL_H_
#define HARDSERIAL_H_

#include <inttypes.h>
#include <avr/io.h>
#ifndef TEST
	#include <avr/interrupt.h>
#endif

#define SERIAL_BUFFER_SIZE 128

typedef struct _ring_buffer {
	unsigned char buffer[SERIAL_BUFFER_SIZE];
	volatile unsigned int head;
	volatile unsigned int tail;
} ring_buffer;

typedef struct _hserial {
	ring_buffer *rx_buffer;
	ring_buffer *tx_buffer;
	volatile uint8_t *ubrrh;
	volatile uint8_t *ubrrl;
	volatile uint8_t *ucsra;
	volatile uint8_t *ucsrb;
	volatile uint8_t *udr;
	uint8_t rxen;
	uint8_t txen;
	uint8_t rxcie;
	uint8_t udrie;
} hserial;

hserial h_serial;

void hs_init();                   // Initializes all available serial ports.
void hs_start(uint32_t baud);  // Sets up a serial port.
void hs_end(void);
uint8_t hs_available();       // Checks whether data is available on the port
void hs_flush(void);            // Flushes the contents on the serial port.
int16_t hs_read(void);           // Gets next character (rx) on serial port.
void hs_write(uint8_t c);   // Write a character (tx) on serial port.

#endif