#ifndef STATE_INCLUDE
#define STATE_INCLUDE


#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.hpp"


class State {
public:
    virtual ~State() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void changeState(State* nextState) = 0;
    virtual void update() = 0;
    virtual void handleInput(sf::Event event, sf::RenderWindow &window) = 0;
    virtual GameState getStateName() = 0;
    virtual void playMusic() = 0;
    GameState stateName;
protected:
    Game* game;
    sf::Music music;
};

#endif
