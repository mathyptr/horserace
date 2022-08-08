#include "Obstacle.hpp"

Obstacle::Obstacle(const sf::Texture& texture, float enemeyMoveSpeed, float posx, float posy,unsigned int zlevel,unsigned int maxy) :
    mSprite(texture),
    mDistanceTravelled(800),
    mMaximumDistance(0)
{
    this->posx=posx;
    this->posy=posy;
    this->mSpeedPerSecond = enemeyMoveSpeed;
    this->mSprite.setPosition(posx, posy);
    this->zlevel= zlevel;
    this->maxy= maxy;

}

void Obstacle::updateObstacle(float rspeedX, float timeDelta)
{
    auto distanceTravelledThisUpdate = mSpeedPerSecond * timeDelta;
    mDistanceTravelled += distanceTravelledThisUpdate;
    float oX;
    oX = rspeedX *ADJUST/ BOTTOM_SPEED_FACTOR;
    mSprite.move(oX,0);
    posx=mSprite.getPosition().x;

}

sf::FloatRect Obstacle::getObstacleGlobalBounds() const
{
    return mSprite.getGlobalBounds();
}

sf::Vector2f Obstacle::getObstaclePosition() const
{
  return mSprite.getPosition();
}

unsigned int Obstacle::getZLevel() const
{
    return zlevel;
}

bool Obstacle::isObstacleAlive() const
{
    return posx>10;
}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
