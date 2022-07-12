#include "StateRace.hpp"
#include "Game.hpp"

StateRace::StateRace(Game *gamePtr) 
{
    game = gamePtr;
/*    try {
        if(!music.openFromFile("../SoundEffects/Route.wav")){
            throw std::runtime_error("File not found: ../SoundEffects/Route.wav");
        }
        music.setLoop(true);
        music.setVolume(20.f);
        music.play();
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }*/
    stateName = GameState ::STATE_RACE;
}

void StateRace::changeState(State* nextState) 
{

    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    /*  auto tmp = dynamic_cast<StatePauseMenu *>(game->getCurrentState());
    if (tmp != nullptr) {
        tmp->setPreviousState(tmpState);
        music.pause();
    } else{
        music.stop();
        delete tmpState;
    }*/
    delete tmpState;
}

void StateRace::draw(sf::RenderWindow &window) 
{
    //window.draw(game->map);
    game->race->render(window);
//    game->player.draw(window,game->player.getState());
//    game->map.drawNPC(window);
//    game->map.drawUI(window);
}

void StateRace::update() 
{
      game->race->update();
//    game->player.move();
//    game->map.checkCollisions(game->player);
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
   // game->race->horseMove();
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
