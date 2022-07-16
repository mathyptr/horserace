#ifndef HORSE_INCLUDE
#define HORSE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "MovingSprite.hpp"

#define HORSE_SHEETS_NUM 5
#define MAXSPEED 500.f
#define SPEEDTHRESHOLD 100.f
#define SPEEDFACTOR 10.f
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
    void init(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z);
    void setName(std::string name);
    std::string getName() const;
    sf::FloatRect getHorseGlobalBounds() const;
    sf::Vector2f getHorsePosition() const;
    void setHorsePosition(float x, float y);
    void setHorseOrigin(float x, float y);
    unsigned int getZLevel() const;
    void move(bool go, float sec);
    void move(float offsetX, float offsetY);
    float getSpeed() const;
    void incSpeed(float sec);
    void decSpeed(float sec);
    bool decLife();
    void incLife();
    int getLife() const;
    bool decMoney();
    void incMoney(int coin);
    int getMoney() const;
    unsigned int getTravelled() const;
    float getTotalTravelled() const;
    void setTotalTravelled(float inc);
    void setTexture();
    void setScale(float factorX, float factorY);
    void draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z);

private:
    std::string horseName;
    unsigned int horseNumber;
    unsigned int travelled;
    float totalTravelled;
    float speed;
    float speedFactor;
    unsigned int zlevel;
    MovingSprite sprite;
    std::vector<sf::Texture> sheets;
    int sheetIndex;
    int life;
    int money;
    void loadImage();
    void setPropHorse();
};
#endif // HORSE_INCLUDE
