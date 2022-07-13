#include "StateResult.hpp"
#include "Game.hpp"

StateResult::StateResult(Game *gamePtr) 
{
    typeWriter=false;
    game = gamePtr;
    stateName = GameState ::STATE_RESULT;
}

void StateResult::changeState(State* nextState) 
{
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
}

void StateResult::draw(sf::RenderWindow &window)
{
   game->race->render(window);
   if(typeWriter)
    game->race->finalResult();
}

void StateResult::update() {
      game->race->result();
}


void StateResult::handleInput(sf::Event event, sf::RenderWindow &window) 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        game->race->finalResult();
        typeWriter=true;
    }
}

GameState StateResult::getStateName() const
{
    return stateName;
}

void StateResult::playMusic() 
{
    music.play();
}
