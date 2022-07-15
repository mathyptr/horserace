#include "Race.hpp"
#include "Utility.hpp"
#include "Game.hpp"


void Race::horseMove(bool go)
{
    const auto elapsed = horsePlayerDeltaTime.getElapsedTime();
    int realSpeed = abs(speedX);
    if (go)
        horsePlayer.move(true, elapsed.asSeconds());
    else
        horsePlayer.move(false, elapsed.asSeconds());// o un qualsiasi altro tasto
    speedX=horsePlayer.getSpeed();
    float rspeed= elapsed.asSeconds() * speedX;
    track->move(rspeed);
    horsePlayer2.move(rspeed,0);
    horsePlayer3.move(rspeed,0);
    horsePlayerDeltaTime.restart();
}



bool Race::checkWinner()
{
    unsigned int travel;
    travel=horsePlayer.getTravelled();

    if (travel >= pathlen)
    {
        speedX = 0;
        winstate=true;
        return true;
    }
    else
    {
        ;//TODO
        return false;
    }
}




void Race::animateExplosion()
{
    const auto explosionDeltaTime = explosionDeltaTimer.getElapsedTime();
    for (auto i = explosions.begin(); i != explosions.end(); i++)
    {
        (*i)->play(boom);
        (*i)->update(explosionDeltaTime);
        (*i)->move(speedX*explosionDeltaTime.asSeconds(),0);
    }
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),[this](const std::shared_ptr<AnimatedSprite>& o){ return !o->isAlive(); }), explosions.end());
    explosionDeltaTimer.restart();
}

void Race::createWeather()
{
    int posx = rand() % 2350 + (-750);
    int posy = -20;
    unsigned int zlevel = rand() % (HORSEZLEVELMAX - HORSEZLEVELMIN) + HORSEZLEVELMIN;
    const auto spawnSome = weatherSpawnTimer.getElapsedTime();
    const auto timeSinceStart = weatherDeltaTime.getElapsedTime();
    sf::Time timerDifficulty = sf::seconds(1.f);
    if (spawnSome > timerDifficulty )//&& countDown > 10)
    {
        unsigned int maxy=horseposymax[zlevel-HORSEZLEVELMIN];
        auto weathptr = std::make_shared<Weather>(Weather(weathtexture,weatherMoveSpeed,posx,posy,zlevel,maxy));
        weath.push_back(weathptr);
        weatherSpawnTimer.restart();
    }

    for (auto i = weath.begin(); i != weath.end(); i++)
        (*i)->updateWeather(speedX, timeSinceStart.asSeconds());

    weath.erase(std::remove_if(weath.begin(), weath.end(),[this](const std::shared_ptr<Weather> o)
                                 {
                                     if (!(*o).isWeatherAlive())
                                     {
                                         auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
                                         pExplosion->setPosition(o->getWeatherPosition());
                                         explosions.push_back(pExplosion);
                                         return true;
                                     }
                                     else
                                         return false;
                                 }
    ), weath.end());

    weatherDeltaTime.restart();
}

void Race::collision()
{

    for (auto i = weath.begin(); i != weath.end(); i++)
    {
        if(horsePlayer.getZLevel()==(*i)->getZLevel())
            {
            sf::FloatRect playerbox = horsePlayer.getHorseGlobalBounds();
            if (playerbox.intersects((*i)->getWeatherGlobalBounds()))
                if (playerbox.intersects((*i)->getWeatherGlobalBounds()))
            {
                auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
                pExplosion->setPosition(horsePlayer.getHorsePosition());
                explosions.push_back(pExplosion);
                speedX = 0;
                cout<<"Hit!!\n";
                weath.erase(i);
                if(!horsePlayer.decLife())
                    gameoverstate=true;
                break;
            }
        }
    }

}


void Race::loadExplosion()
{
    boom.setSpriteSheet(explosion);
    for (unsigned j = 0; j < explosion.getSize().y; j+=30)
        for (unsigned i = 0; i < explosion.getSize().x; i+=30)
            boom.addFrameRect(sf::IntRect(i,j,30,30));
}

void Race::drawWeather(sf::RenderTarget &window)
{
    for (auto e = weath.begin(); e != weath.end(); e++)
        window.draw(*(*e));
}

void Race::drawExplosions(sf::RenderTarget &window)
{
    for (auto x = explosions.begin(); x != explosions.end(); x++)
        window.draw(*(*x));
}

int Race::createProbability(){
    int probability;
    int actprob;
    int prob[NMAXPROB];
    int j=0;
    for(int i=1,j=0;i<4;i++){
        probability=std::stoi(propmgr.getProbability(std::to_string(currentTrackIndex),std::to_string(i)));
        while(j<NMAXPROB&&probability>0){
            prob[j]=i;
            probability--;
            j++;
        }
    }
    actprob=prob[rand()%(10-1)];
    return actprob;
}


