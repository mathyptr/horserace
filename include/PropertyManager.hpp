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
#define PATHLENGHT "PATHLENGHT"

#include "../sqlite3.h"

class PropertyManager
{
public:
    PropertyManager();
    int Init();
    int Connect();
    int getStatus();
    void Close();
    void Query();
    void setTrack(std::string currentTrack);
    std::string getTrack();
    std::string getTrackProperty(std::string propName);
    std::string getCurrentTrack(std::string trackID);
    std::string getNumTrack(std::string trackID);
    std::string getCurrentWeatherTexture(std::string trackID, std::string probability);
    std::string getCurrentWeatherExplosion(std::string trackID, std::string probability);
private:
  sqlite3* db;
  int status;
  std::string currentTrack;
  std::string sendQuery(std::string sql);
};
#endif
