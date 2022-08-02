#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.hpp"

class Game;

enum class GameState
{
    STATE_DEMO,
    STATE_HORSE_MENU,
    STATE_RACE,
    STATE_FINAL_RESULT
};

class State 
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void handleInput(sf::Event event, sf::RenderWindow &window) = 0;
    virtual GameState getStateName() const = 0;

protected:
    Game* game;
    GameState stateName;
};
#endif
