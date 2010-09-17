#include "filterBuildTime.h"

filterBuildTime::filterBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

filterBuildTime::~filterBuildTime()
{
}

const char* filterBuildTime::GetDateTime()
{
    return dateTime;
}

