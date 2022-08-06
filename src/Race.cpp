#include "Race.hpp"
#include "Utility.hpp"
#include <algorithm>

Race::Race(Game* gamePtr, int* horseNumbers, Subject* subject, const bool demo)
{
    game = gamePtr;
    this->demo = demo;
    this->subject=subject;
    gameoverstate = false;
    horseMaxYCreate();
    currentTrackIndex = 1;
    speedX = 0;
    winstate = false;
    weatherMoveSpeed = 40.f;
    int zlevel=HORSEZLEVELMIN;
    horsePlayer = std::make_unique<Horse>(horseNumbers[0], sf::Vector2f(32, 16), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y), zlevel, false);
    zlevel++;
    horsePlayer2 = std::make_unique<Horse>(horseNumbers[1], sf::Vector2f(32, 16), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y), zlevel, true);
    zlevel++;
    horsePlayer3 = std::make_unique<Horse>(horseNumbers[2], sf::Vector2f(32, 16), sf::Vector2f(HORSE3_POS_X, HORSE3_POS_Y), zlevel, true);

    horsePlayer->startPos(sf::Vector2f(0, 0), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y));
    horsePlayer2->startPos(sf::Vector2f(0 , 0), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y));
    horsePlayer3->startPos(sf::Vector2f(0 , 0), sf::Vector2f(HORSE3_POS_X, HORSE3_POS_Y));

    if(demo)
        horsePlayer->setSpeed(-250);
    track = std::make_unique<Track>(getDBInstance()->getTrackProperty(currentTrackIndex, "name"));

    weatherId=createProbability();
    weathtexture.loadFromFile(getDBInstance()->getCurrentWeatherTexture(std::to_string(weatherId)));

    explosionTexture.loadFromFile(getDBInstance()->getCurrentWeatherExplosion(std::to_string(weatherId)));
    explosionAnimation.setSpriteSheet(explosionTexture);

    obstacletexture.loadFromFile(getDBInstance()->getTrackProperty(currentTrackIndex, OBSTACLE_TEX));

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

    subject->CreateMessage(std::to_string(horsePlayer->getLife()),LIFE_MSG);
    subject->CreateMessage(track->getName(),TRACK_MSG);
    subject->CreateMessage( std::to_string(horsePlayer->getMoney()),MONEY_MSG);
}

