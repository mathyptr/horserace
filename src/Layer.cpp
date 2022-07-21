#include "Layer.hpp"

Layer::Layer(sf::Texture& tex, float speedF, const sf::IntRect& rect, const sf::Vector2f& pos, unsigned int z) : AnimatedSprite(sf::seconds(0.02))
{
    speedFactor = speedF;
    zLevel = z;
    setPosition(pos);    
    tex.setRepeated(true);
    tex.setSmooth(true);
    texture = &tex;

    Animation* an = new Animation(*texture);
    int frameCount = 50;
    for (int i = 0; i < frameCount; i++)
        an->addFrameRect(sf::IntRect(rect.left + ((float)i / frameCount) * rect.width /* / speedF */, rect.top, rect.width, rect.height));
    setLooped(true);
    play(*an);
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
