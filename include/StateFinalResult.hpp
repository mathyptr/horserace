#ifndef STATEFINALRESULT_INCLUDE
#define STATEFINALRESULT_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Game.hpp"
#include "State.hpp"
#include "RankingMenu.hpp"

class StateFinalResult : public State 
{
public:
    explicit StateFinalResult(Game* gamePtr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() const override;

private:
    const int* ranking;
    RankingMenu* rankingMenu;
};

#endif