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
        handleInput(event, window);
    }
}

void Game::handleInput(sf::Event event, sf::RenderWindow &window)
{
    currentState->handleInput(event, window);
/*    if (event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Enter)
            changeState(GameState::STATE_RESULT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            changeState(GameState::STATE_RACE);
            */
}

unsigned int Game::getCurrentTrack(){
    return race->getCurrenteIndex();
}

void Game::render()
{
    sf::RenderStates states;
    window.clear();
    currentState->draw(window);
    window.draw(menu);
    window.display();
}

void Game::initMenu(){
    actchall=getCurrentTrack();
    font.loadFromFile(propmgr.getTrackProperty(actchall, FONT_FILE));
    std::string fontSize= propmgr.getTrackProperty(actchall, FONT_SIZE);
    std::string fontColor= propmgr.getTrackProperty(actchall, FONT_COLOR);
    testBase.setFont(font);
    testBase.setCharacterSize(std::stoi(fontSize));
    testBase.setColor(Utility::getColor(fontColor));
    menu.Init(testBase, gameview.getCenter());
}

void Game::loadResources()
{
    gameerrorstate=true;
    if(propmgr.getStatus()==0)
    {
        actchall=getCurrentTrack();
        icon.loadFromFile("img/icon.png");
        gameerrorstate=false;
    }
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

State* Game::createPointer(GameState state) {
    if(state == GameState::STATE_RESULT)
        return new StateResult(this);   
    else if (state == GameState::STATE_RACE)
        return new StateRace(this);
    else
        return nullptr;
}


void Game::changeState(GameState nextGameState) {
   State* nextState= createPointer(nextGameState);
    currentState->changeState(nextState);
}


State *Game::getCurrentState() const {
    return currentState;
}

void Game::setCurrentState(State *_currentState) {
   currentState = _currentState;
}

bool Game::checkState(GameState state) const {
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

//class constructor: creates a SFML window and initializes objects
Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    actchall=1;
    gameoverstate=false;
    demo=false;
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    propmgr =  PropertyManager(true);
    winstate=false;
    if(!gameerrorstate)
    {
        gameview.setCenter(GVIEW_X / 2,GVIEW_Y / 2);
        gameview.setSize(sf::Vector2f(GVIEW_X, GVIEW_Y));
        race= new Race(propmgr,gameview.getCenter());
        loadResources();
        window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());
        initMenu();
        currentState = new StateRace(this);
    }
};
