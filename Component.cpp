#include "Component.hpp"


Component::Component()
{
  
}

void Component::Init(const sf::Texture& text, const sf::IntRect& rect, const sf::Vector2f& position)
{
  texture=text;
  Sprite.setTexture(texture);
  Sprite.setPosition(position);
  Sprite.setTextureRect(rect);
}


sf::Vector2f Component::getPosition() const
{
  return Sprite.getPosition();
}

void Component::setPosition(float x, float y)
{
  Sprite.setPosition(x,y);
}


void Component::move(float offsX, float offsY)
{
  Sprite.move(offsX,offsY);
}


void Component::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(Sprite, states);
}


