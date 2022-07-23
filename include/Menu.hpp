#ifndef MENU_INCLUDE
#define MENU_INCLUDE
#include <SFML/Graphics.hpp>

using namespace std;

class Menu : public sf::Drawable
{
public:
    Menu();
    Menu(const sf::Vector2f& position);
    void updateText(const sf::String bottomL, const sf::String topR, const sf::String bottomC, const sf::String topC, const sf::String bottomR, const sf::String topL);
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f position;

    sf::Font font;
    sf::Color fontColor;
    int fontSize;

    sf::Text topLeftText;
    sf::Text bottomLeftText;
    sf::Text topCenterText;
    sf::Text bottomCenterText;
    sf::Text topRightText;
    sf::Text bottomRightText;

    sf::Vector2f TopLeftPosition;
    sf::Vector2f BottomLeftPosition;
    sf::Vector2f TopCenterPosition;
    sf::Vector2f BottomCenterPosition;
    sf::Vector2f TopRightPosition;
    sf::Vector2f BottomRightPosition;
};
#endif
