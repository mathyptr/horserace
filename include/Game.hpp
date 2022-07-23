#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Menu.hpp"
#include "Race.hpp"
#include "PropertyManager.hpp"

#define GAME_VIEW_X 800
#define GAME_VIEW_Y 600

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
    State* getCurrentState() const;
    Race* race;
    Menu* menu;

private:
    sf::RenderWindow window;
    sf::View gameview;
    sf::Image icon;

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
