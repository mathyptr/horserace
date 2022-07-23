#include "Game.hpp"
#include "Utility.hpp"
#include "Race.hpp"
#include "StateRace.hpp"
#include "StateResult.hpp"

Game::Game(const std::string winTitle) : window(sf::VideoMode(GAME_VIEW_X, GAME_VIEW_Y, 32), winTitle)
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    gameview.setCenter(GAME_VIEW_X / 2,GAME_VIEW_Y / 2);
    gameview.setSize(GAME_VIEW_X, GAME_VIEW_Y);
    
    gameerrorstate = true;
    getDBInstance()->connect();
    if(getDBInstance()->getStatus() == 0)
    {
        icon.loadFromFile("img/icon.png");
        gameerrorstate = false;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    race = new Race(gameview.getCenter());
    menu = new Menu(gameview.getCenter());
    currentState = new StateRace(this);
    gameoverstate = false;
    winstate = false;
    demo = true;
}

void Game::run()
{
    while (window.isOpen() && !gameerrorstate)
    {
        currentState->update();
        processEvents();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            getDBInstance()->close();
            window.close();
        }
        handleInput(event, window);
    }
}

void Game::handleInput(sf::Event event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            if(demo)
            {
                demo = false;
                delete(race);
                race = new Race(gameview.getCenter());
            }
        }
    }
    currentState->handleInput(event, window);
}

void Game::render()
{
    window.clear();
    currentState->draw(window);
    window.draw(*menu);
    window.display();
}

State* Game::createPointer(GameState state) 
{
    switch (state)
    {
        case GameState::STATE_RESULT:
            return new StateResult(this);   
        case GameState::STATE_RACE:
            return new StateRace(this);
        default:
            return nullptr;
    }
}

void Game::changeState(GameState nextGameState) 
{
    State* nextState = createPointer(nextGameState);
    currentState->changeState(nextState);
}

State *Game::getCurrentState() const 
{
    return currentState;
}

void Game::setCurrentState(State *currentState) 
{
    this->currentState = currentState;
}

bool Game::checkState(GameState state) const 
{
    return currentState->getStateName() == state;
}

void Game::setDemo(bool d)
{
    demo = d;
}

bool Game::getDemo() const
{
    return demo;
}
