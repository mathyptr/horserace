#include "HorseMenu.hpp"
#include "Utility.hpp"
#include "PropertyManager.hpp"

HorseMenu::HorseMenu()
{

}

HorseMenu::HorseMenu(const sf::Vector2f& position)
{
    font.loadFromFile("font/default_font.ttf");
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    panel = sf::RectangleShape(sf::Vector2f(MENU_SIZE_X, MENU_SIZE_Y));
    panel.setFillColor(MENU_BG_COLOR);
    panel.setOrigin(panel.getLocalBounds().width / 2, panel.getLocalBounds().height / 2);
    panel.setPosition(position);

    title = sf::Text(TITLE_MSG, font, fontSize);
    title.setColor(fontColor);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(TITLE_X, TITLE_Y);
    title.setScale(1.25, 1.25);

    selected = 0;
    for (int i = 0; i < getDBInstance()->getHorseCount(); i++)
    {
        horses.push_back(std::make_unique<Horse>(i + 1, sf::Vector2f(25, 25), sf::Vector2f(position.x + (i % COLUMNS) * SPACING_X - OFFSET_X, position.y + (i / COLUMNS) * SPACING_Y - OFFSET_Y), 10));
        horses[i]->setScale(1.5, 1.5);

        horseLabels.push_back(sf::Text(horses[i]->getName(), font, fontSize));
        horseLabels[i].setColor(fontColor);
        horseLabels[i].setOrigin(horseLabels[i].getLocalBounds().width / 2, horseLabels[i].getLocalBounds().height / 2);
        horseLabels[i].setPosition(horses[i]->getPosition() + sf::Vector2f(0, LABEL_OFFSET));
    }
    horseLabels[selected].setColor(SELECTED_COLOR);
}

void HorseMenu::update(sf::Time deltaTime)
{
    horses[selected]->update(deltaTime);
}

void HorseMenu::changeSelection(sf::Keyboard::Key key)
{
    horseLabels[selected].setColor(fontColor);
    switch (key)
    {
        case sf::Keyboard::Left:
            selected = (selected - 1 + horses.size()) % horses.size();
            break;
        case sf::Keyboard::Right:
            selected = (selected + 1) % horses.size();
            break;
    }
    horseLabels[selected].setColor(SELECTED_COLOR);
}

int HorseMenu::getSelected() const
{
    return selected;
}

void HorseMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(panel, states);
    target.draw(title, states);

    for (int i = 0; i < horses.size(); i++)
    {
        horses[i]->draw(target, states, 10);
        target.draw(horseLabels[i], states);
    }
}
