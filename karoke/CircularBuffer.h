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


#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H
///////////////////////////////////////////////////////////////////////////////
//
//  CircularBuffer.h
//
//  CircularBuffer is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

#include <string>

class Printer;

class CircularBuffer
{
  public:
    explicit CircularBuffer(int capacity);
    virtual ~CircularBuffer();
    
    bool IsEmpty() const;
    bool IsFull() const;
    void Put(float);
    float Get();
    int Capacity() const;
    float Peek(int index) const;
    int firstIndex() const;
    int endIndex() const;
    int LastIndex() const;
    int NextDex(int dex) const;
    int PrevDex(int dex) const;
  private:
	  
	  int capacity;
	  int index;
	  int outdex;
	  int count;
	  float* values;
	  
	  
 
    CircularBuffer(const CircularBuffer&);
    CircularBuffer& operator=(const CircularBuffer&);
};

class CircularBufferException
{
	public:
		CircularBufferException(std::string message)
		: message(message){}
		
		std::string Message(){return message;}
		
	private:
		std::string message;
	
};

#endif  // D_CircularBuffer_H
