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


class Challenge : public sf::Drawable
{
public:
    Challenge();
    void Init(propertyManager dbm) ;
    void playSound();
    void stopSound();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void loadResources();
    void InitLayer();

    unsigned int zlevel_Act;
    unsigned int zlevel_Max;
    sf::Color getColor(std::string color);

    sf::Texture     mtexture;
    sf::Vector2f    mposition;

    sf::Texture centerpic;
    sf::Texture bottompic;
    sf::Texture toppic;
    sf::Texture atmopic;
    sf::Texture frontpic;


    Component       mTile;
    Component       mTileR;
    Component       mTileL;


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

    propertyManager mdbm;

    unsigned int    mspeedFactor;
};
#endif
