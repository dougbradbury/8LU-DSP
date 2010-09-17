#include "CppUTest/TestHarness.h"
#include "filterBuildTime.h"

TEST_GROUP(filterBuildTime)
{
  filterBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new filterBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(filterBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

