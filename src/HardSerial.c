/*
  HardwareSerial.cpp - Hardware serial library for Wiring
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
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
*/

#include <inttypes.h>
#include <stdio.h>

#include "HardSerial.h"

// set register bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
// clear register bit
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer tx_buffer = { { 0 }, 0, 0};

inline void store_char(unsigned char c, ring_buffer *buffer)
{
	int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != buffer->tail)
	{
		buffer->buffer[buffer->head] = c;
		buffer->head = i;
	}
}


SIGNAL(USART_RX_vect)
{
	unsigned char c  =  UDR0;
	store_char(c, &rx_buffer);
}


ISR(USART_UDRE_vect)
{
	if (tx_buffer.head == tx_buffer.tail)
	{
		// Buffer empty, so disable interrupts
		cbi(UCSR0B, UDRIE0);
	}
	else
	{
		// There is more data in the output buffer. Send the next byte
		unsigned char c = tx_buffer.buffer[tx_buffer.tail];
		tx_buffer.tail = (tx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;
		
		UDR0 = c;
	}
}


void hs_init(){
	h_serial.rx_buffer = &rx_buffer;
	h_serial.tx_buffer = &tx_buffer;
	h_serial.ubrrh = &UBRR0H;
	h_serial.ubrrl = &UBRR0L;
	h_serial.ucsra = &UCSR0A;
	h_serial.ucsrb = &UCSR0B;
	h_serial.udr = &UDR0;
	h_serial.rxen = RXEN0;
	h_serial.txen = TXEN0;
	h_serial.rxcie = RXCIE0;
	h_serial.udrie = UDRIE0;
}

void hs_start(uint32_t baud){
	
	*h_serial.ubrrh = ((F_CPU / 16 + baud / 2) / baud - 1) >> 8;
	*h_serial.ubrrl = ((F_CPU / 16 + baud / 2) / baud - 1);
	
	sbi(*h_serial.ucsrb, h_serial.rxen);
	sbi(*h_serial.ucsrb, h_serial.txen);
	sbi(*h_serial.ucsrb, h_serial.rxcie);
	cbi(*h_serial.ucsrb, h_serial.udrie);
}

void hs_end()
{
	// wait for transmission of outgoing data
	while (h_serial.tx_buffer->head != h_serial.tx_buffer->tail)
		;
	
	cbi(*h_serial.ucsrb, h_serial.rxen);
	cbi(*h_serial.ucsrb, h_serial.txen);
	cbi(*h_serial.ucsrb, h_serial.rxcie);
	cbi(*h_serial.ucsrb, h_serial.udrie);
	
	// clear any received data
	h_serial.rx_buffer->head = h_serial.rx_buffer->tail;
}

uint8_t hs_available(void)
{
	return (uint8_t)(SERIAL_BUFFER_SIZE + h_serial.rx_buffer->head - h_serial.rx_buffer->tail) % SERIAL_BUFFER_SIZE;
}

int16_t hs_read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (h_serial.rx_buffer->head == h_serial.rx_buffer->tail)
	{
		return -1;
	}
	else
	{
		unsigned char c = h_serial.rx_buffer->buffer[h_serial.rx_buffer->tail];
		h_serial.rx_buffer->tail = (unsigned int)(h_serial.rx_buffer->tail + 1) % SERIAL_BUFFER_SIZE;
		return c;
	}
}

void hs_flush()
{
	h_serial.tx_buffer->head = h_serial.tx_buffer->tail;
}

void hs_write(uint8_t c)
{
	int i = (h_serial.tx_buffer->head + 1) % SERIAL_BUFFER_SIZE;
	
	// If the output buffer is full, there's nothing for it other than to 
	// wait for the interrupt handler to empty it a bit
	while (i == h_serial.tx_buffer->tail)
		;
	
	h_serial.tx_buffer->buffer[h_serial.tx_buffer->head] = c;
	h_serial.tx_buffer->head = i;
	
	sbi(*h_serial.ucsrb, h_serial.udrie);
}

void hs_write_int(uint64_t integer)
{
	char buffer [40];
	uint8_t length;
	uint8_t i = 0;
	hs_write('[');
	length = sprintf(buffer, "%u", integer);
	for (i = 0; i < integer; i++) {
		hs_write(buffer[i]);
	}
	hs_write(']');
}



