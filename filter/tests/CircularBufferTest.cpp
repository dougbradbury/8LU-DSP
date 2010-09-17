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

#include "CppUTest/Extensions/SimpleStringExtensions.h"
#include "CppUTest/TestHarness.h"
#include "CircularBuffer.h"

TEST_GROUP(CircularBuffer) 
{
  CircularBuffer* buffer;

  void setup()
  {
    buffer = new CircularBuffer(5);
  }
  void teardown()
  {
    delete buffer;
  }
  
  void fillTheQueue(int seed, int count)
  {
	    for (int i = 0; i < count; i++)
	        buffer->Put(seed++);

  }
  
  void removeFromQueue(int count)
  {
	    for (int i = 0; i < count; i++)
	        buffer->Get();

  }
};

TEST(CircularBuffer, CreateDestroy)
{
}


TEST(CircularBuffer, EmptyAfterCreation)
{
    CHECK(buffer->IsEmpty());   
}

TEST(CircularBuffer, NotFullAfterCreation)
{
    CHECK(!buffer->IsFull());   
}

TEST(CircularBuffer, NotEmpty)
{
    buffer->Put(10046); 
    CHECK(!buffer->IsEmpty());   
}

TEST(CircularBuffer, NotEmptyThenEmpty)
{
    buffer->Put(4567);
    CHECK(!buffer->IsEmpty());
    buffer->Get();   
    CHECK(buffer->IsEmpty());
}

TEST(CircularBuffer, GetPutOneValue)
{
    buffer->Put(4567);
    LONGS_EQUAL(4567, buffer->Get());   
}


TEST(CircularBuffer, GetPutAFew)
{
    buffer->Put(1);
    buffer->Put(2);
    buffer->Put(3);
    LONGS_EQUAL(1, buffer->Get());   
    LONGS_EQUAL(2, buffer->Get());   
    LONGS_EQUAL(3, buffer->Get());   
}


TEST(CircularBuffer, Capacity)
{
    CircularBuffer buffer(2);
    LONGS_EQUAL(2, buffer.Capacity());
}


TEST(CircularBuffer, IsFull)
{
    for (int i = 0; i < buffer->Capacity(); i++)
        buffer->Put(i+100);
        
    CHECK(buffer->IsFull());
}


TEST(CircularBuffer, EmptyToFullToEmpty)
{
    for (int i = 0; i < buffer->Capacity(); i++)
        buffer->Put(i+100);
        
    CHECK(buffer->IsFull());
        
    for (int j = 0; j < buffer->Capacity(); j++)
        LONGS_EQUAL(j+100, buffer->Get());
        
    CHECK(buffer->IsEmpty());
    CHECK(!buffer->IsFull());
}

TEST(CircularBuffer, WrapAround)
{
    int capacity = buffer->Capacity();
    for (int i = 0; i < capacity; i++)
        buffer->Put(i+100);
        
    CHECK(buffer->IsFull());
    LONGS_EQUAL(100, buffer->Get());
    CHECK(!buffer->IsFull());
    buffer->Put(1000);
    CHECK(buffer->IsFull());
    
    for (int i = 1; i < capacity; i++)
        LONGS_EQUAL(i+100, buffer->Get());
        
    LONGS_EQUAL(1000, buffer->Get());
    CHECK(buffer->IsEmpty());
}

TEST(CircularBuffer, PutToFullThrows)
{
    fillTheQueue(900, buffer->Capacity());

    try
    {
    	buffer->Put(9999);
    	FAIL("Put to full buffer should throw");
    }
	catch (CircularBufferException& e)
	{
		CHECK_EQUAL("Put to full circular buffer", e.Message());
	}
}

TEST(CircularBuffer, PutToFullDoesNotDamageContents)
{
    fillTheQueue(900, buffer->Capacity());

    try
    {
    	buffer->Put(9999);
    }
	catch (CircularBufferException& e)
	{
	}
    
    for (int i = 0; i < buffer->Capacity(); i++)
        LONGS_EQUAL(i+900, buffer->Get());
        
    CHECK(buffer->IsEmpty());
}

TEST(CircularBuffer, GetFromEmptyThrows)
{
	try
	{
		buffer->Get(); 
		FAIL("Get from empty should throw");
	}
	catch (CircularBufferException& e)
	{
		CHECK_EQUAL("Get from empty circular buffer", e.Message());
	    CHECK(buffer->IsEmpty());  
	}
}

TEST(CircularBuffer, Peek)
{
  buffer->Put(1);
  buffer->Put(2);
  buffer->Put(3);
  buffer->Put(4);
  buffer->Put(5);
  buffer->Get();

  buffer->Put(6);
  
  int first = buffer->firstIndex();
  CHECK_EQUAL(2, buffer->Peek(first));
  int next = buffer->NextDex(first);
  CHECK_EQUAL(3, buffer->Peek(next));

  next = buffer->NextDex(next);
  CHECK_EQUAL(4, buffer->Peek(next));

  next = buffer->NextDex(next);
  CHECK_EQUAL(5, buffer->Peek(next));

  next = buffer->NextDex(next);
  CHECK_EQUAL(6, buffer->Peek(next));

  next = buffer->NextDex(next);  
  CHECK(buffer->endIndex() == next);  
}

TEST(CircularBuffer, lastIndexWrap)
{
  buffer->Put(1);
  buffer->Put(2);
  buffer->Put(3);
  buffer->Put(4);
  buffer->Put(5);

  CHECK_EQUAL(0, buffer->endIndex())
}

TEST(CircularBuffer, initalIndexState)
{
  CHECK_EQUAL(0, buffer->firstIndex());
  CHECK_EQUAL(0, buffer->endIndex());
}

TEST(CircularBuffer, prevdex)
{
  buffer->Put(1);
  buffer->Put(2);
  buffer->Put(3);
  buffer->Put(4);
  buffer->Put(5);
  buffer->Get();

  buffer->Put(6);
  
  int n = buffer->LastIndex();
  CHECK_EQUAL(0, n);
  
  CHECK_EQUAL(6, buffer->Peek(n));  
  n = buffer->PrevDex(n);

  CHECK_EQUAL(4, n);
  CHECK_EQUAL(5, buffer->Peek(n));
  n = buffer->PrevDex(n);

  CHECK_EQUAL(4, buffer->Peek(n));
  n = buffer->PrevDex(n);

  CHECK_EQUAL(3, buffer->Peek(n));
  n = buffer->PrevDex(n);

  CHECK_EQUAL(2, buffer->Peek(n));
  n = buffer->PrevDex(n);  
  
}
