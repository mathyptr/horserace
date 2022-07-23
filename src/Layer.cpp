#include "Layer.hpp"

Layer::Layer(sf::Texture& tex, float speedFactor, const sf::IntRect& rect, const sf::Vector2f& pos, unsigned int z) : AnimatedSprite()/*  : AnimatedSprite(sf::milliseconds(5) * rect.width / 800) */
{
    frameTime = sf::milliseconds(30);

    this->speedFactor = speedFactor;
    zLevel = z;
    setPosition(pos);    
    tex.setRepeated(true);
    tex.setSmooth(true);
    texture = &tex;

    Animation* an = new Animation(*texture);
    int frameCount = 1 / frameTime.asSeconds() * speedFactor;
    for (int i = 0; i < frameCount; i++)
        an->addFrameRect(sf::IntRect(rect.left + ((float)i / frameCount) * rect.width, rect.top, rect.width, rect.height));
    setLooped(true);
    play(*an);
}

float Layer::getSpeedFactor() const
{
    return speedFactor;
}

void Layer::setSpeedFactor(float speedFactor)
{
    this->speedFactor = speedFactor;
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
