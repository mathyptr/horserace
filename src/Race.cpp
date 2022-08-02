#include "Race.hpp"
#include "Utility.hpp"
#include <algorithm>

Race::Race(Game* gamePtr, int* horseNumbers, const bool demo)
{
    game = gamePtr;
    this->demo = demo;
    
    gameoverstate = false;
    horseMaxYCreate();
    currentTrackIndex = 1;
    speedX = 0;
    winstate = false;
    weatherMoveSpeed = 40.f;
    
    horsePlayer2 = std::make_unique<Horse>(horseNumbers[1], sf::Vector2f(32, 16), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y), 5);
    horsePlayer3 = std::make_unique<Horse>(horseNumbers[2], sf::Vector2f(32, 16), sf::Vector2f(HORSE3_POS_X, HORSE3_POS_Y), 6);
    horsePlayer = std::make_unique<Horse>(horseNumbers[0], sf::Vector2f(32, 16), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y), 7);

    horsePlayer->startPos(sf::Vector2f(32, 16), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y));
    if(demo)
        horsePlayer->setSpeed(-250);
    horsePlayer2->startPos(sf::Vector2f(32 , 16), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y));

    track = std::make_unique<Track>(getDBInstance()->getTrackProperty(currentTrackIndex, "name"));

    weatherId=createProbability();
    weathtexture.loadFromFile(getDBInstance()->getCurrentWeatherTexture(std::to_string(weatherId)));

    explosionTexture.loadFromFile(getDBInstance()->getCurrentWeatherExplosion(std::to_string(weatherId)));
    explosionAnimation.setSpriteSheet(explosionTexture);
    for (unsigned y = 0; y < explosionTexture.getSize().y; y += EXP_SHEET_Y)
        for (unsigned x = 0; x < explosionTexture.getSize().x; x += EXP_SHEET_X)
            explosionAnimation.addFrameRect(sf::IntRect(x, y, EXP_SHEET_X, EXP_SHEET_Y));

    //per la corsa demo si usa la musica da intro, altrimenti la musica del percorso corrente
    if(!this->demo)
    {
        game->music.stop();
        game->music.openFromFile(getDBInstance()->getTrackProperty(currentTrackIndex, SOUND));
        game->music.play();
    }
}

void Race::update(sf::Time deltaTime)
{
    for(unsigned int i = 0; i < 40; i++)
        createWeather();

    animateExplosion();
    collision();

    if(!winstate)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || demo)
            horseMove(true, deltaTime);
        else
            horseMove(false, deltaTime);

        checkFinalLine();
        horsePlayerFinished();
    }
    if(winstate)
        calculateRanking();
}

void Race::render(sf::RenderTarget &window)
{
    sf::RenderStates states;
    for(unsigned int zlevel = 1; zlevel <= ZLEVELMAX; zlevel++)
    {
        track->draw(window, states, zlevel);
        if(!winstate && !gameoverstate)
        {
            horsePlayer->draw(window, states, zlevel);
            horsePlayer2->draw(window, states, zlevel);
            horsePlayer3->draw(window, states, zlevel);
            drawExplosions(window);
        }
    }
    drawWeather(window);
    drawExplosions(window);
}

void Race::horseMove(bool move, sf::Time deltaTime)
{
    if (move)
    {
        track->move(deltaTime);
        horsePlayer->move(true, deltaTime.asSeconds());
    }
    else
        horsePlayer->move(false, deltaTime.asSeconds());// o un qualsiasi altro tasto
    
    speedX = horsePlayer->getSpeed();
    float rspeed= deltaTime.asSeconds() * speedX;
    horsePlayer2->move(rspeed, 0, deltaTime.asSeconds());
    horsePlayer3->move(rspeed, 0, deltaTime.asSeconds());
}

bool Race::horsePlayerFinished()
{
    if (horsePlayer->getTravelled() >= track->getPathLength())
    {
        speedX = 0;
        winstate = true;
        return true;
    }
    else
        return false;
}

