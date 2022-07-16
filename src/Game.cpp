#include "Game.hpp"
#include "Utility.hpp"
#include "StateRace.hpp"
#include "Race.hpp"
#include "StateResult.hpp"

//listens to events (in this case, closing the window by the cross button or by the escape key)
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        handleInput(event, window);
    }
}

void Game::handleInput(sf::Event event, sf::RenderWindow &window)
{
    currentState->handleInput(event, window);
    if (event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Enter)
            changeState(GameState::STATE_RESULT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            changeState(GameState::STATE_RACE);
}

void Game::render()
{
    sf::RenderStates states;
    window.clear();
    currentState->draw(window);
    window.draw(menu);
    window.display();
}

void Game::loadResources()
{
    gameerrorstate=true;
    if(propmgr.getStatus()==0)
    {
        icon.loadFromFile("img/icon.png");
        gameerrorstate=false;
    }
}

//game loop: it is executed until exit or errors
void Game::Run()
{
    while (window.isOpen() && !gameerrorstate)
    {
        currentState->update();
        processEvents();
        render();
    }
}

State* Game::createPointer(GameState state) 
{
    if(state == GameState::STATE_RESULT)
        return new StateResult(this);
    else if (state == GameState::STATE_RACE)
        return new StateRace(this);
    else
        return nullptr;
}

void Game::changeState(GameState nextGameState) 
{
   State* nextState= createPointer(nextGameState);
    currentState->changeState(nextState);
}

State *Game::getCurrentState() const 
{
    return currentState;
}

void Game::setCurrentState(State *currentState) 
{
    this->currentState = currentState;
    std::cout<<"stato: "<<currentState;
}

bool Game::checkState(GameState state) const
{
    return currentState->getStateName() == state;
}

//class constructor: creates a SFML window and initializes objects
Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    gameoverstate = false;
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    propmgr =  PropertyManager(true);
    winstate = false;
    loadResources();
    if(!gameerrorstate)
    {
        window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());
        gameview.setCenter(GVIEW_X / 2,GVIEW_Y / 2);
        gameview.setSize(sf::Vector2f(GVIEW_X, GVIEW_Y));
        race= new Race(propmgr,gameview.getCenter());
        loadResources();
        window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());
        initMenu();
        currentState = new StateRace(this);
    }
};
