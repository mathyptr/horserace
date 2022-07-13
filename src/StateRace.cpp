#include "StateRace.hpp"
#include "Game.hpp"

StateRace::StateRace(Game *gamePtr) 
{
    game = gamePtr;
    stateName = GameState ::STATE_RACE;
}

void StateRace::changeState(State* nextState) 
{
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;
}

void StateRace::draw(sf::RenderWindow &window) 
{
    game->race->render(window);
}

void StateRace::update() 
{
      game->race->update();
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
  if (event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Up)
            game->race->getNextTrack();
}

GameState StateRace::getStateName() const
{
    return stateName;
}

void StateRace::playMusic() 
{
    music.play();
}
