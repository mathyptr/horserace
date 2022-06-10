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
    sf::Texture     mtexture;
    sf::Vector2f    mposition;
    Component       mTile;
    Component       mTileR;
    Component       mTileL;
    const float     mSpeedPerSecond;
    float           mDistanceTravelled;
    const float     mMaximumDistance;
    unsigned int    mspeedFactor;
};
#endif
