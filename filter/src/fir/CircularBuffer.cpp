/* Copyright (c) 2007, 2008 
 * James Grenning All Rights Reserved
 * Renaissance Software Consulting, Inc
 * For use as a conference exercise only
 * 
 * Contact info:
 * www.renaissancesoftware.net
 * www.renaissancesoftware.net/blog
 * james@renaissancesoftware.net
 */

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int capacity)
: capacity(capacity)
, index(0)
, outdex(0)
, count(0)
{
	values = new float[capacity];
}

CircularBuffer::~CircularBuffer()
{
	delete [] values;
}

bool CircularBuffer::IsEmpty() const
{
	return index == outdex;
}

bool CircularBuffer::IsFull() const
{
	return count == capacity;
}

void CircularBuffer::Put(float value)
{
	if (count >= capacity)
		throw CircularBufferException("Put to full circular buffer");

	count++;
	values[index] = value;
	
	index = NextDex(index);
}

float CircularBuffer::Get()
{
	if (count == 0)
		throw CircularBufferException("Get from empty circular buffer");
	
	count--;
	int value = values[outdex];
	outdex = NextDex(outdex);
	return value;
}

int CircularBuffer::Capacity() const
{
	return capacity;
}


int CircularBuffer::NextDex(int dex) const
{
	if (++dex >= capacity)
		dex = 0;
	return dex;
}

int CircularBuffer::PrevDex(int dex) const
{
  int prev = dex - 1;
 if (prev < 0)
   prev = capacity - 1;
 return prev;  
}

float CircularBuffer::Peek(int index) const
{
  return values[index];
}

int CircularBuffer::firstIndex() const
{
  return outdex;
}

int CircularBuffer::endIndex() const
{
  return index;
}

int CircularBuffer::LastIndex() const
{
  return PrevDex(index);
}