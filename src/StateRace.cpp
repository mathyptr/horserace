#include "StateRace.hpp"
#include "Game.hpp"

StateRace::StateRace(Game *gamePtr) 
{
    testBottomCenter="";
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
    testBottomCenter="";
    if(game->race->checkWinner())
        testBottomCenter=TEST_BOTTOM_CENTER_GAME;
     game->race->update();
     game->menu.UpdateText("Life: "+std::to_string(game->race->horsePlayer.getLife()),"",testBottomCenter,"","",game->race->track->getName()+"\nMoney: "+std::to_string(game->race->horsePlayer.getMoney()));
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
  if (event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Up){
            game->race->getNextTrack();
            game->initMenu();
        }
}

GameState StateRace::getStateName() const
{
    return stateName;
}

void StateRace::playMusic() 
{
    music.play();
}