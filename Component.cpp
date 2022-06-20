#include "Component.hpp"


Component::Component()
{

}

void Component::init(const sf::Texture& text, const sf::IntRect& rect, const sf::Vector2f& position)
{
  texture=text;
  sprite.setTexture(texture);
  sprite.setPosition(position);
  sprite.setTextureRect(rect);
}


sf::Vector2f Component::getPosition() const
{
  return sprite.getPosition();
}

void Component::setPosition(float x, float y)
{
  sprite.setPosition(x,y);
}

void Component::move(float offsX, float offsY)
{
  sprite.move(offsX,offsY);
}

void Component::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(sprite, states);
}


