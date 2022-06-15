#ifndef GAME_INCLUDE
#define GAME_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <memory>
#include "Component.hpp"
#include "Challenge.hpp"
#include "Layer.hpp"
#include "Menu.hpp"
#include "propertyManager.hpp"

using namespace std;

#define MAX_ZLEVEL_GAME 10
#define  CENTER_SPEED_FACTOR 4
//#define  BOTTOM_SPEED_FACTOR 1
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define GVIEW_X 800
#define GVIEW_Y 600

#define  LAYER_ATMO_RECTLEFT 0
#define  LAYER_ATMO_RECTTOP 0
#define  LAYER_BATMO_RECWIDTH 800
#define  LAYER_ATMO_RECTHEIGHT 180

#define  LAYER_BOTTOM_RECTLEFT 0
#define  LAYER_BOTTOM_RECTTOP 472
#define  LAYER_BOTTOM_RECWIDTH 800
#define  LAYER_BOTTOM_RECTHEIGHT 200

#define  LAYER_TOP_RECTLEFT 0
#define  LAYER_TOP_RECTTOP 0
#define  LAYER_TOP_RECWIDTH 800
#define  LAYER_TOP_RECTHEIGHT 480

#define  LAYER_CENTER_RECTLEFT 0
#define  LAYER_CENTER_RECTTOP 280
#define  LAYER_CENTER_RECWIDTH 800
#define  LAYER_CENTER_RECTHEIGHT 250

#define  LAYER_CENTER_COORDX 0
#define  LAYER_CENTER_COORDY 285
#define  LAYER_TOP_COORDX 0
#define  LAYER_TOP_COORDY 0
#define  LAYER_ATMO_COORDX 0
#define  LAYER_ATMO_COORDY 0

#define  LAYER_BOTTOM_POSDX 0
#define  LAYER_BOTTOM_POSY 285
#define  LAYER_CENTER_POSX 0
#define  LAYER_CENTER_POSY 285
#define  LAYER_TOP_POSX 0
#define  LAYER_TOP_POSY 0
#define  LAYER_ATMO_POSX 0
#define  LAYER_ATMO_POSY 0


#define  HORSE1_POSX 400
#define  HORSE1_POSY 472
#define  HORSE2_POSX 400
#define  HORSE2_POSY 522
#define  HORSE3_POSX 400
#define  HORSE3_POSY 562

class Game
{
public:
  Game(const std::string wintTitle);
  void Run();

private:
  unsigned int actchall;
  propertyManager mdbm;
  sf::RenderWindow window;
  sf::View gameview;

/*
  std::string soundchall;
  sf::Sound sound;
  sf::SoundBuffer buffersound;
  */
  bool nosound;


/*  Layer layerBottom;
  Layer layerCenter;
  Layer layerTop;
  Layer layerAtmo;
  Layer layerFront;
*/
  Challenge chall;

  sf::Image icon;

  bool winstate;
  bool gameoverstate;
  bool gameerrorstate;

  sf::Font font;
  sf::Text testBase;

  Menu mmenu;
  void processEvent();
  void backgroundLoop();
  void render();
  void InitLayer();
  void updateMenu();
  void loadResources();
  sf::Color getColor(std::string color);
  void chgState();
  void getNextChall();
  void playSound();
  void stopSound();
};
#endif // GAME_INCLUDE
