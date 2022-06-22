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
    layerAtmo.init(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(0, 0, 800,180),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)),zlevel);
    zlevel++;
    layerBottom.init(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)),zlevel);
    zlevel++;
    layerTop.init(toppic,TOP_SPEED_FACTOR,sf::IntRect(0, 0, 800,480),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)),zlevel);
    zlevel++;
    layerCenter.init(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(0, 280, 800, 250),sf::Vector2f(static_cast<float>(0),static_cast<float>(285)),zlevel);
    zlevel++;
    layerFront.init(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)),zlevel);


    zlevelAct=0;

    layerBottom.setPosition(0,472);
    layerCenter.setPosition(0,285);
    layerTop.setPosition(0,0);
    layerAtmo.setPosition(0,0);
    layerFront.setPosition(0,472);

    layerTop.setLevel(1);
    layerAtmo.setLevel(2);
    layerCenter.setLevel(3);
    layerBottom.setLevel(4);
    layerFront.setLevel(6);

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


