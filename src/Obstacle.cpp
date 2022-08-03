#include "Obstacle.hpp"

Obstacle::Obstacle(const sf::Texture& texture, float enemeyMoveSpeed, float posx, float posy,unsigned int zlevel,unsigned int maxy) :
    mSprite(texture),
    mDistanceTravelled(800),
    mMaximumDistance(0)
{
 //   obstaclepic.loadFromFile("./img/player_right.png");
//    mSprite.setTexture(obstaclepic);

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
//    mSprite.move(distanceTravelledThisUpdate,speedX*timeDelta);
    float oX;
    oX = rspeedX / BOTTOM_SPEED_FACTOR;
    mSprite.move(oX,0);
  /*  if (mSprite.getPosition().x > 1600)
    {
        mSprite.setPosition(-800, mSprite.getPosition().y);
    }
    if (mSprite.getPosition().x < -800)
    {
        mSprite.setPosition(1600, mSprite.getPosition().y);
    }*/
    posx=mSprite.getPosition().x;
//  std::cout<<"Speed: "<<rspeedX<<" Posx: "<<posx<<" Posy: "<<posy<<std::endl;
 //   std::cout<<"Speed: "<<rspeedX<<" Posx: "<<mSprite.getPosition().x<<" Posy: "<<mSprite.getPosition().y<<std::endl;

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
    //return true;
    //return mDistanceTravelled > 0;
    return posx>10;
//    return posx>0;
}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
