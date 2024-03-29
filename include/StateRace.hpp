#ifndef STATERACE_INCLUDE
#define STATERACE_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Game.hpp"
#include "State.hpp"
#include "Race.hpp"
#include "RankingMenu.hpp"
#include "RaceMenu.hpp"
#include "Observer.hpp"

#define HORSE_IN_RACE 3

class Race;

class StateRace : public State 
{
public:
    explicit StateRace(Game* gamePtr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() const override;
    int globalRanking[HORSE_IN_RACE];
    int* getHorseNumbers() const;
    void getGlobalRanking();

private:
    Race* race;
    RaceMenu* raceMenu;
    RankingMenu* rankingMenu;
    Subject *subject ;
    Observer *observerMenuRace ;
    bool msg;
    bool typeW=false;
    int* horseNumbers;
};

#endif // STATERACE_INCLUDE
