#include "Game.hpp"
#include "Race.hpp"
#include "StateRace.hpp"
#include "StateDemo.hpp"
#include "Utility.hpp"

Game::Game(const std::string winTitle) : window(sf::VideoMode(GAME_VIEW_X, GAME_VIEW_Y, 32), winTitle)
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    gameview.setCenter(GAME_VIEW_X / 2,GAME_VIEW_Y / 2);
    gameview.setSize(GAME_VIEW_X, GAME_VIEW_Y);
    
    getDBInstance()->connect();
    gameerrorstate = getDBInstance()->getStatus() != 0;
    icon.loadFromFile(getDBInstance()->getMiscPath("icon"));
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    font.loadFromFile(getDBInstance()->getMiscPath("default_font"));
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    restart();
}

void Game::run()
{
    while (window.isOpen() && !gameerrorstate)
    {
        currentState->update();
        processEvents();
        render();
        deltaTime = deltaTimeClock.restart();
    }
}

void Game::restart()
{
    demoState = nullptr;
    horseMenuState = nullptr;
    raceState = nullptr;
    finalResultState = nullptr;
    demoState = (StateDemo*)getStatePointer(GameState::STATE_DEMO);
    currentState = demoState;
    subject = new Subject;
    observerMenuRace = new Observer(*subject);

    music.openFromFile(getDBInstance()->getMiscPath("intro_music"));
    music.setLoop(true);
    music.play();

    timeClock.restart();
    deltaTimeClock.restart();
}

//global events (not state-depending)
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
        else if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::M:
                    if(music.getVolume() > 0)
                        music.setVolume(0);
                    else
                        music.setVolume(100);
                default:
                    break;
            }
        }
        currentState->handleInput(event, window);
    }
}

void Game::render()
{
    window.clear();
    currentState->draw(window);
    window.display();
}

State* Game::getStatePointer(GameState state) 
{
    switch (state)
    {
        case GameState::STATE_DEMO:
            if(demoState == nullptr)
                demoState = new StateDemo(this);
            return demoState;
        case GameState::STATE_HORSE_MENU:
            if(horseMenuState == nullptr)
                horseMenuState = new StateHorseMenu(this);
            return horseMenuState;
        case GameState::STATE_RACE:
            if(raceState == nullptr)
                raceState = new StateRace(this);
            return raceState;
        case GameState::STATE_FINAL_RESULT:
            if(finalResultState == nullptr)
                finalResultState = new StateFinalResult(this);
            return finalResultState; 
        default:
            return nullptr;
    }
}

void Game::changeState(State *currentState) 
{
    this->currentState = currentState;
}

void Game::changeState(GameState nextGameState) 
{
    currentState = getStatePointer(nextGameState);
}

State* Game::getCurrentState() const 
{
    return currentState;
}

bool Game::checkState(GameState state) const 
{
    return currentState->getStateName() == state;
}

sf::Time Game::getTime() const
{
    return timeClock.getElapsedTime();
}

sf::Time Game::getDeltaTime() const
{
    return deltaTime;
}

sf::Texture* Game::getScreenshot() const
{
    sf::Texture* texture = new sf::Texture();
    texture->create(window.getSize().x, window.getSize().y);
    texture->update(window);
    return texture;
}
