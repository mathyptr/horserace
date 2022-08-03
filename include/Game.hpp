#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Menu.hpp"
#include "HorseMenu.hpp"
#include "Race.hpp"
#include "PropertyManager.hpp"
#include "State.hpp"
#include "StateDemo.hpp"
#include "StateHorseMenu.hpp"
#include "StateRace.hpp"
#include "StateFinalResult.hpp"
#include "Observer.hpp"

#define GAME_VIEW_X 800
#define GAME_VIEW_Y 600

class HorseMenu;

class State;
class StateDemo;
class StateHorseMenu;
class StateRace;
class StateFinalResult;

class Game
{
public:
    Game(std::string winTitle);
    void run();
    void restart();
    void changeState(State *nextState);
    void changeState(GameState nextGameState);
    State* getCurrentState() const;
    bool checkState(GameState state) const;
    State* getStatePointer(GameState state);
    sf::Texture* getScreenshot() const;
    void getScreenshot(sf::Texture& texture) const;
    Subject *subject ;
    Observer *observerMenuRace ;

    sf::Time getTime() const;
    sf::Time getDeltaTime() const;

    sf::Music music;
    
    sf::Font font;
    int fontSize;
    sf::Color fontColor;

private:
    sf::RenderWindow window;
    sf::View gameview;
    sf::Image icon;

    sf::Clock timeClock;
    sf::Clock deltaTimeClock;
    sf::Time deltaTime;

    bool gameerrorstate;
    State* currentState;
    StateDemo* demoState;
    StateHorseMenu* horseMenuState;
    StateRace* raceState;
    StateFinalResult* finalResultState;
    void processEvents();
    void render();
};
#endif // GAME_INCLUDE
