#ifndef LAYER_INCLUDE
#define LAYER_INCLUDE
#include <SFML/Graphics.hpp>
#include "Component.hpp"

class Layer
{
public:
    Layer();
    void init(const sf::Texture& texture, unsigned int speedFactor, const sf::IntRect& rect, const sf::Vector2f& position) ;
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void setLevel(unsigned int lev);
    void incLevel();
    unsigned int getLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int zlevel) ;
private:
    sf::Texture     texture;
    sf::Vector2f    position;
    Component       tile;
    Component       tileR;
    Component       tileL;
    unsigned int zlevel;
    unsigned int    speedFactor;
};
#endif
