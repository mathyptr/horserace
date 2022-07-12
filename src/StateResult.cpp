#include "StateResult.h"
#include "Game.hpp"


StateResult::StateResult(Game *gamePtr) {
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
    stateName = GameState ::STATE_RESULT;
}

void StateResult::changeState(State* nextState) {

    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    /*auto tmp = dynamic_cast<StatePauseMenu *>(game->getCurrentState());
    if (tmp != nullptr) {
        tmp->setPreviousState(tmpState);
        music.pause();
    } else{
        music.stop();
        delete tmpState;
    }*/
}

void StateResult::draw(sf::RenderWindow &window) {
    //window.draw(game->map);
   game->race->render(window);
//    game->player.draw(window,game->player.getState());
//    game->map.drawNPC(window);
//    game->map.drawUI(window);
}

void StateResult::update() {

      game->race->result();
//    game->player.move();
//    game->map.checkCollisions(game->player);
}



void StateResult::handleInput(sf::Event event, sf::RenderWindow &window) {
    // game->race->horseMove();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            game->race->finalResult();

}

GameState StateResult::getStateName() {
    return stateName;
}

void StateResult::playMusic() {
    music.play();
}