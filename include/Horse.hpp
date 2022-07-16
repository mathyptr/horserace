#ifndef HORSE_INCLUDE
#define HORSE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "AnimatedSprite.hpp"
#include "MovingSprite.hpp"

#define HORSE_SHEETS_NUM 5
#define MAXSPEED 500.f
#define SPEEDTHRESHOLD 100.f
#define SPEEDFACTOR 10.f
#define SPEEDSMOOTH 40.f

#define SHEET_COUNT 5
#define SHEET_HEIGHT 51
#define SHEET_WIDTH 64

/*
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

*/

class Horse : public AnimatedSprite
{
public:
    Horse();
    Horse(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z);
    std::string getName() const;
    void setName(std::string name);
    void move(bool go, float sec);
    void move(float offsetX, float offsetY, float sec);
    float getSpeed() const;
    void incSpeed(float sec);
    void decSpeed(float sec);
    int getLife() const;
    void incLife();
    bool decLife();
    int getMoney() const;
    void incMoney(int coin);
    bool decMoney();
    unsigned int getTravelled() const;
    float getTotalTravelled() const;
    void setTotalTravelled(float inc);
    void draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z);

private:
    std::string horseName;
    unsigned int horseNumber;
    unsigned int travelled;
    float totalTravelled;
    float speed;
    float speedFactor;

    int life;
    int money;
    void setPropHorse();
};
#endif // HORSE_INCLUDE
