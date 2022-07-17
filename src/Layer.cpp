#include "Layer.hpp"

Layer::Layer()
{
    
}

Layer::Layer(const sf::Texture& tex, float speedF, const sf::IntRect& rect, const sf::Vector2f& pos, unsigned int z) : AnimatedSprite(sf::seconds(0.01))
{
    speedFactor = speedF;
    zLevel = z;
    setPosition(pos);    
    texture = &tex;

    Animation* an = new Animation(*texture);
    //int frameCount = rect.width
    int frameCount = 50;
    for (int i = 0; i < frameCount; i++)
        an->addFrameRect(sf::IntRect(rect.top, rect.left + ((float)i / frameCount) * rect.width, rect.width, rect.height));
    play(*an);
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
