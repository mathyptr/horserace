#include "Layer.hpp"


Layer::Layer()
{
    zlevel=0;
    zlevel_Act=0;
}

void Layer::Init(const sf::Texture& text,unsigned int speedFactor, const sf::IntRect& rect, const sf::Vector2f& pos)
{
  texture=text;
  position=pos;
  speedFactor=speedFactor;
  Tile.Init(texture, rect, position);
  TileR.Init(texture, rect,sf::Vector2f(static_cast<float>(position.x+800),static_cast<float>(position.y+472) ) );
  TileL.Init(texture, rect,sf::Vector2f(static_cast<float>(position.x-800),static_cast<float>(position.y+472) ) );

}

sf::Vector2f Layer::getPosition()
{
  return position;
}

void Layer::setPosition(float x, float y)
{
  position.x=x;
  position.y=y;
  Tile.setPosition(x,y);
  TileR.setPosition(x+800,y);
  TileL.setPosition(x-800,y);
}


void Layer::move(float offsetX, float offsetY)
{

  float oX,oY;
  oX=offsetX/mspeedFactor;
  oY=offsetY/mspeedFactor;
  Tile.move(oX,oY);
  TileR.move(oX,oY);
  TileL.move(oX,oY);

  if (this->getPosition().x > 400)
    this->setPosition(-400, position.y);
  else if (this->getPosition().x < -400)
    this->setPosition(400, position.y);

  position= Tile.getPosition();

}


void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(zlevel_Act==zlevel)
    {
        target.draw(Tile, states);
        target.draw(TileR, states);
        target.draw(TileL, states);
    }
//       zlevel_Act++;
}


