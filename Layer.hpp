#ifndef LAYER_INCLUDE
#define LAYER_INCLUDE
#include <SFML/Graphics.hpp>
#include "Component.hpp"

class Layer : public sf::Drawable
{
public:
    Layer();
    void Init(const sf::Texture& texture, unsigned int speedFactor, const sf::IntRect& rect, const sf::Vector2f& position) ;
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Texture     texture;
    sf::Vector2f    position;
    Component       Tile;
    Component       TileR;
    Component       TileL;
    unsigned int zlevel;
    unsigned int zlevel_Act;
    unsigned int    mspeedFactor;
};
#endif
