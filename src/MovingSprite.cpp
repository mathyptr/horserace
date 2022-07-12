#include "MovingSprite.hpp"

MovingSprite::MovingSprite()
{

}

void MovingSprite::init(const sf::Texture& tex, const sf::IntRect& rect, const sf::Vector2f& position, unsigned int z)
{
    texture = tex;
    zLevel = z;
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setTextureRect(rect);
}

void MovingSprite::init(const sf::Texture &tex, const sf::Vector2f &position, unsigned int z)
{
    texture = tex;
    zLevel = z;
    sprite.setTexture(texture, true);
    sprite.setPosition(position);
}

sf::Vector2f MovingSprite::getPosition() const
{
    return sprite.getPosition();
}

void MovingSprite::setPosition(float x, float y)
{
    sprite.setPosition(x,y);
}

void MovingSprite::move(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
}

unsigned int MovingSprite::getZLevel() const
{
    return zLevel;
}

void MovingSprite::setZLevel(unsigned int z)
{
    zLevel = z;
}

sf::Vector2f MovingSprite::getScale() const
{
    return sprite.getScale();
}

void MovingSprite::setScale(float factorX, float factorY)
{
    sprite.setScale(factorX, factorY);
}

void MovingSprite::setTexture(sf::Texture &tex)
{
    texture = tex;
    sprite.setTexture(texture);
}

sf::FloatRect MovingSprite::getBounds() const
{
    return sprite.getGlobalBounds();
}

void MovingSprite::setOrigin(float x, float y)
{
    sprite.setOrigin(x, y);
}

void MovingSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
