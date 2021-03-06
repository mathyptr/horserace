#ifndef LAYER_INCLUDE
#define LAYER_INCLUDE
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

#define MAX_HORIZONTAL_X 400

class Layer : public AnimatedSprite
{
public:
    Layer(sf::Texture& tex, float speedFactor, const sf::IntRect& rect, const sf::Vector2f& position, unsigned int z);
    float getSpeedFactor() const;
    void setSpeedFactor(float speedFactor);
    void draw(sf::RenderTarget &target, sf::RenderStates &states, unsigned int z);

private:
    float speedFactor;
};
#endif
