#ifndef STATERACE_INCLUDE
#define STATERACE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Game.hpp"
#include "State.hpp"
#include "StateRace.hpp"

/*
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

*/


class StateRace : public State {
public:
    explicit StateRace(Game* gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    void playMusic() override ;
    GameState getStateName() override;
};

#endif // STATERACE_INCLUDE
