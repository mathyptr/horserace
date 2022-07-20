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
    if(game->getDemo())
        testBottomCenter="Press key to play";
    else
        testBottomCenter="";
    if(game->race->checkWinner())
        testBottomCenter=TEST_BOTTOM_CENTER_GAME;
    game->race->update();
    game->menu.UpdateText("Life: "+std::to_string(game->race->horsePlayer->getLife()),"",testBottomCenter,"","",game->race->track->getName()+"\nMoney: "+std::to_string(game->race->horsePlayer->getMoney()));
    game->race->setDemo(game->getDemo());
    if(game->getDemo()&&game->race->checkWinner()){
            game->race->getNextTrack();
            game->initMenu();
    }
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
  if (event.type == sf::Event::KeyReleased)
      if(game->race->checkWinner())
      {
          game->race->setDemo(false);
          if (event.key.code == sf::Keyboard::Enter)
              game->changeState(GameState::STATE_RESULT);
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
