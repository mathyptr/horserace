#include "HorseMenu.hpp"
#include "Utility.hpp"
#include "PropertyManager.hpp"

HorseMenu::HorseMenu()
{

}

HorseMenu::HorseMenu(const sf::Vector2f& position, Game* parent)
{
    this->parent = parent;

    font.loadFromFile("font/default_font.ttf");
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    panel = sf::RectangleShape(sf::Vector2f(600, 400));
    panel.setFillColor(sf::Color::Color(220, 220, 220, 220));
    panel.setOrigin(panel.getLocalBounds().width / 2, panel.getLocalBounds().height / 2);
    panel.setPosition(position);

    title = sf::Text("Choose your horse", font, fontSize);
    title.setColor(fontColor);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(400, 150);
    title.setScale(1.25, 1.25);

    selected = 0;
    for (int i = 0; i < getDBInstance()->getHorseCount(); i++)
    {
        horses.push_back(std::make_unique<Horse>(i + 1, sf::Vector2f(25, 25), sf::Vector2f(position.x + (i % 3) * 200 - 200, position.y + (i / 3) * 150 - 50), 10));
        horses[i]->setScale(1.5, 1.5);

        horseLabels.push_back(sf::Text(horses[i]->getName(), font, fontSize));
        horseLabels[i].setColor(fontColor);
        horseLabels[i].setOrigin(horseLabels[i].getLocalBounds().width / 2, horseLabels[i].getLocalBounds().height / 2);
        horseLabels[i].setPosition(horses[i]->getPosition() + sf::Vector2f(0, 50));
    }
    

    setPosition(position);
}

/* void HorseMenu::updateText(const sf::String bottomL, const sf::String topR, const sf::String bottomC, const sf::String topC, const sf::String bottomR, const sf::String topL)
{
    topLeftText.setString(topL);
    bottomLeftText.setString(bottomL);
    topCenterText.setString(topC);
    bottomCenterText.setString(bottomC);
    topRightText.setString(topR);
    bottomRightText.setString(bottomR);
} */

sf::Vector2f HorseMenu::getPosition() const
{
    return position;
}

void HorseMenu::setPosition(sf::Vector2f pos)
{
    position = pos;
/*     topLeftText.setPosition(position + TopLeftPosition);
    bottomLeftText.setPosition(position + BottomLeftPosition);
    topCenterText.setPosition(position + TopCenterPosition);
    bottomCenterText.setPosition(position + BottomCenterPosition);
    topRightText.setPosition(position + TopRightPosition);
    bottomRightText.setPosition(position + BottomRightPosition); */
}

void HorseMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.draw(topLeftText/* , states */);
    //target.draw(bottomLeftText/* , states */);
    //target.draw(topCenterText/* , states */);
    //target.draw(bottomCenterText/* , states */);
    //target.draw(topRightText/* , states */);
    //target.draw(bottomRightText/* , states */);

    target.draw(panel, states);
    target.draw(title, states);

    for (int i = 0; i < getDBInstance()->getHorseCount(); i++)
    {
        horses[i]->draw(target, states, 10);
        
        if(i == selected)
            horses[i]->update(parent->getDeltaTime() * (float)10);

        target.draw(horseLabels[i], states);
    }
}
