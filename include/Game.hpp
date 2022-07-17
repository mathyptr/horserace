#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <memory>
#include "Track.hpp"
#include "Horse.hpp"
#include "Weather.hpp"
#include "Layer.hpp"
#include "Menu.hpp"
#include "Race.hpp"
#include "PropertyManager.hpp"
#include "AnimatedSprite.hpp"

using namespace std;

#define GVIEW_X 800
#define GVIEW_Y 600

#define  CENTER_SPEED_FACTOR 4
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define  HORSEZLEVELMIN 5
#define  HORSEZLEVELMAX 8
#define  HORSE1_POSX 400
#define  HORSE1_POSY 472
#define  HORSE2_POSX 400
#define  HORSE2_POSY 522
#define  HORSE3_POSX 400
#define  HORSE3_POSY 562
#define NMAXHORSE 3
#define NMAXPROB 10

class State;
enum class GameState
{
    STATE_RACE,
    STATE_RESULT
};

class Game
{
public:
    Game();
    Game(std::string winTitle);
    void Run();
    void initMenu();
    void changeState(GameState nextGameState);
    void setCurrentState(State *_currentState);
    bool checkState(GameState state) const;
    State* getCurrentState() const;
    Race* race;
    Menu menu;
    void setDemo(bool d);
    bool getDemo();

private:
    unsigned int getCurrentTrack();
    unsigned int currentTrack;
    PropertyManager propmgr;
    sf::RenderWindow window;
    sf::View gameview;

    sf::Image icon;
    sf::Font font;
    sf::Text testBase;
    bool mute;
    bool winstate;
    bool gameoverstate;
    bool gameerrorstate;
    bool demo;
    State* createPointer(GameState state);
    State* currentState;
    void processEvents();
    void handleInput(sf::Event event, sf::RenderWindow &window);
    void render();
 
};
#endif // GAME_INCLUDE
