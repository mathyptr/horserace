#ifndef COMPONENT_INCLUDE
#define COMPONENT_INCLUDE
#include <SFML/Graphics.hpp>

class Component :  public sf::Drawable
{
public:
    Component();
    void init(const sf::Texture& texture,const sf::IntRect& rect, const sf::Vector2f& position) ;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    void move(float offsX, float offsY);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)  const override;
    sf::Texture     texture;
    sf::Sprite      sprite;

};
#endif
