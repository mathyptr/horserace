#ifndef HORSEMENU_INCLUDE
#define HORSEMENU_INCLUDE
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Game.hpp"
#include "Horse.hpp"

using namespace std;

class Game;

class HorseMenu : public sf::Drawable
{
public:
    HorseMenu();
    HorseMenu(const sf::Vector2f& position, Game* parent);
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Game* parent;

    sf::Vector2f position;

    sf::Font font;
    sf::Color fontColor;
    int fontSize;

    sf::Text title;
    sf::RectangleShape panel;

    std::vector<unique_ptr<Horse>> horses;
    std::vector<sf::Text> horseLabels;

    int selected;
    sf::RectangleShape selectedRect;

};
#endif
