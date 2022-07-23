#include "Menu.hpp"
#include "Utility.hpp"
#include "PropertyManager.hpp"

Menu::Menu()
{

}

Menu::Menu(const sf::Vector2f& position)
{
    font.loadFromFile("font/default_font.ttf");
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    TopLeftPosition = sf::Vector2f(-390, -300);
    TopCenterPosition = sf::Vector2f(-120, -300);
    TopRightPosition = sf::Vector2f(240, -300);
    BottomLeftPosition = sf::Vector2f(-390, 270);
    BottomCenterPosition = sf::Vector2f(-120, 270);
    BottomRightPosition = sf::Vector2f(280, 270);

    topLeftText = sf::Text("", font, fontSize);
    topLeftText.setColor(fontColor);

    bottomLeftText = sf::Text("", font, fontSize);
    bottomLeftText.setColor(fontColor);
    
    topCenterText = sf::Text("", font, fontSize);
    topCenterText.setColor(fontColor);

    bottomCenterText = sf::Text("", font, fontSize);
    bottomCenterText.setColor(fontColor);

    topRightText = sf::Text("", font, fontSize);
    topRightText.setColor(fontColor);

    bottomRightText = sf::Text("", font, fontSize);
    bottomRightText.setColor(fontColor);

    setPosition(position);
}

void Menu::updateText(const sf::String bottomL, const sf::String topR, const sf::String bottomC, const sf::String topC, const sf::String bottomR, const sf::String topL)
{
    topLeftText.setString(topL);
    bottomLeftText.setString(bottomL);
    topCenterText.setString(topC);
    bottomCenterText.setString(bottomC);
    topRightText.setString(topR);
    bottomRightText.setString(bottomR);
}

sf::Vector2f Menu::getPosition() const
{
    return position;
}

void Menu::setPosition(sf::Vector2f pos)
{
    position = pos;
    topLeftText.setPosition(position + TopLeftPosition);
    bottomLeftText.setPosition(position + BottomLeftPosition);
    topCenterText.setPosition(position + TopCenterPosition);
    bottomCenterText.setPosition(position + BottomCenterPosition);
    topRightText.setPosition(position + TopRightPosition);
    bottomRightText.setPosition(position + BottomRightPosition);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(topLeftText/* , states */);
    target.draw(bottomLeftText/* , states */);
    target.draw(topCenterText/* , states */);
    target.draw(bottomCenterText/* , states */);
    target.draw(topRightText/* , states */);
    target.draw(bottomRightText/* , states */);
}
