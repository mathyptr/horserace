#include "StateHorseMenu.hpp"

StateHorseMenu::StateHorseMenu(Game *gamePtr) 
{
    game = gamePtr;
    stateName = GameState::STATE_HORSE_MENU;
    horseMenu = new HorseMenu(sf::Vector2f(GAME_VIEW_X, GAME_VIEW_Y) * (float)0.5);

    background.setPosition(0, 0);
    background.setTexture(*(game->getScreenshot()));
    background.setTextureRect(sf::IntRect(0, 0, GAME_VIEW_X, GAME_VIEW_Y));
}

void StateHorseMenu::draw(sf::RenderWindow &window) 
{
    window.draw(background);
    window.draw(*horseMenu);
}

void StateHorseMenu::update() 
{
    horseMenu->update(game->getDeltaTime());
}

void StateHorseMenu::handleInput(sf::Event event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
                horseMenu->changeSelection(event.key.code);
                break;
            case sf::Keyboard::Return:
                game->changeState(GameState::STATE_RACE);
                break;
        }
    }
}

GameState StateHorseMenu::getStateName() const
{
    return stateName;
}

int StateHorseMenu::getSelectedHorseIndex() const
{
    return horseMenu->getSelected();
}
