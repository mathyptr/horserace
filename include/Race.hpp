#ifndef RACE_INCLUDE
#define RACE_INCLUDE
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
#define NCHALL 5

class Race
{
public:
  Race(const sf::Vector2f& pos);
  void update();
  void render(sf::RenderTarget &target);
  bool checkWinner();
  void playSound();
  void stopSound();
  void initHorses();
  void getNextTrack();
  void horseMove(bool go);
  sf::String result();
  std::string finalResult();
  void collision();
  std::string order( map <std::string,float> results);
  unsigned int getCurrentIndex();
  void setDemo(bool state);
  unique_ptr<Horse> horsePlayer, horsePlayer2,horsePlayer3;
  unique_ptr<Track> track;
  int weatherId;
  unsigned int character = 0;

private:
  unsigned int currentTrackIndex;
  unsigned int pathlen;
  sf::Clock timer;
  sf::Vector2f posgameview;
  bool mute;
  bool demo;
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
  bool winstate;
  bool gameoverstate;
  bool gameerrorstate;
  sf::Texture weathtexture;
  sf::Texture explosion;
  bool checkFinalLine();
  void loadResources();
  void horseMaxYCreate();
  int createProbability();
  void createWeather();
  void drawWeather(sf::RenderTarget &target);
  void animateExplosion();
  void loadExplosion();
  void drawExplosions(sf::RenderTarget &target);
};
#endif // GAME_INCLUDE
