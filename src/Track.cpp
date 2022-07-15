#include "Track.hpp"
#include "Utility.hpp"

Track::Track()
{

}

Track::Track(PropertyManager propManager, std::string name)
{
    zlevelAct=0;
    zlevelMax=0;
    this->name = name;
    propmgr = propManager;
    loadResources();
    initLayer();
}

void Track::loadResources()
{
    toppic.loadFromFile(propmgr.getTrackProperty(name, TOP_PIC));
    bottompic.loadFromFile(propmgr.getTrackProperty(name, BOTTOM_PIC));
    centerpic.loadFromFile(propmgr.getTrackProperty(name, CENTER_PIC));
    atmopic.loadFromFile(propmgr.getTrackProperty(name, SKY_PIC));
    frontpic.loadFromFile(propmgr.getTrackProperty(name, FRONT_PIC));
    soundchall = propmgr.getTrackProperty(name, SOUND);

   /* font.loadFromFile(propmgr.getTrackProperty(name, FONT_FILE));
    std::string fontSize = propmgr.getTrackProperty(name, FONT_SIZE);
    std::string fontColor = propmgr.getTrackProperty(name, FONT_COLOR);

    testBase.setFont(font);
    testBase.setCharacterSize(std::stoi(fontSize));
    testBase.setColor(Utility::getColor(fontColor));*/

    if (!buffersound.loadFromFile(soundchall))
        nosound = true;
}

void Track::initLayer()
{
    unsigned int zlevel;
    zlevel=1;
    layerTop = new Layer(toppic,TOP_SPEED_FACTOR,sf::IntRect(LAYER_TOP_RECTLEFT, LAYER_TOP_RECTTOP, LAYER_TOP_RECWIDTH,LAYER_TOP_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_TOP_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    zlevel++;
    layerAtmo =new Layer(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(LAYER_ATMO_RECTLEFT, LAYER_ATMO_RECTTOP, LAYER_ATMO_RECWIDTH,LAYER_ATMO_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_ATMO_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    zlevel++;
    layerCenter =new Layer(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(LAYER_CENTER_RECTLEFT, LAYER_CENTER_RECTTOP, LAYER_CENTER_RECWIDTH, LAYER_CENTER_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_CENTER_POSX),static_cast<float>(LAYER_CENTER_POSY)),zlevel);
    zlevel++;
    layerBottom =new Layer(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(LAYER_BOTTOM_RECTLEFT, LAYER_BOTTOM_RECTTOP, LAYER_BOTTOM_RECWIDTH,LAYER_BOTTOM_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_BOTTOM_POSX),static_cast<float>(LAYER_BOTTOM_POSY)),zlevel);
    layerFront =new Layer(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(LAYER_FRONT_RECTLEFT, LAYER_FRONT_RECTTOP, LAYER_FRONT_RECWIDTH,LAYER_FRONT_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_FRONT_POSX),static_cast<float>(LAYER_FRONT_POSY)),ZLEVELMAX);

    zlevelAct=0;

    layerAtmo->setPosition(LAYER_ATMO_POSX,LAYER_ATMO_POSY);
    layerTop->setPosition(LAYER_TOP_POSX,LAYER_TOP_POSY);
    layerCenter->setPosition(LAYER_CENTER_POSX,LAYER_CENTER_POSY);
    layerBottom->setPosition(LAYER_BOTTOM_POSX,LAYER_BOTTOM_POSY);
    layerFront->setPosition(LAYER_FRONT_POSX,LAYER_FRONT_POSY);

}

void Track:: move(float speed)
{
    layerBottom->move(speed,0);
    layerCenter->move(speed,0);
    layerTop->move(speed,0);
    layerAtmo->move(speed,0);
    layerFront->move(speed,0);
}


void Track:: playSound()
{
    sound.setBuffer(buffersound);
    sound.setLoop(true);
    sound.play();
}

void Track:: stopSound()
{
    sound.stop();
}

void Track::setZLevel(int z)
{
    zlevelAct = z;
}

unsigned int Track::getZLevel()
{
    return zlevelAct;
}

void Track::incZLevel()
{
    zlevelAct = (zlevelAct + 1) % ZLEVELMAX;
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
    layerFront->draw(target, states, actzlevel);

    //incZLevel();
}