void Race::loadResources()
{
    gameerrorstate=true;
    if(propmgr.getStatus()==0)
    {
    weatherId=createProbability();
    std::cout<<"Load Probability: "<<endl;
    weathtexture.loadFromFile(propmgr.getCurrentWeatherTexture(std::to_string(weatherId)));
    explosion.loadFromFile(propmgr.getCurrentWeatherExplosion(std::to_string(weatherId)));
    if(track!=NULL)
        track->setName(propmgr.getTrackProperty(currentTrackIndex, "name"));

    pathlen=stoi(propmgr.getTrackProperty(currentTrackIndex, PATHLENGTH));
    icon.loadFromFile("img/icon.png");

   /* font.loadFromFile(propmgr.getTrackProperty(currentTrackIndex, FONT_FILE));
    std::string fontSize= propmgr.getTrackProperty(currentTrackIndex, FONT_SIZE);
    std::string fontColor= propmgr.getTrackProperty(currentTrackIndex, FONT_COLOR);

    testBase.setFont(font);
    testBase.setCharacterSize(std::stoi(fontSize));
    testBase.setColor(Utility::getColor(fontColor));*/

    gameerrorstate=false;
    }
}

void Race::getNextTrack()
{
    horsePlayer.incMoney(currentTrackIndex*5);
    winstate=false;
   /* testBottomCenter="";
    testTopRight="";
    testTopCenter="";*/
    currentTrackIndex++;
    character=0;
    initHorses();
    loadResources();
    if(!gameerrorstate)
    {
        if(track!=NULL)
            delete track;
        track = new Track(propmgr, propmgr.getTrackProperty(currentTrackIndex, "name"));
        //menu.Init(testBase, posgameview);
    }
    playSound();
}

void Race::playSound()
{
    track->playSound();
}

void Race::stopSound()
{
    track->stopSound();
}

void Race::initHorses()
{
    unsigned int zlevel;
    float posx,posy,posx2,posy2,posx3,posy3;

    posx3=HORSE3_POSX;
    posy3=HORSE3_POSY;
    posx2=HORSE2_POSX;
    posy2=HORSE2_POSY;
    posx=HORSE1_POSX;
    posy=HORSE1_POSY;
    zlevel=5;
    horsePlayer2.init(2,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx2),static_cast<float>(posy2)),zlevel);
    zlevel++;
    horsePlayer3.init(3,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx3),static_cast<float>(posy3)),zlevel);
    zlevel++;
    horsePlayer.init(1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx),static_cast<float>(posy)),zlevel);
}

void Race::horseMaxYCreate()
{
    horseposymax[0]=HORSE1_POSY;
    horseposymax[1]=HORSE2_POSY;
    horseposymax[2]=HORSE3_POSY;
}

std::string Race::order( map <std::string,float> results){
    map<float,std::string> ordRes;
    std::string res="";
    int i=3;
    for (const auto & [key, value] : results) {
        ordRes.emplace(value, key);
    }

    for (const auto & [key, value] : ordRes) {
        res=std::to_string(i)+". "+value+"\n"+res;
        i--;
    }
    return "Result\n"+res;
}

sf::String Race::result(){
    std::string str;
    horsePlayer.setTotalTravelled(horsePlayer.getHorsePosition().x);
    horsePlayer2.setTotalTravelled(horsePlayer2.getHorsePosition().x);
    horsePlayer3.setTotalTravelled(horsePlayer3.getHorsePosition().x);
    str=order({{"Player",horsePlayer.getHorsePosition().x},{"Salazar",horsePlayer2.getHorsePosition().x},{"Sarah",horsePlayer3.getHorsePosition().x}});
    return  str;
}

std::string Race::finalResult(){
    std::string str;
    str="Total "+order({{"Player",horsePlayer.getTotalTravelled()},{"Salazar",horsePlayer2.getTotalTravelled()},{"Sarah",horsePlayer3.getTotalTravelled()}});
    return str;
}



/*void Race::updateMenu(sf::String bottLeft,sf::String topRight,sf::String topCenter,sf::String bottomRight,sf::String topLeft,sf::String bottomCenter)
{
    testBottomLeft="Life: "+bottLeft;
    testTopLeft=topLeft;
    testBottomCenter=bottomCenter;
    testTopCenter=topCenter;
    menu.UpdateText(testBottomLeft,testTopRight,testBottomCenter,testTopCenter,"",testTopLeft);

}*/

void Race::update()
{
    {
        for(unsigned int i=0;i<40;i++)
            createWeather();
        animateExplosion();
        collision();
        if(!winstate){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
               horseMove(true);
        else
            horseMove(false);
        checkWinner();
     }
    }
}

unsigned int Race::getCurrenteIndex()
{
    return currentTrackIndex;
}

void Race::render(sf::RenderTarget &window)
{
    sf::RenderStates states;
    for(unsigned int zlevel = 1; zlevel <= ZLEVELMAX; zlevel++)
    {
        track->draw(window,states,zlevel);
        if (winstate||gameoverstate)
        {
            ;//TODO
        }
        if(!winstate&&!gameoverstate)
        {
            horsePlayer.draw(window,states,zlevel);
            horsePlayer2.draw(window,states,zlevel);
            horsePlayer3.draw(window,states,zlevel);
            drawExplosions(window);
        }

    }
    drawWeather(window);
    drawExplosions(window);
 //  window.draw(menu);
}



Race::Race(PropertyManager propmanager, const sf::Vector2f& posgv)
{
    track=NULL;
    gameoverstate=false;
    horseMaxYCreate();
    currentTrackIndex=1;
    speedX = 0;
    propmgr = propmanager;
    winstate=false;
    weatherMoveSpeed=40.f;
    posgameview=posgv;
    loadResources();
    if(!gameerrorstate)
    {
        initHorses();
        track = new Track(propmgr, propmgr.getTrackProperty(currentTrackIndex, "name"));
        playSound();
       // menu.Init(testBase, posgameview);
        loadExplosion();
    }
};
