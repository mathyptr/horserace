#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Menu.hpp"
#include "HorseMenu.hpp"
#include "Race.hpp"
#include "PropertyManager.hpp"

#define GAME_VIEW_X 800
#define GAME_VIEW_Y 600

class HorseMenu;

class State;
enum class GameState
{
    STATE_RACE,
    STATE_RESULT
};

class Game
{
public:
    Game(std::string winTitle);
    void run();
    void changeState(GameState nextGameState);
    void setCurrentState(State *_currentState);
    bool checkState(GameState state) const;
    void setDemo(bool d);
    bool getDemo() const;
    bool getMute() const;
    sf::Time getTime() const;
    sf::Time getDeltaTime() const;
    State* getCurrentState() const;
    Race* race;
    Menu* menu;
    HorseMenu* horseMenu;

private:
    sf::RenderWindow window;
    sf::View gameview;
    sf::Image icon;

    sf::Clock timeClock;
    sf::Clock deltaTimeClock;

    bool mute;
    bool winstate;
    bool gameoverstate;
    bool gameerrorstate;
    bool demo;
    State* currentState;
    State* createPointer(GameState state);
    void processEvents();
    void render();
 
};
#endif // GAME_INCLUDE
