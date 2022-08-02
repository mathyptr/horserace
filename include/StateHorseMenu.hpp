#ifndef STATEHORSEMENU_INCLUDE
#define STATEHORSEMENU_INCLUDE

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "State.hpp"

class HorseMenu;

class StateHorseMenu : public State 
{
public:
    explicit StateHorseMenu(Game* gamePtr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() const override;
    int getSelectedHorseIndex() const;

private:
    HorseMenu* horseMenu;
    sf::Sprite background;
};
#endif
