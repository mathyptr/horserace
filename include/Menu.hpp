#ifndef MENU_INCLUDE
#define MENU_INCLUDE
#include <SFML/Graphics.hpp>

using namespace std;

class Menu : public sf::Drawable
{
public:
    Menu();
    void Init(sf::Text testBase, const sf::Vector2f& position) ;
    void UpdateText( const sf::String BottomL, const  sf::String TopR, const sf::String BottomC,  const sf::String TopC, const sf::String BottomR, const sf::String TopL);
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void move(float offsX, float offsY);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Texture     texture;
    sf::Vector2f    position;
    const float     mSpeedPerSecond;
    float           mDistanceTravelled;
    const float     mMaximumDistance;
    sf::Font font;
    sf::Text testBase;
    sf::Text BottomLeft;
    sf::Text TopRight;
    sf::Text BottomCenter;
    sf::Text TopCenter;
    sf::Text BottomRight;
    sf::Text TopLeft;
    sf::String BottomLeftLabel;
    sf::String TopRightLabel;
    sf::String BottomCenterLabel;
    sf::String TopCenterLabel;
    sf::String BottomRightLabel;
    sf::String TopLeftLabel;
    sf::Vector2f TopLeftPosition;
    sf::Vector2f TopCenterPosition;
    sf::Vector2f TopRightPosition;
    sf::Vector2f BottomLeftPosition;
    sf::Vector2f BottomCenterPosition;
    sf::Vector2f BottomRightPosition;
};
#endif
