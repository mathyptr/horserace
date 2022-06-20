#ifndef CHALLENGE_INCLUDE
#define CHALLENGE_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Layer.hpp"
#include "propertyManager.hpp"


#define  CENTER_SPEED_FACTOR 4
//#define  BOTTOM_SPEED_FACTOR 1
#define  BOTTOM_SPEED_FACTOR 2
#define  TOP_SPEED_FACTOR 10
#define  ATMO_SPEED_FACTOR 20
#define  FRONT_SPEED_FACTOR 1

#define ZLEVELMAX 10

class Challenge
{
public:
    Challenge();
    void init(propertyManager propmanager) ;
    void playSound();
    void stopSound();
    void setLevel(unsigned int lev);
    void incLevel();
    unsigned int getLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates &states,unsigned int actzlevel);
private:
    void loadResources();
    void initLayer();

    unsigned int zlevelAct;
    unsigned int zlevelMax;
    unsigned int zlevel;

    sf::Color getColor(std::string color);

    sf::Texture     texture;
    sf::Vector2f    position;

    sf::Texture centerpic;
    sf::Texture bottompic;
    sf::Texture toppic;
    sf::Texture atmopic;
    sf::Texture frontpic;


    Layer layerBottom;
    Layer layerCenter;
    Layer layerTop;
    Layer layerAtmo;
    Layer layerFront;

    std::string soundchall;
    sf::Sound sound;
    sf::SoundBuffer buffersound;
    bool nosound;

    sf::Font font;
    sf::Text testBase;

    propertyManager propmgr;

    unsigned int    speedFactor;
};
#endif
