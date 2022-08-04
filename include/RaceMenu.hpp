#ifndef RACEMENU_INCLUDE
#define RACEMENU_INCLUDE

#include <SFML/Graphics.hpp>
#include "PropertyManager.hpp"
#include "Utility.hpp"

#define TRACK_TEXT_POSITION sf::Vector2f(10, 0)
#define LIFE_TEXT_POSITION sf::Vector2f(10, 525)
#define MONEY_TEXT_POSITION sf::Vector2f(10, 560)

class RaceMenu : public sf::Drawable
{
public:
    RaceMenu();
    RaceMenu(const sf::Vector2f& position,int index);
    void update(sf::Time deltaTime,int index);
    void setTrackText(std::string text);
    void setLifeText(std::string text);
    void setMoneyText(std::string text);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f position;

    sf::Font font;
    sf::Color fontColor;
    int fontSize;

    sf::Text trackText;
    sf::Text lifeText;
    sf::Text moneyText;
};
#endif
