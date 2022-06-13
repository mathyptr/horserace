#include "Layer.hpp"


Layer::Layer():
  mSpeedPerSecond(800.f),
  mDistanceTravelled(0),
  mMaximumDistance(900.f)
{
  
}

void Layer::Init(const sf::Texture& texture,unsigned int speedFactor, const sf::IntRect& rect, const sf::Vector2f& position)
{
  this->mtexture=texture;
  mposition=position;
  mspeedFactor=speedFactor;
  this->mTile.Init(texture, rect, mposition);
  this->mTileR.Init(texture, rect,sf::Vector2f(static_cast<float>(mposition.x+800),static_cast<float>(mposition.y+472) ) );
  this->mTileL.Init(texture, rect,sf::Vector2f(static_cast<float>(mposition.x-800),static_cast<float>(mposition.y+472) ) );

}

sf::Vector2f Layer::getPosition()
{
  return mposition;
}

void Layer::setPosition(float x, float y)
{
  mposition.x=x;
  mposition.y=y;
  mTile.setPosition(x,y);
  mTileR.setPosition(x+800,y);
  mTileL.setPosition(x-800,y);
}


void Layer::move(float offsetX, float offsetY)
{

  float oX,oY;
  oX=offsetX/mspeedFactor;
  oY=offsetY/mspeedFactor;
  mTile.move(oX,oY);
  mTileR.move(oX,oY);
  mTileL.move(oX,oY);

  if (this->getPosition().x > 400)
    this->setPosition(-400, mposition.y);
  else if (this->getPosition().x < -400)
    this->setPosition(400, mposition.y);

  mposition= mTile.getPosition();

}


void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mTile, states);
    target.draw(mTileR, states);    
    target.draw(mTileL, states);
}


