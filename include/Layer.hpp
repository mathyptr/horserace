#ifndef LAYER_INCLUDE
#define LAYER_INCLUDE
#include <SFML/Graphics.hpp>
#include "MovingSprite.hpp"

#define MAX_HORIZONTAL_X 400

class Layer
{
public:
    Layer();
    Layer(const sf::Texture& tex, float speedFactor, const sf::IntRect& rect, const sf::Vector2f& position, unsigned int z);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void setZLevel(unsigned int z);
    unsigned int getZLevel() const;
    void draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z);
private:
    sf::Texture texture;
    sf::Vector2f position;
    MovingSprite tile;
    MovingSprite tileR;
    MovingSprite tileL;
    unsigned int zlevel;
    float speedFactor;
};
#endif
