#include "StateResult.hpp"
#include "Game.hpp"
#define TEST_BOTTOM_CENTER_RESULT "Press up/down key (play/total result)"

StateResult::StateResult(Game *gamePtr) 
{
    testTopCenter="";
    typeW=false;
    game = gamePtr;
    stateName = GameState ::STATE_RESULT;
}

void StateResult::changeState(State* nextState) 
{
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;

}

void StateResult::draw(sf::RenderWindow &window)
{
   game->race->render(window);
   if(typeW){
       typeWriter();
       update();
   }
}

void StateResult::typeWriter(){
    std::string str=game->race->finalResult();
    if ((timer.getElapsedTime().asSeconds() > 0.01) && game->race->character < str.length())
    {
        game->race->character++;
        if (timer.getElapsedTime() > sf::milliseconds(1)){
            testTopCenter=(str.substr(0,game->race->character)) ;
            timer.restart();
        }
    }
}

void StateResult::update() {
    game->menu.UpdateText("Life: "+std::to_string(game->race->horsePlayer->getLife()),game->race->result(),TEST_BOTTOM_CENTER_RESULT,testTopCenter,"",game->race->track->getName()+"\nMoney: "+std::to_string(game->race->horsePlayer->getMoney()));
}


void StateResult::handleInput(sf::Event event, sf::RenderWindow &window) 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        typeW=true;
        typeWriter();
    }
    if (event.type == sf::Event::KeyReleased)
    {
      if (event.key.code == sf::Keyboard::Up){
        game->race->getNextTrack();
        game->initMenu();
        game->changeState(GameState::STATE_RACE);
        }
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
