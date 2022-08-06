#ifndef STATEDEMO_INCLUDE
#define STATEDEMO_INCLUDE

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "State.hpp"
#include "Race.hpp"
#include "Observer.hpp"

#define TITLE_TEXT_X 400
#define TITLE_TEXT_Y 100
#define TITLE_TEXT_MSG "HORSE RACING"

#define START_TEXT_X 400
#define START_TEXT_Y 550
#define START_TEXT_MSG "Press enter to play"

class Race;

class StateDemo : public State 
{
public:
    explicit StateDemo(Game* gamePtr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() const override;

private:
    Observer *observerMenuRace ;
    Subject *subject ;
    sf::Text titleText;
    sf::Text startGameText;
    Race* race;
};

#endif
