#include "Game.hpp"
#include "Utility.hpp"
#include "StateRace.hpp"
#include "Race.hpp"
#include "StateResult.hpp"

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        currentState->handleInput(event, window);
    }
}

unsigned int Game::getCurrentTrack()
{
    return race->getCurrentIndex();
}

void Game::render()
{
    sf::RenderStates states;
    window.clear();
    currentState->draw(window);
    window.draw(menu);
    window.display();
}

void Game::initMenu()
{
    currentTrack=getCurrentTrack();
    font.loadFromFile(propmgr.getTrackProperty(currentTrack, FONT_FILE));
    std::string fontSize= propmgr.getTrackProperty(currentTrack, FONT_SIZE);
    std::string fontColor= propmgr.getTrackProperty(currentTrack, FONT_COLOR);
    testBase.setFont(font);
    testBase.setCharacterSize(std::stoi(fontSize));
    testBase.setColor(Utility::getColor(fontColor));
    menu.Init(testBase, gameview.getCenter());
}

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
    demo=d;
}

bool Game::getDemo()
{
    return demo;
}

Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    gameview.setCenter(GVIEW_X / 2,GVIEW_Y / 2);
    gameview.setSize(sf::Vector2f(GVIEW_X, GVIEW_Y));
    
    propmgr = PropertyManager(true);
    gameerrorstate=true;
    if(propmgr.getStatus() == 0)
    {
        icon.loadFromFile("img/icon.png");
        gameerrorstate=false;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    race = new Race(propmgr, gameview.getCenter());
    currentState = new StateRace(this);
    currentTrack = getCurrentTrack();
    gameoverstate = false;
    winstate = false;
    demo = false;
    initMenu();
};
