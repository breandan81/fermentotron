#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "ringBuffer.h"


void * operator new(size_t size);
void operator delete(void * ptr); 

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
} 

ringBuffer::ringBuffer(int len)
{
	bytes = 0;
	size = len;
	index = 0;
	buf = new char(len);
}
ringBuffer::~ringBuffer()
{
	delete buf;
}
int ringBuffer::push(char me)
{
	if(bytes == size)
	{
		return -1;
	}
	else
	{
		buf[(index+bytes)%size] = me;
		bytes++;
		return 0;
	}
}
int ringBuffer::pop()
{
	if(bytes == 0)
	{
		return -1;
	}
	else
	{
		int retVal = buf[index];
		bytes--;
		index = (index + 1)%size;
		return retVal;
	}
}
