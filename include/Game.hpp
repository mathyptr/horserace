#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <memory>
//#include "MovingSprite.hpp"
#include "Track.hpp"
#include "Horse.hpp"
#include "Weather.hpp"
#include "Layer.hpp"
#include "Menu.hpp"
#include "Race.hpp"

#include "PropertyManager.hpp"
#include "AnimatedSprite.hpp"


using namespace std;

#define  CENTER_SPEED_FACTOR 4
//#define  BOTTOM_SPEED_FACTOR 1
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define GVIEW_X 800
#define GVIEW_Y 600


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
  STATE_AWARD,
  STATE_RACE,
  STATE_RESULT,
  STATE_MAIN_MENU,
  STATE_PAUSE_MENU
};


class Game
{
public:
  Game();
  Game(std::string winTitle);
  void Run();
  void changeState(GameState nextGameState);
  State* getCurrentState() const;
  void setCurrentState(State *_currentState);
  bool checkState(GameState state) const;
  Race* race;

private:
  State* currentState;

  unsigned int actchall;
  unsigned int pathlen;
  int weatherId;
  PropertyManager propmgr;
  sf::RenderWindow window;
  sf::View gameview;

  bool mute;

  Track chall;
  Horse horsePlayer,horsePlayer2,horsePlayer3;
  unsigned int horseposymax[NMAXHORSE];
  std::vector<std::shared_ptr<Weather>> weath;
  std::vector<std::shared_ptr<AnimatedSprite>> explosions;
  Animation boom;

  sf::Clock horsePlayerDeltaTime;
  sf::Clock weatherDeltaTime;
  sf::Clock weatherSpawnTimer;
  sf::Clock explosionDeltaTimer;
  float speedX;
  float weatherMoveSpeed;
  sf::Image icon;

  bool winstate;
  bool gameoverstate;
  bool gameerrorstate;

  sf::Font font;
  sf::Text testBase;
  sf::String testBottomCenter;
  sf::String testTopCenter;
  sf::Texture weathtexture;
  sf::Texture explosion;
  Menu menu;

  State* createPointer(GameState state);
  void processEvents();
  void handleInput(sf::Event event, sf::RenderWindow &window);
  void backgroundLoop();
  void render();
  void initLayer();
  void updateMenu();
  void loadResources();
  void horseMaxYCreate();
  void chgState();
  void getNextChall();
  int createProbability();
  void playSound();
  void stopSound();
  void initHorses();
  void horseMove();
  bool checkWinner();
  void createWeather();
  void drawWeather();
  void animateExplosion();
  void collision();
  void loadExplosion();
  void drawExplosions();

};
#endif // GAME_INCLUDE
