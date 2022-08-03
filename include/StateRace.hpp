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

    const int* getGlobalRanking() const;
    int* getHorseNumbers() const;

private:
    Race* race;
    RaceMenu* raceMenu;
    RankingMenu* rankingMenu;
    Subject *subject ;
    Observer *observerMenuRace ;
    int* horseNumbers;
    int globalRanking[HORSE_IN_RACE];
    void calculateRanking();
};

#endif // STATERACE_INCLUDE
