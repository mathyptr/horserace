#include "Challenge.hpp"


Challenge::Challenge()
{
    zlevel_Act=0;
    zlevel_Max=0;
}

void Challenge::Init(propertyManager propmanager)
{
    propmgr=propmanager;
    loadResources();
    InitLayer();
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


void Challenge::InitLayer()
{

    layerAtmo.Init(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(0, 0, 800,180),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)));
    layerBottom.Init(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)));
    layerTop.Init(toppic,TOP_SPEED_FACTOR,sf::IntRect(0, 0, 800,480),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)));
    layerCenter.Init(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(0, 280, 800, 250),sf::Vector2f(static_cast<float>(0),static_cast<float>(285)));
    layerFront.Init(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)));

    zlevel_Act=0;
    zlevel_Max=5;

    layerBottom.setPosition(0,472);
    layerCenter.setPosition(0,285);
    layerTop.setPosition(0,0);
    layerAtmo.setPosition(0,0);
    layerFront.setPosition(0,472);

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

void Challenge::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
unsigned int zlevel_Act=0;
    target.draw(layerTop);
    target.draw(layerAtmo);
    target.draw(layerCenter);
    target.draw(layerBottom);
    target.draw(layerFront);
//    zlevel_Act=(zlevel_Act+1)%zlevel_Max;
}


