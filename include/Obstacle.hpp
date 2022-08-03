#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE

#include <SFML/Graphics.hpp>
#include <Track.hpp>
#include <iostream>
/*
#define  HORSE1_POSX 400
#define  HORSE1_POSY 472
#define  HORSE2_POSX 400
#define  HORSE2_POSY 522
#define  HORSE3_POSX 400
#define  HORSE3_POSY 562
*/


class Obstacle : public sf::Drawable
{
public:
    Obstacle(const sf::Texture& texture,  float enemyMoveSpeed, float posx, float posy,unsigned int zlevel,unsigned int maxy);
    void updateObstacle(float speedX, float timeDelta);
    sf::FloatRect getObstacleGlobalBounds() const;
    sf::Vector2f getObstaclePosition() const;
    unsigned int getZLevel() const;
    bool isObstacleAlive() const;

private:
    sf::Sprite mSprite;
    unsigned int zlevel;
    unsigned int maxy;
    float posx,posy;
    float mSpeedPerSecond;
    float mDistanceTravelled;
    const float mMaximumDistance;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Texture obstaclepic;
};
#endif
