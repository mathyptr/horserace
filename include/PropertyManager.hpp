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

#define FONT_FILE "font_file"
#define FONT_SIZE "font_size"
#define FONT_COLOR "font_color"
#define TOP_PIC "top_pic" 
#define BOTTOM_PIC "bottom_pic"
#define CENTER_PIC "center_pic"
#define SKY_PIC "sky_pic"
#define FRONT_PIC "front_pic"
#define SOUND "sound"
#define PATHLENGTH "length"

#define WEATHER_TEX "main_texture"
#define WEATHER_EXP "explosion_texture"

#include "sqlite3.h"

class PropertyManager
{
public:
	PropertyManager(bool autoConnect = true);
	int connect();
	void close();
	int getStatus();
	std::string getTrackProperty(int trackID, std::string propName);
	std::string getTrackProperty(std::string trackName, std::string propName);
    std::string getTrackCount();
    std::string getWeatherProperty(int weatherID, std::string propName);
    std::string getWeatherProperty(std::string weatherName, std::string propName);
    std::string getWeatherProbability(int weatherID, int trackID);

    std::string getCurrentWeatherTexture(std::string weatherId);
    std::string getCurrentWeatherExplosion(std::string weatherId);
    std::string getProbability(std::string trackID, std::string weatherId);

private:
	sqlite3* db;
	int status;
	std::string sendQuery(std::string sql);
};
#endif
