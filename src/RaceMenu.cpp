#include "RaceMenu.hpp"

RaceMenu::RaceMenu()
{

}

RaceMenu::RaceMenu(const sf::Vector2f& position)
{
    font.loadFromFile("font/default_font.ttf");
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    trackText = sf::Text("Track", font, fontSize);
    trackText.setColor(fontColor);
    trackText.setPosition(TRACK_TEXT_POSITION);
    lifeText = sf::Text("Life", font, fontSize);
    lifeText.setColor(fontColor);
    lifeText.setPosition(LIFE_TEXT_POSITION);
    moneyText = sf::Text("Money", font, fontSize);
    moneyText.setColor(fontColor);
    moneyText.setPosition(MONEY_TEXT_POSITION);
}

void RaceMenu::update(sf::Time deltaTime)
{
    
}

void RaceMenu::setTrackText(std::string text)
{
    trackText.setString(text);
}

void RaceMenu::setLifeText(std::string text)
{
    lifeText.setString(text);
}

void RaceMenu::setMoneyText(std::string text)
{
    moneyText.setString(text);
}

void RaceMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(trackText, states);
    target.draw(lifeText, states);
    target.draw(moneyText, states);
}
