#ifndef PROPERTYMANAGER_INCLUDE
#define PROPERTYMANAGER_INCLUDE

#include <SFML/System.hpp>
#include <iostream>
#include "sqlite3.h"
using namespace std;

#define getDBInstance() PropertyManager::getInstance()

#define FONT_FILE "font_file"
#define FONT_SIZE "font_size"
#define FONT_COLOR "font_color"
#define TOP_PIC "top_pic" 
#define BOTTOM_PIC "bottom_pic"
#define FINALLINE_PIC "finalline_pic"
#define CENTER_PIC "center_pic"
#define SKY_PIC "sky_pic"
#define FRONT_PIC "front_pic"
#define SOUND "sound"
#define PATHLENGTH "length"

#define WEATHER_TEX "main_texture"
#define WEATHER_EXP "explosion_texture"

class PropertyManager
{
public:
	static PropertyManager* getInstance();

	int connect();
	void close();
	int getStatus();

	std::string getTrackProperty(int trackID, std::string propName);
	std::string getTrackProperty(std::string trackName, std::string propName);
    int getTrackCount();
	std::string getHorseProperty(int horseID, std::string propName);
    int getHorseCount();
    std::string getWeatherProperty(int weatherID, std::string propName);
    std::string getWeatherProperty(std::string weatherName, std::string propName);
    std::string getWeatherProbability(int weatherID, int trackID);
    std::string getCurrentWeatherTexture(std::string weatherId);
    std::string getCurrentWeatherExplosion(std::string weatherId);
    std::string getProbability(std::string trackID, std::string weatherId);

private:
	PropertyManager();
	static PropertyManager* instance;

	sqlite3* db;
	int status;
	std::string sendQuery(std::string sql);
};
#endif
