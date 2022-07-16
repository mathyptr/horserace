#include "Layer.hpp"

Layer::Layer()
{
    
}

Layer::Layer(const sf::Texture& tex, float speedF, const sf::IntRect& rect, const sf::Vector2f& pos, unsigned int z)
{
    zlevel = z;
    texture = tex;
    position = pos;
    speedFactor = speedF;
    tile.init(texture, rect, position, z);
    tileR.init(texture, rect,sf::Vector2f(static_cast<float>(position.x+800),static_cast<float>(position.y+472)), z);
    tileL.init(texture, rect,sf::Vector2f(static_cast<float>(position.x-800),static_cast<float>(position.y+472)), z);
}

sf::Vector2f Layer::getPosition() const
{
    return position;
}

void Layer::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    tile.setPosition(x, y);
    tileR.setPosition(x+800, y);
    tileL.setPosition(x-800, y);
}

void Layer::move(float offsetX, float offsetY)
{
    float oX, oY;
    oX = offsetX / speedFactor;
    oY = offsetY / speedFactor;
    tile.move(oX, oY);
    tileR.move(oX, oY);
    tileL.move(oX, oY);
    if (getPosition().x > MAX_HORIZONTAL_X)
        setPosition(-MAX_HORIZONTAL_X, position.y);
    else if (getPosition().x < -MAX_HORIZONTAL_X)
        setPosition(MAX_HORIZONTAL_X, position.y);
    position = tile.getPosition();
}

void Layer::setZLevel(unsigned int z)
{
    zlevel = z;
}

unsigned int Layer::getZLevel() const
{
    return zlevel;
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z)
{
    if(getZLevel() == z)
    {
        target.draw(tile, states);
        target.draw(tileR, states);
        target.draw(tileL, states);
    }
}


