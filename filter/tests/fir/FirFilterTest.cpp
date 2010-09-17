#include "FirFilter.h"
#include <iostream>
using namespace std;

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(FirFilter)
{
  FirFilter* firFilter;

  void setup()
  {
    firFilter = 0;
  }
  void teardown()
  {
    if (firFilter)
      delete firFilter;
  }
};

TEST(FirFilter, TwoStage)
{
  firFilter = new FirFilter(2);
  float coeffecients[] = {0.5f, 0.5f};
  firFilter->setCoeffecients(coeffecients, sizeof(coeffecients));
  CHECK_EQUAL(0.5f, firFilter->process(1.0f));
  CHECK_EQUAL(1.0f, firFilter->process(1.0f));  
  CHECK_EQUAL(1.0f, firFilter->process(1.0f));  
  CHECK_EQUAL(1.0f, firFilter->process(1.0f));  
  CHECK_EQUAL(1.0f, firFilter->process(1.0f));  
  DOUBLES_EQUAL(0.75f, firFilter->process(0.5f), 0.00001f);    
}

TEST(FirFilter, TwoStageAdvanced)
{
  firFilter = new FirFilter(2);
  float coeffecients[] = {0.5f, 0.1f};
  firFilter->setCoeffecients(coeffecients, sizeof(coeffecients));
  CHECK_EQUAL(0.5f * 1.0f, firFilter->process(1.0f));
  DOUBLES_EQUAL(0.1f * 0.5f + 1.0f * 0.1f, firFilter->process(0.1f), 0.00001f);  
}

float dblp_sfp[32] = {
    0.000922063956f,    0.000117008203f,    0.000123516301f,    0.000130276368f,    0.000136560577f,    0.000142284646f,    0.000147898424f,    0.000153079425f,    0.000157832184f,    0.000161808477f,    0.000165257537f,    0.000167802294f,    0.000170218234f,    0.000172472489f,    0.000174889158f,    0.000173808690f,    0.000173808690f,    0.000174889158f,    0.000172472489f,    0.000170218234f,    0.000167802294f,    0.000165257537f,    0.000161808477f,    0.000157832184f,    0.000153079425f,    0.000147898424f,    0.000142284646f,    0.000136560577f,    0.000130276368f,    0.000123516301f,    0.000117008203f,    0.000922063956f
};

TEST(FirFilter, ImpulseTest)
{
  firFilter = new FirFilter(32);
  firFilter->setCoeffecients(dblp_sfp, 32);
  float y[32];
  y[0] = firFilter->process(1.0);
  for (int i = 1 ; i < 32; i++)
  {
    y[i] = firFilter->process(0.0);
  }
  
  for (int i = 0 ; i < 32; i++)
  {
    // cout << dblp_sfp[i] << " == "<< y[i] << endl;
    
    DOUBLES_EQUAL(dblp_sfp[i], y[i], 0.00000001f);
  }
  
}

