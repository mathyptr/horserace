#ifndef MENU_INCLUDE
#define MENU_INCLUDE
#include <SFML/Graphics.hpp>
#include "Component.hpp"

using namespace std;

class Menu : public sf::Drawable
{
public:
    Menu();
    void Init(sf::Text testBase, const sf::Vector2f& position) ;
    void UpdateText(const sf::String &showEnemiesLeft, const sf::String &livesLeft, const sf::String &bombsExploded, const sf::String &timeRemaining, const  sf::String &showLevel, const sf::String &speedometer);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);
    void move(float offsX, float offsY);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Texture     mtexture;
    sf::Vector2f    mposition;

    const float     mSpeedPerSecond;
    float           mDistanceTravelled;
    const float     mMaximumDistance;
    sf::Font mfont;
    sf::Text mtestBase;
    sf::Text mBottomLeft;
    sf::Text mTopRight;
    sf::Text mBottomCenter;
    sf::Text mTopCenter;
    sf::Text mBottomRight;
    sf::Text mTopLeft;
    sf::String mBottomLeftLabel;
    sf::String mTopRightLabel;
    sf::String mBottomCenterLabel;
    sf::String mTopCenterLabel;
    sf::String mBottomRightLabel;
    sf::String mTopLeftLabel;
    sf::Vector2f mTopLeftPosition;
    sf::Vector2f mTopCenterPosition;
    sf::Vector2f mTopRightPosition;
    sf::Vector2f mBottomLeftPosition;
    sf::Vector2f mBottomCenterPosition;
    sf::Vector2f mBottomRightPosition;


};
#endif
