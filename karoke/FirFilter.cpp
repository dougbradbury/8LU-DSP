#include "FirFilter.h"
#include "string.h"
#include "circularBuffer.h"
#include <iostream>
using namespace std;

FirFilter::FirFilter(int order) :
mOrder(order)
{
  mCoefficients = new float[mOrder];
  mDelayLine = new CircularBuffer(mOrder + 1);
  for(int i = 0; i < mOrder - 1; i++)
    mDelayLine->Put(0.0f);

  memset(mCoefficients, 0, sizeof(mCoefficients));
}

FirFilter::~FirFilter()
{
  delete[] mCoefficients;
  delete mDelayLine;
}

void FirFilter::setCoeffecients(float * coeffecients, int size)
{
  memcpy(mCoefficients, coeffecients, mOrder*sizeof(float));
}

float FirFilter::process(float input)
{
  float output = 0.0f;
  mDelayLine->Put(input);
  int n = mDelayLine->LastIndex();
  int stage = 0;
  while (stage < mOrder)
  {
    float z = mDelayLine->Peek(n);
    output += mCoefficients[stage] * z;
    n = mDelayLine->PrevDex(n);    
    stage++;
  }
  mDelayLine->Get();
  return output;
}