#include "Game.hpp"
#include "Utility.hpp"

//listens to events (in this case, closing the window by the cross button or by the escape key)
void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }
}

void Game::horseMove()
{
    const auto elapsed = horsePlayerDeltaTime.getElapsedTime();

    int realSpeed = abs(speedX);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        horsePlayer.move(sf::Keyboard::Left, elapsed.asSeconds());
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        horsePlayer.move(sf::Keyboard::Right, elapsed.asSeconds());
    else
        horsePlayer.move(sf::Keyboard::A, elapsed.asSeconds());// o un qualsiasi altro tasto

    speedX=horsePlayer.getSpeed();

    float rspeed= elapsed.asSeconds() * speedX;

    chall.move(rspeed);
//    horsePlayer2.setTexture();
//    horsePlayer3.setTexture();
    horsePlayer2.move(rspeed,0);
    horsePlayer3.move(rspeed,0);
    //restart the timer
    horsePlayerDeltaTime.restart();
}
void Game::animateExplosion()
{
    const auto explosionDeltaTime = explosionDeltaTimer.getElapsedTime();
    //loop tru explosions vector and animate the pointers
    for (auto i = explosions.begin(); i != explosions.end(); i++)
    {
        (*i)->play(boom);
        (*i)->update(explosionDeltaTime);
        (*i)->move(speedX*explosionDeltaTime.asSeconds(),0);
    }
    //remove pointer from vector if isAlive returns false.
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),[this](const std::shared_ptr<AnimatedSprite>& o){ return !o->isAlive(); }), explosions.end());
    explosionDeltaTimer.restart();
}
void Game::createWeather()
{
    //create random starting position
    int posx = rand() % 2350 + (-750);
    int posy = -20;
    unsigned int zlevel = rand() % (HORSEZLEVELMAX - HORSEZLEVELMIN) + HORSEZLEVELMIN;
    const auto spawnSome = weatherSpawnTimer.getElapsedTime();
    const auto timeSinceStart = weatherDeltaTime.getElapsedTime();
//Mathy  timerDifficulty = sf::seconds(5.f);
    sf::Time timerDifficulty = sf::seconds(1.f);
    if (spawnSome > timerDifficulty )//&& countDown > 10)
    {
        unsigned int maxy=horseposymax[zlevel-HORSEZLEVELMIN];
//        cout<<"ZLEVEL "<<zlevel-HORSEZLEVELMIN<<"MAXY "<<maxy<<"\n";
        auto weathptr = std::make_shared<Weather>(Weather(weathtexture,weatherMoveSpeed,posx,posy,zlevel,maxy));
        weath.push_back(weathptr);
        weatherSpawnTimer.restart();
    }

    for (auto i = weath.begin(); i != weath.end(); i++)
        (*i)->updateWeather(speedX, timeSinceStart.asSeconds());

    weath.erase(std::remove_if(weath.begin(), weath.end(),[this](const std::shared_ptr<Weather> o)
                                 {
                                     //delete enemy if isenemy alive returns true. create explosion @ same cordinates
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

void Game::collision()
{

    for (auto i = weath.begin(); i != weath.end(); i++)
    {
        if(horsePlayer.getZLevel()==(*i)->getZLevel())
            {
            sf::FloatRect playerbox = horsePlayer.getHorseGlobalBounds();
            sf::FloatRect weatherbox =   (*i)->getWeatherGlobalBounds();
            //cout<<"Player:"<< playerbox.height<<" "<<playerbox.width<<" "<<playerbox.left<<" "<<playerbox.top<<" "<<"\n";
            //cout<<"weatherbox:"<< weatherbox.height<<" "<<weatherbox.width<<" "<<weatherbox.left<<" "<<weatherbox.top<<" "<<"\n";
            if (playerbox.intersects((*i)->getWeatherGlobalBounds()))
             //if (playerbox.contains(weatherbox.left,weatherbox.top))
                if (playerbox.intersects((*i)->getWeatherGlobalBounds()))
            {
                auto pExplosion = std::make_shared<AnimatedSprite>(AnimatedSprite(sf::seconds(0.05f),false,false));
                pExplosion->setPosition(horsePlayer.getHorsePosition());
                explosions.push_back(pExplosion);
//                horsePlayer.setHorsePosition(400, 472);
                speedX = 0;
                ;//TODO dec energy horse
                cout<<"Hit!!\n";
                weath.erase(i);
                break;
            }
        }
    }

}


void Game::loadExplosion()
{
    //create animation using 16 images sheet. all sprites 30x30px big
    boom.setSpriteSheet(explosion);
    for (unsigned j = 0; j < explosion.getSize().y; j+=30)
        for (unsigned i = 0; i < explosion.getSize().x; i+=30)
            boom.addFrame(sf::IntRect(i,j,30,30));
}


bool Game::checkWinner()
{
    unsigned int travel;
    travel=horsePlayer.getTravelled();

    if (travel >= pathlen)
    {
        speedX = 0;
        return true;
    }
    else
    {
        ;//TODO
        return false;
    }
}


void Game::chgState()
{

    winstate=checkWinner();
    if(winstate)
    {
        testBottomCenter="Press Return KEY to continue....";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            testBottomCenter="";
            winstate=false;
            stopSound();
            initHorses();
            getNextChall();
        }
    }
    else
    {
        gameoverstate=false;
        if(gameoverstate)
        {
            stopSound();
            testBottomCenter="GAME OVER";
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                testBottomCenter="";
                initHorses();
            }
        }
        else
        {
            horseMove();
            sf::RenderStates states;
/*            horsePlayer.draw(window,states,6);
            horsePlayer2.draw(window,states,6);
            horsePlayer3.draw(window,states,6);
            */
            drawWeather();
            drawExplosions();
        }
    }
}

void Game::updateMenu()
{
    menu.setPosition(gameview.getCenter());
    menu.UpdateText("","",testBottomCenter,"","",chall.getName());

}


void Game::render()
{
    sf::RenderStates states;

    window.clear();
    for(unsigned int zlevel = 1; zlevel <= ZLEVELMAX; zlevel++)
    {
        chall.draw(window,states,zlevel);
        if (winstate||gameoverstate)
        {
            ;//TODO
        }
        if(!winstate&&!gameoverstate)
        {
            horsePlayer.draw(window,states,zlevel);
            horsePlayer2.draw(window,states,zlevel);
            horsePlayer3.draw(window,states,zlevel);
            drawExplosions();
        }

    }
    drawWeather();
    window.draw(menu);
    window.display();
}

void Game::drawWeather()
{
    for (auto e = weath.begin(); e != weath.end(); e++)
        window.draw(*(*e));
}

void Game::drawExplosions()
{
    for (auto x = explosions.begin(); x != explosions.end(); x++)
        window.draw(*(*x));
}



void Game::loadResources()
{
  gameerrorstate=true;
  if(propmgr.getStatus()==0)
  {

//      weathtexture.loadFromFile("img/thunder.png");
      weathtexture.loadFromFile(propmgr.getCurrentWeatherTexture(std::to_string(actchall),"1"));
//      explosion.loadFromFile("img/thunder_exp.png");
      explosion.loadFromFile(propmgr.getCurrentWeatherExplosion(std::to_string(actchall),"1"));


      chall.setName(propmgr.getCurrentTrack(std::to_string(actchall)));
      propmgr.setTrack(chall.getName());

      std::cout<<"length: "<<propmgr.getTrackProperty(PATHLENGHT);

      pathlen=stoi(propmgr.getTrackProperty(PATHLENGHT));
      icon.loadFromFile("img/icon.png");

      font.loadFromFile(propmgr.getTrackProperty(FONT_TYPE));
      std::string fontSize= propmgr.getTrackProperty(FONT_SIZE);
      std::string fontColor= propmgr.getTrackProperty(FONT_COLOR);

      testBase.setFont(font);
      testBase.setCharacterSize(std::stoi(fontSize));
      testBase.setColor(Utility::getColor(fontColor));

      gameerrorstate=false;

  }

}

void Game::getNextChall()
{
    actchall++;

    loadResources();
    if(!gameerrorstate)
    {
        chall.init(propmgr);
        menu.Init(testBase, gameview.getCenter());
    }
    playSound();
}

void Game::playSound()
{
    chall.playSound();
}

void Game::stopSound()
{
    chall.stopSound();
}

void Game::initHorses()
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

void Game::horseMaxYCreate()
{
    horseposymax[0]=HORSE1_POSY;
    horseposymax[1]=HORSE2_POSY;
    horseposymax[2]=HORSE3_POSY;
}

//game loop: it is executed until exit or errors
void Game::Run()
{
    while (window.isOpen() && !gameerrorstate)
    {
        for(unsigned int i=0;i<40;i++)
            createWeather();
        animateExplosion();
        collision();
        processEvents();
        updateMenu();
        chgState();
        render();
    }
}

//class constructor: creates a SFML window and initializes objects
Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    horseMaxYCreate();
    actchall=1;
    speedX = 0;
    std::string actchallstr;
    propmgr.Init();
    actchallstr= propmgr.getCurrentTrack(std::to_string(actchall));
    propmgr.setTrack(actchallstr);
    winstate=false;
    weatherMoveSpeed=40.f;
    loadResources();
    if(!gameerrorstate)
    {
        initHorses();
        chall.init(propmgr);

        playSound();

        window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());

        gameview.setCenter(GVIEW_X / 2,GVIEW_Y / 2);
        gameview.setSize(sf::Vector2f(GVIEW_X, GVIEW_Y));

        menu.Init(testBase, gameview.getCenter());
        loadExplosion();
    }
};
