#ifndef HORSE_INCLUDE
#define HORSE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "MovingSprite.hpp"

#define HORSE_SHEETS_NUM 5
#define MAXSPEED 500.f
#define SPEEDTRESHOLD 100.f
#define SPEEDFACTOR 10.f
#define SPEEDSMOOTH 40.f

class Horse
{
public:
    Horse();
    void init(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z);
    void setName(std::string name);
    std::string getName();
    sf::FloatRect getHorseGlobalBounds() const;
    sf::Vector2f getHorsePosition() const;
    void setHorsePosition(float x, float y);
    void setHorseOrigin(float x, float y);
    void move(sf::Keyboard::Key key, float sec);
    void move(float offsetX, float offsetY);
    float getSpeed();
    void incSpeed(float sec);
    void decSpeed(float sec);
    void setTexture();
    void setScale(float factorX, float factorY);
    void draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z);
private:
    std::string horseName;
    unsigned int horseNumber;
    float speed;
    float speedFactor;
    unsigned int zlevel;
    MovingSprite sprite;
    std::vector<sf::Texture> sheets;
    int sheetIndex;
    void loadImage();
    void setPropHorse();
};
#endif // HORSE_INCLUDE
