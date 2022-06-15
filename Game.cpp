#include "Game.hpp"

void Game::processEvent()
{
  sf::Event event;

  while (window.pollEvent(event))
    if (event.type == sf::Event::Closed)
      window.close();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    window.close();
}


void Game::render()
{
    window.clear();

    for(int i=0;i<MAX_ZLEVEL_GAME;i++)
    {
        window.draw(chall);
        window.draw(mmenu);
    }
    window.display();
}

void Game::Run()
{
  while (window.isOpen()&&!gameerrorstate)
  {
    processEvent();
    render();
  }
}


sf::Color  Game::getColor(std::string color)
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

void Game::loadResources()
{
  gameerrorstate=true;
  if(propmgr.getStatus()==0)
  {
      icon.loadFromFile("img/icon.png");


      font.loadFromFile(propmgr.getChallProperty(FONT_TYPE));
      std::string fontSize=propmgr.getChallProperty(FONT_SIZE);
      std::string fontColor=propmgr.getChallProperty(FONT_COLOR);

      testBase.setFont(font);
      testBase.setCharacterSize(std::stoi(fontSize));
      testBase.setColor(getColor(fontColor));

      gameerrorstate=false;

  }

}

void Game::getNextChall()
{
    actchall++;

    std::string actchallstr;
    actchallstr=propmgr.getActualChall(std::to_string(actchall));

    propmgr.setChall(actchallstr);

    loadResources();
    if(!gameerrorstate)
        chall.Init(propmgr);
    playSound();
}


void Game:: playSound()
{
    chall.playSound();

}

void Game:: stopSound()
{
//    sound.stop();
    chall.stopSound();

}


Game::Game(const std::string &winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
    actchall=1;

    std::string actchallstr;
    actchallstr=propmgr.getActualChall(std::to_string(actchall));
    propmgr.setChall(actchallstr);


    winstate=false;
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    loadResources();
    if(!gameerrorstate)
    {
        chall.Init(propmgr);

        playSound();

        window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());

        gameview.setCenter(GVIEW_X/2,GVIEW_Y/2);
        gameview.setSize(sf::Vector2f(GVIEW_X,GVIEW_Y));

        mmenu.Init(testBase, gameview.getCenter());
    }
};
