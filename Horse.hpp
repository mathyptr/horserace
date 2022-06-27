#ifndef HORSE_INCLUDE
#define HORSE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>

#define NUM_IMG_HORSE 5
#define MAXSPEED  500.f
#define SPEEDTRHESOLD  100.f
#define SPEEDFACTOR  10.f
#define SPEEDSMOOTH 40.f

/*
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

*/

class Horse
{
public:
   Horse();
   void setName(std::string name);
   std::string getName();
   void init(unsigned int num,sf::Vector2f orig,sf::Vector2f pos, unsigned int lev);
   sf::FloatRect getHorseGlobalBounds() const;
   sf::Vector2f getHorsePosition() const;
   void setHorsePosition(float x, float y);
   void setHorseOrigin(float x, float y);
   void setScale (float factorX, float factorY);
   void move(sf::Keyboard::Key key, float sec);
   void move(float offsetX, float offsetY);
   float getSpeed();
   void incSpeed(float sec);
   void decSpeed(float sec);
   void setTexture();
   void setLevel(unsigned int lev);
   unsigned int getLevel() const;
   void draw(sf::RenderTarget &target, sf::RenderStates states,unsigned int zlevel);
private:
    std::string horseName;
    sf::Texture     horse;
    sf::Sprite      Sprite;
    sf::Texture     horse1;
    sf::Texture     horse2;
    sf::Texture     horse3;
    sf::Texture     horse4;
    sf::Texture     horse5;
    unsigned int zlevel;
    unsigned int num;
    int indeximg;
    float speedX;
    unsigned int    speedFactor;
    bool directionLeft;
    void loadImage();
    void setPropHorse();
};

#endif // HORSE_INCLUDE
