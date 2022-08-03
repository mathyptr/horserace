#ifndef HORSE_INCLUDE
#define HORSE_INCLUDE

#include <SFML/Graphics.hpp>
#include <cmath>
#include "AnimatedSprite.hpp"
#include "PropertyManager.hpp"

#define GRAVITY 8*9.81
#define VO_Y 100
#define MAXSPEED 500.f
#define SPEEDTHRESHOLD 100.f
#define SPEEDFACTOR 10.f
#define SPEEDSMOOTH 40.f

#define SHEET_COUNT 5
#define SHEET_HEIGHT 51
#define SHEET_WIDTH 64

class Horse : public AnimatedSprite
{
public:
    Horse();
    Horse(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z);
    int getNumber() const;
    std::string getName() const;
    void setName(std::string name);
    void move(bool go, float sec);
    void move(float offsetX, float offsetY, float sec);
    float getSpeed() const;
    void incSpeed(float sec);
    void decSpeed(float sec);
    void setSpeed(float sec);
    int getLife() const;
    void incLife();
    bool decLife();
    int getMoney() const;
    void incMoney(int coin);
    bool decMoney();
    float yOnJump(float speed);
    void SetJumpON();
    void startPos(sf::Vector2f orig, sf::Vector2f pos);
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
    float agility;
    int life;
    int money;
    sf::Vector2f pos;
    bool jumpon;
    sf::Clock horseplayerJumpTimer;
    void setPropHorse();
};
#endif // HORSE_INCLUDE
