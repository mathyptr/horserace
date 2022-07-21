#include "Track.hpp"

Track::Track(std::string name)
{
    this->name = name;
    finalLineState=false;
    loadResources();
    initLayer();
}

void Track::loadResources()
{
    toppic.loadFromFile(getDBInstance()->getTrackProperty(name, TOP_PIC));
    bottompic.loadFromFile(getDBInstance()->getTrackProperty(name, BOTTOM_PIC));
    centerpic.loadFromFile(getDBInstance()->getTrackProperty(name, CENTER_PIC));
    atmopic.loadFromFile(getDBInstance()->getTrackProperty(name, SKY_PIC));
    finalLinepic.loadFromFile(getDBInstance()->getTrackProperty(name, FINALLINE_PIC));
    frontpic.loadFromFile(getDBInstance()->getTrackProperty(name, FRONT_PIC));
    soundPath = getDBInstance()->getTrackProperty(name, SOUND);
    if (!buffersound.loadFromFile(soundPath))
        nosound = true;
}

void Track::initLayer()
{
    finalLineState=false;
    unsigned int zlevel;
    zlevel=1;
    layerTop = std::make_unique<Layer>(toppic,TOP_SPEED_FACTOR,sf::IntRect(LAYER_TOP_RECTLEFT, LAYER_TOP_RECTTOP, LAYER_TOP_RECWIDTH,LAYER_TOP_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_TOP_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    zlevel++;
    layerAtmo = std::make_unique<Layer>(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(LAYER_ATMO_RECTLEFT, LAYER_ATMO_RECTTOP, LAYER_ATMO_RECWIDTH,LAYER_ATMO_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_ATMO_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    zlevel++;
    layerCenter = std::make_unique<Layer>(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(LAYER_CENTER_RECTLEFT, LAYER_CENTER_RECTTOP, LAYER_CENTER_RECWIDTH, LAYER_CENTER_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_CENTER_POSX),static_cast<float>(LAYER_CENTER_POSY)),zlevel);
    zlevel++;
    layerBottom = std::make_unique<Layer>(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(LAYER_BOTTOM_RECTLEFT, LAYER_BOTTOM_RECTTOP, LAYER_BOTTOM_RECWIDTH,LAYER_BOTTOM_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_BOTTOM_POSX),static_cast<float>(LAYER_BOTTOM_POSY)),zlevel);
    layerFinalLine = std::make_unique<Layer>(finalLinepic,BOTTOM_SPEED_FACTOR,sf::IntRect(LAYER_BOTTOM_RECTLEFT, LAYER_BOTTOM_RECTTOP, LAYER_BOTTOM_RECWIDTH,LAYER_BOTTOM_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_BOTTOM_POSX),static_cast<float>(LAYER_BOTTOM_POSY)),zlevel);
    layerFront = std::make_unique<Layer>(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(LAYER_FRONT_RECTLEFT, LAYER_FRONT_RECTTOP, LAYER_FRONT_RECWIDTH,LAYER_FRONT_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_FRONT_POSX),static_cast<float>(LAYER_FRONT_POSY)),ZLEVELMAX);

    layerAtmo->setPosition(LAYER_ATMO_POSX,LAYER_ATMO_POSY);
    layerTop->setPosition(LAYER_TOP_POSX,LAYER_TOP_POSY);
    layerCenter->setPosition(LAYER_CENTER_POSX,LAYER_CENTER_POSY);
    layerBottom->setPosition(LAYER_BOTTOM_POSX,LAYER_BOTTOM_POSY);
    layerFinalLine->setPosition(LAYER_BOTTOM_POSX,LAYER_BOTTOM_POSY);
    layerFront->setPosition(LAYER_FRONT_POSX,LAYER_FRONT_POSY);
}

/* void Track:: move(float speed)
{
    layerBottom->move(speed,0);
    if(finalLineState)
        layerFinalLine->move(speed,0);
    layerCenter->move(speed,0);
    layerTop->move(speed,0);
    layerAtmo->move(speed,0);
    layerFront->move(speed,0);
} */

void Track::move(sf::Time sec)
{
    layerBottom->update(sec);
    if(finalLineState)
        layerFinalLine->update(sec);
    layerCenter->update(sec);
    layerTop->update(sec);
    layerAtmo->update(sec);
    layerFront->update(sec);
}

void Track::playSound()
{
    sound.setBuffer(buffersound);
    sound.setLoop(true);
    sound.play();
}

void Track::stopSound()
{
    sound.stop();
}

void Track::setfinalLineState()
{
    finalLineState=true;
}

void Track::setName(std::string trackName)
{
    name = trackName;
}

std::string Track::getName()
{
    return name;
}

void Track::draw(sf::RenderTarget &target, sf::RenderStates &states, int actzlevel)
{
    layerTop->draw(target, states, actzlevel);
    layerAtmo->draw(target, states, actzlevel);
    layerCenter->draw(target, states, actzlevel);
    layerBottom->draw(target, states, actzlevel);
    if(finalLineState)
        layerFinalLine->draw(target, states, actzlevel);
    layerFront->draw(target, states, actzlevel);
}
