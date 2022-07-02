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
#include "Layer.hpp"
#include "Menu.hpp"
#include "PropertyManager.hpp"

using namespace std;

#define  CENTER_SPEED_FACTOR 4
//#define  BOTTOM_SPEED_FACTOR 1
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define GVIEW_X 800
#define GVIEW_Y 600


#define  HORSE1_POSX 400
#define  HORSE1_POSY 472
#define  HORSE2_POSX 400
#define  HORSE2_POSY 522
#define  HORSE3_POSX 400
#define  HORSE3_POSY 562

class Game
{
public:
  Game(std::string winTitle);
  void Run();

private:
  unsigned int actchall;
  PropertyManager propmgr;
  sf::RenderWindow window;
  sf::View gameview;

  bool mute;

  Track chall;
  Horse horsePlayer;
  sf::Clock horsePlayerDeltaTime;
  float speedX;

  sf::Image icon;

  bool winstate;
  bool gameoverstate;
  bool gameerrorstate;

  sf::Font font;
  sf::Text testBase;

  Menu menu;

  void processEvents();
  void backgroundLoop();
  void render();
  void initLayer();
  void updateMenu();
  void loadResources();
  void chgState();
  void getNextChall();
  void playSound();
  void stopSound();
  void initHorses();
  void horseMove();
};
#endif // GAME_INCLUDE
