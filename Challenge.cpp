#include "Challenge.hpp"


Challenge::Challenge()
{
    zlevelAct=0;
    zlevelMax=0;
}

void Challenge::init(propertyManager propmanager)
{
    propmgr=propmanager;
    loadResources();
    initLayer();
}


sf::Color  Challenge::getColor(std::string color)
{
    sf::Color co;

    std::transform(color.begin(), color.end(),color.begin(), ::toupper);
    if(color.compare("BLACK")==0) co=sf::Color::Black;
    else if(color.compare("RED")==0) co=sf::Color::Red;
    else if(color.compare("GREEN")==0) co=sf::Color::Green;
    else if(color.compare("BLUE")==0) co=sf::Color::Blue;
    else if(color.compare("YELLOW")==0) co=sf::Color::Yellow;
    else if(color.compare("MAGENTA")==0) co=sf::Color::Magenta;
    else if(color.compare("CYAN")==0) co=sf::Color::Cyan;
    else if(color.compare("TRASPARENT")==0) co=sf::Color::Transparent;
    return co;
}

void Challenge::loadResources()
{

    if(propmgr.getStatus()==0)
    {
        toppic.loadFromFile(propmgr.getChallProperty(TOP_PIC));
        bottompic.loadFromFile(propmgr.getChallProperty(BOTTOM_PIC));
        centerpic.loadFromFile(propmgr.getChallProperty(CENTER_PIC));
        atmopic.loadFromFile(propmgr.getChallProperty(ATMO_PIC));
        frontpic.loadFromFile(propmgr.getChallProperty(FRONT_PIC));
        soundchall=propmgr.getChallProperty(SOUND_CHALL);

        font.loadFromFile(propmgr.getChallProperty(FONT_TYPE));
        std::string fontSize=propmgr.getChallProperty(FONT_SIZE);
        std::string fontColor=propmgr.getChallProperty(FONT_COLOR);

        testBase.setFont(font);
        testBase.setCharacterSize(std::stoi(fontSize));
        testBase.setColor(getColor(fontColor));

        if (!buffersound.loadFromFile(soundchall))
            nosound=true;

    }

}


void Challenge::initLayer()
{
    unsigned int zlevel;
    zlevel=1;
    layerAtmo.init(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(LAYER_ATMO_RECTLEFT, LAYER_ATMO_RECTTOP, LAYER_ATMO_RECWIDTH,LAYER_ATMO_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_ATMO_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    layerAtmo.setLevel(zlevel);
    zlevel++;
    layerTop.init(toppic,TOP_SPEED_FACTOR,sf::IntRect(LAYER_TOP_RECTLEFT, LAYER_TOP_RECTTOP, LAYER_TOP_RECWIDTH,LAYER_TOP_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_TOP_POSX),static_cast<float>(LAYER_TOP_POSY)),zlevel);
    layerTop.setLevel(zlevel);
    zlevel++;
    layerCenter.init(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(LAYER_CENTER_RECTLEFT, LAYER_CENTER_RECTTOP, LAYER_CENTER_RECWIDTH, LAYER_CENTER_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_CENTER_POSX),static_cast<float>(LAYER_CENTER_POSY)),zlevel);
    layerCenter.setLevel(zlevel);
    zlevel++;
    layerBottom.init(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(LAYER_BOTTOM_RECTLEFT, LAYER_BOTTOM_RECTTOP, LAYER_BOTTOM_RECWIDTH,LAYER_BOTTOM_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_BOTTOM_POSX),static_cast<float>(LAYER_BOTTOM_POSY)),zlevel);
    layerBottom.setLevel(zlevel);

    layerFront.init(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(LAYER_FRONT_RECTLEFT, LAYER_FRONT_RECTTOP, LAYER_FRONT_RECWIDTH,LAYER_FRONT_RECTHEIGHT),sf::Vector2f(static_cast<float>(LAYER_FRONT_POSX),static_cast<float>(LAYER_FRONT_POSY)),zlevel);
    layerFront.setLevel(ZLEVELMAX);

    zlevelAct=0;

    layerAtmo.setPosition(LAYER_ATMO_POSX,LAYER_ATMO_POSY);
    layerTop.setPosition(LAYER_TOP_POSX,LAYER_TOP_POSY);
    layerCenter.setPosition(LAYER_CENTER_POSX,LAYER_CENTER_POSY);
    layerBottom.setPosition(LAYER_BOTTOM_POSX,LAYER_BOTTOM_POSY);
    layerFront.setPosition(LAYER_FRONT_POSX,LAYER_FRONT_POSY);

}

void Challenge:: move(float speed)
{
    layerBottom.move(speed,0);
    layerCenter.move(speed,0);
    layerTop.move(speed,0);
    layerAtmo.move(speed,0);
    layerFront.move(speed,0);
}


void Challenge:: playSound()
{
    sound.setBuffer(buffersound);
    sound.setLoop(true);
    sound.play();

}

void Challenge:: stopSound()
{
    sound.stop();
}


void Challenge::setLevel(unsigned int lev)
{
    zlevelAct=lev;
}
unsigned int Challenge::getLevel()
{
    return zlevelAct;
}

void Challenge::incLevel()
{
    zlevelAct=(zlevelAct+1)%ZLEVELMAX;
}


void Challenge::draw(sf::RenderTarget &target, sf::RenderStates &states,unsigned int actzlevel)
{
 /*    target.draw(layerTop);
    target.draw(layerAtmo);
    target.draw(layerCenter);
    target.draw(layerBottom);
    target.draw(layerFront);*/

    layerTop.draw(target,states,actzlevel);
    layerAtmo.draw(target,states,actzlevel);
    layerCenter.draw(target,states,actzlevel);
    layerBottom.draw(target,states,actzlevel);
    layerFront.draw(target,states,actzlevel);

    incLevel();
}


