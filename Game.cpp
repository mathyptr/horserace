#include "Game.hpp"

void Game::processEvent()
{
  sf::Event event;
  //events handler bad and slow. just using for closing the window
  while (window.pollEvent(event))
    if (event.type == sf::Event::Closed)
      window.close();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    window.close();
}


void Game::render()
{
  //clear old, draw new and show
  window.clear();

  window.draw(layerTop); //Mathy
  window.draw(layerAtmo); //Mathy
  window.draw(layerCenter); //Mathy
  window.draw(layerBottom); //Mathy


    window.draw(mmenu);



  window.draw(layerFront); //Mathy

  window.display();
}

void Game::Run()
{
  while (window.isOpen())
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
  icon.loadFromFile("img/icon.png");

  toppic.loadFromFile(mdbm.getChallProperty(TOP_PIC)); 
  bottompic.loadFromFile(mdbm.getChallProperty(BOTTOM_PIC));
  centerpic.loadFromFile(mdbm.getChallProperty(CENTER_PIC));
  atmopic.loadFromFile(mdbm.getChallProperty(ATMO_PIC));
  frontpic.loadFromFile(mdbm.getChallProperty(FRONT_PIC));
  soundchall=mdbm.getChallProperty(SOUND_CHALL);


  font.loadFromFile(mdbm.getChallProperty(FONT_TYPE));
  std::string fontSize=mdbm.getChallProperty(FONT_SIZE);
  std::string fontColor=mdbm.getChallProperty(FONT_COLOR);

  testBase.setFont(font);
  testBase.setCharacterSize(std::stoi(fontSize));
  testBase.setColor(getColor(fontColor));

  if (!buffersound.loadFromFile(soundchall))
      nosound=true;
}

void Game::getNextChall()
{
    actchall++;

    std::string actchallstr;
    actchallstr=mdbm.getActualChall(std::to_string(actchall));
//  mdbm.setChall("DESERT");
    mdbm.setChall(actchallstr);


    loadResources();
    playSound();
    InitLayer();
}

void Game::InitLayer()
{

    layerAtmo.Init(atmopic,ATMO_SPEED_FACTOR,sf::IntRect(0, 0, 800,180),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)));//MATHY
    layerBottom.Init(bottompic,BOTTOM_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)));//MATHY
    layerTop.Init(toppic,TOP_SPEED_FACTOR,sf::IntRect(0, 0, 800,480),sf::Vector2f(static_cast<float>(0),static_cast<float>(0)));//MATHY
    layerCenter.Init(centerpic,CENTER_SPEED_FACTOR,sf::IntRect(0, 280, 800, 250),sf::Vector2f(static_cast<float>(0),static_cast<float>(285)));//MATHY
    layerFront.Init(frontpic,FRONT_SPEED_FACTOR,sf::IntRect(0, 472, 800,200),sf::Vector2f(static_cast<float>(0),static_cast<float>(472)));//MATHY


    layerBottom.setPosition(0,472); //MATHY
    layerCenter.setPosition(0,285); //MATHY
    layerTop.setPosition(0,0); //MATHY
    layerAtmo.setPosition(0,0); //MATHY
    layerFront.setPosition(0,472); //MATHY

}

void Game:: playSound()
{
    sound.setBuffer(buffersound);
    sound.setLoop(true);
    sound.play();
}

void Game:: stopSound()
{
    sound.stop();
}


Game::Game(const std::string winTitle) : window(sf::VideoMode(800, 600, 32), winTitle)
{
  actchall=1;

    std::string actchallstr;
    actchallstr=mdbm.getActualChall(std::to_string(actchall));
//  mdbm.setChall("DESERT");
    mdbm.setChall(actchallstr);


  winstate=false;
  window.setMouseCursorVisible(false);
  window.setFramerateLimit(60);

  loadResources();

  playSound();

  InitLayer();


  window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());

  gameview.setCenter(GVIEW_X/2,GVIEW_Y/2);
  gameview.setSize(sf::Vector2f(GVIEW_X,GVIEW_Y));
  mmenu.Init(testBase, gameview.getCenter());


};
