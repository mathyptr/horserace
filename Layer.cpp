#include "Layer.hpp"


Layer::Layer()
{
    zlevel=0;
}

void Layer::init(const sf::Texture& text,unsigned int speedFactor, const sf::IntRect& rect, const sf::Vector2f& pos)
{
  texture=text;
  position=pos;
  speedFactor=speedFactor;
  tile.init(texture, rect, position);
  tileR.init(texture, rect,sf::Vector2f(static_cast<float>(position.x+800),static_cast<float>(position.y+472) ) );
  tileL.init(texture, rect,sf::Vector2f(static_cast<float>(position.x-800),static_cast<float>(position.y+472) ) );

}

sf::Vector2f Layer::getPosition()
{
  return position;
}

void Layer::setPosition(float x, float y)
{
  position.x=x;
  position.y=y;
  tile.setPosition(x,y);
  tileR.setPosition(x+800,y);
  tileL.setPosition(x-800,y);
}


void Layer::move(float offsetX, float offsetY)
{

  float oX,oY;
  oX=offsetX/speedFactor;
  oY=offsetY/speedFactor;
  tile.move(oX,oY);
  tileR.move(oX,oY);
  tileL.move(oX,oY);

  if (this->getPosition().x > 400)
    this->setPosition(-400, position.y);
  else if (this->getPosition().x < -400)
    this->setPosition(400, position.y);

  position= tile.getPosition();

}

void Layer::setLevel(unsigned int lev)
{
    zlevel=lev;
}
unsigned int Layer::getLevel()
{
    return zlevel;
}


void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states,unsigned int zlevel)
{
    if(getLevel()==zlevel)
    {
        target.draw(tile, states);
        target.draw(tileR, states);
        target.draw(tileL, states);
    }
}


