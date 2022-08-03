#include "StateDemo.hpp"

StateDemo::StateDemo(Game *gamePtr) 
{
    game = gamePtr;
    stateName = GameState::STATE_DEMO;
    subject = new Subject;
    race = new Race(gamePtr, Utility::getRandom(1, getDBInstance()->getHorseCount(), HORSE_IN_RACE),subject, true);
    
    startGameText = sf::Text(START_TEXT_MSG, game->font, game->fontSize);
    startGameText.setColor(game->fontColor);
    startGameText.setOrigin(startGameText.getLocalBounds().width / 2, startGameText.getLocalBounds().height / 2);
    startGameText.setPosition(sf::Vector2f(START_TEXT_X, START_TEXT_Y));

    titleText = sf::Text(TITLE_TEXT_MSG, game->font, game->fontSize * 2);
    titleText.setColor(game->fontColor);
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(sf::Vector2f(TITLE_TEXT_X, TITLE_TEXT_Y));
}

void StateDemo::draw(sf::RenderWindow &window) 
{
    race->render(window);
    window.draw(titleText);
    window.draw(startGameText);
}

void StateDemo::update() 
{
    race->update(game->getDeltaTime());
    if(race->horsePlayerFinished())
        race->loadNextTrack(true);
}

void StateDemo::handleInput(sf::Event event, sf::RenderWindow &window)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            titleText.setString("");
            startGameText.setString("");
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            game->changeState(GameState::STATE_HORSE_MENU);
        }
    }
}

GameState StateDemo::getStateName() const
{
    return stateName;
}
