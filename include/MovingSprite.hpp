#ifndef COMPONENT_INCLUDE
#define COMPONENT_INCLUDE
#include <SFML/Graphics.hpp>

class MovingSprite : public sf::Drawable
{
public:
    MovingSprite();
    void init(const sf::Texture& tex, const sf::IntRect& rect, const sf::Vector2f& position, unsigned int z);
    void init(const sf::Texture& tex, const sf::Vector2f& position, unsigned int z);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    sf::Vector2f getScale() const;
    void setScale (float factorX, float factorY);
    unsigned int getZLevel() const;
    void setZLevel(unsigned int z);
    void setTexture(sf::Texture& tex);
    sf::FloatRect getBounds() const;
    void setOrigin(float x, float y);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Texture texture;
    sf::Sprite sprite;
    unsigned int zLevel;
};
#endif
