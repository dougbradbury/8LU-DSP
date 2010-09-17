#ifndef D_FirFilter_H
#define D_FirFilter_H

///////////////////////////////////////////////////////////////////////////////
//
//  FirFilter is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
class CircularBuffer;

class FirFilter
  {
  public:
    explicit FirFilter(int filterOrder);
    virtual ~FirFilter();
    
    void setCoeffecients(float * coeffecients, int size);
    float process(float input);

  private:

    float *  mCoefficients;
    CircularBuffer * mDelayLine;
    int mOrder;

    FirFilter(const FirFilter&);
    FirFilter& operator=(const FirFilter&);

  };

#endif  // D_FirFilter_H
