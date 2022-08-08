#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE
#define ADJUST 1.6

#include <SFML/Graphics.hpp>
#include <Track.hpp>
#include <iostream>



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
