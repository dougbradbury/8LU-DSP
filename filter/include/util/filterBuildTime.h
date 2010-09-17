#ifndef D_filterBuildTime_H
#define D_filterBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  filterBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class filterBuildTime
  {
  public:
    explicit filterBuildTime();
    virtual ~filterBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    filterBuildTime(const filterBuildTime&);
    filterBuildTime& operator=(const filterBuildTime&);

  };

#endif  // D_filterBuildTime_H
