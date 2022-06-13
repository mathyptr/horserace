#ifndef PROPERTYMANAGER_INCLUDE
#define PROPERTYMANAGER_INCLUDE

#include <SFML/System.hpp>
#include <iostream>
using namespace std;

/*
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

*/

#define FONT_TYPE "FONT_TYPE"
#define FONT_SIZE "FONT_SIZE"
#define FONT_COLOR "FONT_COLOR"
#define TOP_PIC "TOP_PIC" 
#define BOTTOM_PIC "BOTTOM_PIC"
#define CENTER_PIC "CENTER_PIC"
#define ATMO_PIC "ATMO_PIC"
#define FRONT_PIC "FRONT_PIC"
#define SOUND_CHALL "SOUND_CHALL"


#include "sqlite3.h"

class propertyManager 
{
public:
    propertyManager();
    void setChall(std::string actChall);
    std::string getChall();
    int Connect() ;
    int getStatus();
    void Close() ;
    void Query() ;
    std::string  getChallProperty(std::string  prop);
    std::string  getActualChall(std::string  challId);


private:
  sqlite3* mdb;
  int mstatus;
  std::string  mactChall;
  std::string   sendQuery(std::string sql);
};
#endif
