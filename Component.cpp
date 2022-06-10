#include "Component.hpp"


Component::Component():
  mSpeedPerSecond(800.f),
  mDistanceTravelled(0),
  mMaximumDistance(900.f)
{
  
}

void Component::Init(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position)
{
  this->mtexture=texture;
  this->mSprite.setTexture(this->mtexture);
  this->mSprite.setPosition(position);
  this->mSprite.setTextureRect(rect);   
}


sf::Vector2f Component::getPosition() const
{
  return mSprite.getPosition();
}

void Component::setPosition(float x, float y)
{
  mSprite.setPosition(x,y);
}


void Component::move(float offsX, float offsY)
{
  mSprite.move(offsX,offsY);
}


void Component::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