void Race::update(sf::Time deltaTime)
{
    {
        int nmaxweather;
        nmaxweather=40;
        for(unsigned int i=0;i<nmaxweather;i++)
            createWeather();
        animateExplosion();
        collision();
        if(!winstate){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                horsePlayer->SetJumpON();
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
        drawWeather(window,zlevel);
        drawObstacle(window,zlevel);
    }
    drawExplosions(window);
}

void Race::horseMove(bool move, sf::Time deltaTime)
{
    int zlevel;
    sf::Rect<float> obstacle_pos;
    if (move)
    {
        track->move(deltaTime);
        horsePlayer->move(true, deltaTime.asSeconds());
    }
    else
    horsePlayer->move(false, deltaTime.asSeconds());// o un qualsiasi altro tasto
    speedX=horsePlayer->getSpeed();
    rspeed= deltaTime.asSeconds() * speedX;
    createObstacle();
    for (auto i = obs.begin(); i != obs.end(); i++)
    {
        zlevel=(*i)->getZLevel();
        obstacle_pos=(*i)->getObstacleGlobalBounds();
        if(zlevel==horsePlayer2->getZLevel())
            if(isTimeToJump(horsePlayer2->getGlobalBounds(),obstacle_pos))
                horsePlayer2->SetJumpON();
        if(zlevel==horsePlayer3->getZLevel())
            if(isTimeToJump(horsePlayer3->getGlobalBounds(),obstacle_pos))
                horsePlayer3->SetJumpON();
    }
    horsePlayer2->move(rspeed, 0,  deltaTime.asSeconds());
    horsePlayer3->move(rspeed, 0,  deltaTime.asSeconds());
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
    subject->CreateMessage(track->getName(),TRACK_MSG);
    horsePlayer->startPos(sf::Vector2f(0, 0), sf::Vector2f(HORSE1_POS_X, HORSE1_POS_Y));
    horsePlayer2->startPos(sf::Vector2f(0 , 0), sf::Vector2f(HORSE2_POS_X, HORSE2_POS_Y));
    horsePlayer3->startPos(sf::Vector2f(0 , 0), sf::Vector2f(HORSE3_POS_X, HORSE3_POS_Y));

    if(demo)
        horsePlayer->setSpeed(-250);

    weatherId=createProbability();
    weathtexture.loadFromFile(getDBInstance()->getCurrentWeatherTexture(std::to_string(weatherId)));
    explosionTexture.loadFromFile(getDBInstance()->getCurrentWeatherExplosion(std::to_string(weatherId)));
    obstacletexture.loadFromFile(getDBInstance()->getTrackProperty(currentTrackIndex, OBSTACLE_TEX));

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
    subject->CreateMessage(std::to_string(ranking[0]),FIRST_MSG);
    subject->CreateMessage(std::to_string(ranking[1]),SECOND_MSG);
    subject->CreateMessage(std::to_string(ranking[2]),THIRD_MSG);
}


void Race::calculateGlobalRanking()
{
   horsePlayer->setTotalTravelled(horsePlayer->getPosition().x);
   horsePlayer2->setTotalTravelled(horsePlayer2->getPosition().x);
   horsePlayer3->setTotalTravelled(horsePlayer3->getPosition().x);

    std::vector<float> distances = { horsePlayer->getTotalTravelled(), horsePlayer2->getTotalTravelled(), horsePlayer3->getTotalTravelled() };
    map<float, int> pairs = { { horsePlayer->getTotalTravelled(), horsePlayer->getNumber() }, {horsePlayer2->getTotalTravelled(), horsePlayer2->getNumber() }, {horsePlayer3->getTotalTravelled(), horsePlayer3->getNumber() } };

    std::sort(distances.begin(), distances.end());
    for (int i = 0; i < HORSE_COUNT; i++)
    globalRanking[HORSE_COUNT - i - 1] = pairs[distances[i]];
    subject->CreateMessage(std::to_string(globalRanking[0]),FIRST_MSG);
    subject->CreateMessage(std::to_string(globalRanking[1]),SECOND_MSG);
    subject->CreateMessage(std::to_string(globalRanking[2]),THIRD_MSG);
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

void Race::createObstacle()
{

    int posx = 800;

    unsigned int zlevel;
    const auto spawnSome = obstacleSpawnTimer.getElapsedTime();
    const auto timeSinceStart = obstacleDeltaTime.getElapsedTime();

    bool newobj=false;

    while(!newobj&&obs.size()<HORSE_COUNT)
    {
        newobj=true;
        zlevel= rand() % (HORSEZLEVELMAX - HORSEZLEVELMIN) + HORSEZLEVELMIN;
        for (auto i = obs.begin(); i != obs.end(); i++)
        {

            if(zlevel== (*i)->getZLevel())
            {
                newobj=false;
                break;
            }
        }
    }

    sf::Time timerDifficulty = sf::seconds(1.f);
    if (spawnSome > timerDifficulty )
    {
        if(obs.size()<HORSE_COUNT)
        {
            unsigned int posy=horseposymax[zlevel-HORSEZLEVELMIN]+horsePlayer->getGlobalBounds().height-obstacletexture.getSize().y;
            auto obsptr = std::make_shared<Obstacle>(Obstacle(obstacletexture,rspeed,posx,posy,zlevel,0));
            obs.push_back(obsptr);
            cout<<"Create obstacle Object size:"<<obs.size()<<"\n";
        }
        obstacleSpawnTimer.restart();

    }
    for (auto i = obs.begin(); i != obs.end(); i++)
        (*i)->updateObstacle(rspeed, timeSinceStart.asSeconds());

    obs.erase(std::remove_if(obs.begin(), obs.end(),[this](const std::shared_ptr<Obstacle> o)
                             {
                                 if (!(*o).isObstacleAlive())
                                 {
                                     auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
                                     pExplosion->setPosition(o->getObstaclePosition());
                                     explosions.push_back(pExplosion);
                                     return true;
                                 }
                                 else
                                     return false;
                             }
    ), obs.end());

    obstacleDeltaTime.restart();
}


void Race::collision()
{
    for (auto i = weath.begin(); i != weath.end(); i++)
    {
        if(collisionWeather(horsePlayer,*i))
            weath.erase(i);
        else if(collisionWeather(horsePlayer2,*i))
            weath.erase(i);
        else if(collisionWeather(horsePlayer3,*i))
            weath.erase(i);
    }

    for (auto i = obs.begin(); i != obs.end(); i++)
    {
        if(collisionObstacle(horsePlayer,*i))
        {
            cout<<"Before Canc Obstacle on horsePlayer!! obs size= "<<obs.size()<<"\n";
            obs.erase(i);
            cout<<"After Canc Obstacle on horsePlayer!! obs size= "<<obs.size()<<"\n";
            break;
        }
    }
    for (auto i = obs.begin(); i != obs.end(); i++)
    {
        if(collisionObstacle(horsePlayer2,*i))
        {
            cout<<"Before Canc Obstacle on Horse2!! obs size= "<<obs.size()<<"\n";
            obs.erase(i);
            cout<<"After Canc Obstacle on Horse2!! obs size= "<<obs.size()<<"\n";
            break;
        }
    }
    for (auto i = obs.begin(); i != obs.end(); i++)
    {

        if(collisionObstacle(horsePlayer3,*i))
        {
            cout<<"Before Canc Obstacle on Horse2!! obs size= "<<obs.size()<<"\n";
            obs.erase(i);
            cout<<"After Canc Obstacle on Horse2!! obs size= "<<obs.size()<<"\n";
            break;
        }
    }
}


bool Race::collisionObstacle(std::shared_ptr<Horse> horse,shared_ptr<Obstacle> o)
{
    bool collisiondetected=false;
    if(horse->getZLevel()==o->getZLevel())
    {
        sf::FloatRect playerbox = horse->getGlobalBounds();
        if (playerbox.intersects(o->getObstacleGlobalBounds()))
        {
            auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
            pExplosion->setPosition(horse->getPosition());
            explosions.push_back(pExplosion);
            speedX = 0;
            cout<<"Hit Obstacle!!\n";
            collisiondetected=true;
            horse->decLife();
            subject->CreateMessage(std::to_string(horse->getLife()),LIFE_MSG);

        }
    }
    return collisiondetected;
}


bool Race::collisionWeather(std::shared_ptr<Horse> horse,shared_ptr<Weather> w)
{
    bool collisiondetected=false;
    if(horse->getZLevel()==w->getZLevel())
    {
        sf::FloatRect playerbox = horse->getGlobalBounds();
        if (playerbox.intersects(w->getWeatherGlobalBounds()))
        {
            auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
            pExplosion->setPosition(horse->getPosition());
            explosions.push_back(pExplosion);
            cout<<"Hit "<<horse->getName()<<endl;
            collisiondetected=true;
            horse->decLife();
            if(!horse->CPU())
                subject->CreateMessage(std::to_string(horse->getLife()),LIFE_MSG);

        }
    }
    return collisiondetected;
}

void Race::drawWeather(sf::RenderTarget &window, unsigned int zlevel)
{
    for (auto e = weath.begin(); e != weath.end(); e++)
        if((*e)->getZLevel()==zlevel)
            window.draw(*(*e));
}

void Race::drawObstacle(sf::RenderTarget &window, unsigned int zlevel)
{
    for (auto e = obs.begin(); e != obs.end(); e++)
        if((*e)->getZLevel()==zlevel)
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

bool Race::isTimeToJump(sf::FloatRect horsepos,sf::FloatRect obstaclepos)
{
    return (horsepos.left>(obstaclepos.left-150))&&horsepos.left<obstaclepos.left;
}

bool Race::reward()
{
    for(int i=0;i<HORSE_COUNT;i++)
        if(ranking[i]== horsePlayer->getNumber())
            horsePlayer->incMoney(HORSE_COUNT+1-i);
    subject->CreateMessage( std::to_string(horsePlayer->getMoney()),MONEY_MSG);
    if(horsePlayer->getMoney()>=5){
        horsePlayer->incLife();
        horsePlayer->decMoney(5);
        subject->CreateMessage(std::to_string(horsePlayer->getLife()),LIFE_MSG);
        subject->CreateMessage( std::to_string(horsePlayer->getMoney()),MONEY_MSG);
        return true;
    }
    else
        return false;
}

