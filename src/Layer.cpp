#include "Layer.hpp"
#include <iostream>
#include <SFML/OpenGL.hpp>

Layer::Layer()
{
    
}

Layer::Layer(sf::Texture& tex, float speedF, const sf::IntRect& rect, const sf::Vector2f& pos, unsigned int z) : AnimatedSprite(sf::seconds(0.02))
{
    speedFactor = speedF;
    zLevel = z;
    setPosition(pos);    
/*     tex.setRepeated(true); */
    texture = &tex;
    sf::Texture::bind(texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
/*     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); */
    sf::Texture::bind(NULL);

    Animation* an = new Animation(*texture);
    //int frameCount = rect.width
    int frameCount = 50;
    for (int i = 0; i < frameCount; i++)
    {
        an->addFrameRect(sf::IntRect(rect.left + ((float)i / frameCount) * rect.width, rect.top, rect.width, rect.height));
        sf::IntRect r = an->getFrameRect(i); 
        std::cout << r.top << " " << r.left << "\n";
    }
    setLooped(true);
    play(*an);
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
