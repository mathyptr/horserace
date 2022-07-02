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

    //restart the timer
    horsePlayerDeltaTime.restart();
}

void Game::chgState()
{

    /*
            if (start)
                checkWin();
            else if (pricegiving)
                checkEndPrizeGiving();
    */
    winstate=false;

    if(winstate)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                initHorses();
            }
        }
        else
        {
            horseMove();
            sf::RenderStates states;
            horsePlayer.draw(window,states,6);
        }
    }
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
        }

        window.draw(menu);
    }
    window.display();
}

void Game::loadResources()
{
  gameerrorstate=true;
  if(propmgr.getStatus()==0)
  {
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

    std::string actchallstr;
    actchallstr= propmgr.getCurrentTrack(std::to_string(actchall));

    propmgr.setTrack(actchallstr);

    loadResources();
    if(!gameerrorstate)
        chall.init(propmgr);
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
    float posx,posy;
    zlevel=5;
    posx=HORSE3_POSX;
    posy=HORSE3_POSY;
    horsePlayer.init(1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx),static_cast<float>(posy)),zlevel);
}

//game loop: it is executed until exit or errors
void Game::Run()
{
    while (window.isOpen() && !gameerrorstate)
    {
        processEvents();
        chgState();
        render();
    }
}

//class constructor: creates a SFML window and initializes objects
Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    actchall=1;
    speedX = 0;
    std::string actchallstr;
    propmgr.Init();
    actchallstr= propmgr.getCurrentTrack(std::to_string(actchall));
    propmgr.setTrack(actchallstr);
    winstate=false;

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
    }
};