unsigned int Race::getCurrentTrackIndex()
{
    return currentTrackIndex;
}

bool Race::loadNextTrack(bool restart)
{
    if(!restart)
        currentTrackIndex++;
    else
        currentTrackIndex = currentTrackIndex % getDBInstance()->getTrackCount() + 1;

    if(currentTrackIndex > getDBInstance()->getTrackCount())
        return false;

    winstate=false;
    gameoverstate=false;

    track = std::make_unique<Track>(getDBInstance()->getTrackProperty(currentTrackIndex, "name"));
    
    horsePlayer->startPos(sf::Vector2f(32, 16), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y));
    horsePlayer2->startPos(sf::Vector2f(32 , 16), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y));
    horsePlayer3->startPos(sf::Vector2f(32 , 16), sf::Vector2f(HORSE3_POS_X, HORSE3_POS_Y));
    horsePlayer->incMoney(currentTrackIndex*5);
    if(demo)
        horsePlayer->setSpeed(-250);

    weatherId=createProbability();
    weathtexture.loadFromFile(getDBInstance()->getCurrentWeatherTexture(std::to_string(weatherId)));
    explosionTexture.loadFromFile(getDBInstance()->getCurrentWeatherExplosion(std::to_string(weatherId)));

    if(!demo)
    {
        game->music.stop();
        game->music.openFromFile(getDBInstance()->getTrackProperty(currentTrackIndex, SOUND));
        game->music.play();
    }

    return true;
}

void Race::calculateRanking()
{
    std::vector<float> distances = { horsePlayer->getPosition().x, horsePlayer2->getPosition().x, horsePlayer3->getPosition().x };
    map<float, int> pairs = { { horsePlayer->getPosition().x, horsePlayer->getNumber() }, { horsePlayer2->getPosition().x, horsePlayer2->getNumber() }, { horsePlayer3->getPosition().x, horsePlayer3->getNumber() } };

    std::sort(distances.begin(), distances.end());
    for (int i = 0; i < HORSE_COUNT; i++)
        ranking[HORSE_COUNT - i - 1] = pairs[distances[i]];
}

const int* Race::getRanking() const
{
    return ranking;
}

bool Race::checkFinalLine()
{
    unsigned int travel;
    travel=horsePlayer->getTravelled();
    if (track->getPathLength()-travel <= 2*MAX_HORIZONTAL_X)
    {
        track->setfinalLineState();
        return true;
    }
    else
        return false;
}

void Race::animateExplosion()
{
    const auto explosionDeltaTime = explosionDeltaTimer.getElapsedTime();
    for (auto i = explosions.begin(); i != explosions.end(); i++)
    {
        (*i)->play(explosionAnimation);
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
    if (spawnSome > timerDifficulty )
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
        if(horsePlayer->getZLevel()==(*i)->getZLevel())
        {
            sf::FloatRect playerbox = horsePlayer->getGlobalBounds();
            if (playerbox.intersects((*i)->getWeatherGlobalBounds()))
            {
                auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
                pExplosion->setPosition(horsePlayer->getPosition());
                explosions.push_back(pExplosion);
                speedX = 0;
                cout<<"Hit!!\n";
                weath.erase(i);
                if(!horsePlayer->decLife())
                    gameoverstate=true;
                break;
            }
        }
    }
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

int Race::createProbability()
{
    int probability;
    int actprob;
    int prob[NMAXPROB];
    int j=0;
    for(int i=1,j=0;i<4;i++){
        probability=std::stoi(getDBInstance()->getProbability(std::to_string(currentTrackIndex),std::to_string(i)));
        while(j<NMAXPROB&&probability>0){
            prob[j]=i;
            probability--;
            j++;
        }
    }
    actprob=prob[rand()%(10-1)];
    return actprob;
}

void Race::horseMaxYCreate()
{
    horseposymax[0]=HORSE1_POS_Y;
    horseposymax[1]=HORSE2_POS_Y;
    horseposymax[2]=HORSE3_POS_Y;
}
