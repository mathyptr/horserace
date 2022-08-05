#ifndef HORSEMENU_INCLUDE
#define HORSEMENU_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Horse.hpp"

#define MENU_SIZE_X 600
#define MENU_SIZE_Y 400
#define MENU_BG_COLOR sf::Color(220, 220, 220, 220)

#define TITLE_MSG "Choose your horse"
#define TITLE_X 400
#define TITLE_Y 150
#define COLUMNS 3
#define SPACING_X 200
#define SPACING_Y 150
#define OFFSET_X 200
#define OFFSET_Y 50
#define LABEL_OFFSET 50

#define SELECTED_COLOR sf::Color::Red

class HorseMenu : public sf::Drawable
{
public:
    HorseMenu();
    HorseMenu(const sf::Vector2f& position);
    void update(sf::Time deltaTime);
    void changeSelection(sf::Keyboard::Key key);
    int getSelected() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f position;

    sf::Font font;
    sf::Color fontColor;
    int fontSize;

    sf::Text title;
    sf::RectangleShape panel;

    std::vector<unique_ptr<Horse>> horses;
    std::vector<sf::Text> horseLabels;
    int selected;
};
#endif
