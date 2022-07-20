#ifndef CHALLENGE_INCLUDE
#define CHALLENGE_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Layer.hpp"
#include "PropertyManager.hpp"

#define  CENTER_SPEED_FACTOR 4
//#define  BOTTOM_SPEED_FACTOR 1
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define ZLEVELMAX 10

#define  LAYER_ATMO_RECTLEFT 0
#define  LAYER_ATMO_RECTTOP 0
#define  LAYER_ATMO_RECWIDTH 800
#define  LAYER_ATMO_RECTHEIGHT 180

#define  LAYER_TOP_RECTLEFT 0
#define  LAYER_TOP_RECTTOP 0
#define  LAYER_TOP_RECWIDTH 800
#define  LAYER_TOP_RECTHEIGHT 480

#define  LAYER_CENTER_RECTLEFT 0
#define  LAYER_CENTER_RECTTOP 280
#define  LAYER_CENTER_RECWIDTH 800
#define  LAYER_CENTER_RECTHEIGHT 250

#define  LAYER_BOTTOM_RECTLEFT 0
#define  LAYER_BOTTOM_RECTTOP 472
#define  LAYER_BOTTOM_RECWIDTH 800
#define  LAYER_BOTTOM_RECTHEIGHT 200

#define  LAYER_ATMO_POSX 0
#define  LAYER_ATMO_POSY 0
#define  LAYER_TOP_POSX 0
#define  LAYER_TOP_POSY 0
#define  LAYER_CENTER_POSX 0
#define  LAYER_CENTER_POSY 285
#define  LAYER_BOTTOM_POSX 0
#define  LAYER_BOTTOM_POSY 472
#define  LAYER_FRONT_POSX 0
#define  LAYER_FRONT_POSY 472

#define  LAYER_FRONT_RECTLEFT 0
#define  LAYER_FRONT_RECTTOP 472
#define  LAYER_FRONT_RECWIDTH 800
#define  LAYER_FRONT_RECTHEIGHT 200


class Track
{
public:
    Track();
    Track(PropertyManager propManager, std::string name);
    /* void move(float speed); */
    void move(sf::Time sec);
    void playSound();
    void stopSound();
    void setZLevel(int z);
    unsigned int getZLevel();
    void setName(std::string trackName);
    std::string getName();
    void setfinalLineState();
    void draw(sf::RenderTarget &target, sf::RenderStates &states, int actzlevel);
    //~Track();

private:
    void loadResources();
    void initLayer();
    unsigned int zlevelAct;
    unsigned int zlevelMax;
    bool finalLineState;
    std::string name;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Texture centerpic;
    sf::Texture bottompic;
    sf::Texture toppic;
    sf::Texture atmopic;
    sf::Texture frontpic;
    sf::Texture finalLinepic;
    unique_ptr<Layer> layerBottom;
    unique_ptr<Layer> layerCenter;
    unique_ptr<Layer> layerTop;
    unique_ptr<Layer> layerAtmo;
    unique_ptr<Layer> layerFront;
    unique_ptr<Layer> layerFinalLine;
    std::string soundchall;
    sf::Sound sound;
    sf::SoundBuffer buffersound;
    bool nosound;
    PropertyManager propmgr;
    unsigned int speedFactor;
};
#endif
