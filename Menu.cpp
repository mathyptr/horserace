#include "Menu.hpp"


Menu::Menu():
  mSpeedPerSecond(800.f),
  mDistanceTravelled(0),
  mMaximumDistance(900.f)
{
  

  mfont.loadFromFile("roboto-black.ttf");


  sf::Color ccol=sf::Color::Red;
  unsigned int csize=24;

  mtestBase.setFont(mfont);
  mtestBase.setCharacterSize(csize);
  mtestBase.setColor(ccol);


  mBottomLeftLabel="";
  mTopRightLabel="";
  mBottomCenterLabel="";
  mTopCenterLabel="";
  mBottomRightLabel="";
  mTopLeftLabel="";


  mTopLeftPosition=sf::Vector2f(-390,-300);
  mTopCenterPosition=sf::Vector2f(-120,-300);
  mTopRightPosition=sf::Vector2f(240,-300);
  mBottomLeftPosition=sf::Vector2f(-390,270);
  mBottomCenterPosition=sf::Vector2f(-120,270);
  mBottomRightPosition=sf::Vector2f(280,270);
  
  mBottomLeft.setFont(mfont); // font is a sf::Font
  mBottomLeft.setString("");
  mBottomLeft.setCharacterSize(csize);
  mBottomLeft.setColor(ccol);

  mTopRight.setFont(mfont); // font is a sf::Font
  mTopRight.setString("");
  mTopRight.setCharacterSize(csize);
  mTopRight.setColor(ccol);

  mBottomCenter.setFont(mfont); // font is a sf::Font
  mBottomCenter.setString("");
  mBottomCenter.setCharacterSize(csize);
  mBottomCenter.setColor(ccol);

  mTopCenter.setFont(mfont); // font is a sf::Font
  mTopCenter.setString("");
  mTopCenter.setCharacterSize(csize);
  mTopCenter.setColor(ccol);

  mBottomRight.setFont(mfont); // font is a sf::Font
//  mBottomRight.setString("Level: " + std::to_string(0));
  mBottomRight.setString("");
  mBottomRight.setCharacterSize(csize);
  mBottomRight.setColor(ccol);

  mTopLeft.setFont(mfont); // font is a sf::Font
  mTopLeft.setString("");
  mTopLeft.setCharacterSize(csize);
  mTopLeft.setColor(ccol);


}

void Menu::Init(sf::Text testBase, const sf::Vector2f& position) 
{

//  mfont.loadFromFile(font);
  //mfont=font;
  mtestBase=testBase;
  mfont=*mtestBase.getFont();
  unsigned int csize=mtestBase.getCharacterSize();
  sf::Color ccol=mtestBase.getColor();



  mposition=position;

  mBottomLeftLabel="";
  mTopRightLabel="";
  mBottomCenterLabel="";
  mTopCenterLabel="";
  mBottomRightLabel="";
  mTopLeftLabel="";


  mTopLeftPosition=sf::Vector2f(-390,-300);
  mTopCenterPosition=sf::Vector2f(-120,-300);
  mTopRightPosition=sf::Vector2f(240,-300);
  mBottomLeftPosition=sf::Vector2f(-390,270);
  mBottomCenterPosition=sf::Vector2f(-120,270);
  mBottomRightPosition=sf::Vector2f(280,270);

  setPosition(position);
 
  
  mBottomLeft.setString("");
  mBottomLeft.setFont(mfont);
  mBottomLeft.setCharacterSize(csize);
  mBottomLeft.setColor(ccol);

  mTopRight.setString("");
  mTopRight.setFont(mfont);
  mTopRight.setCharacterSize(csize);
  mTopRight.setColor(ccol);

  mBottomCenter.setString("");
  mBottomCenter.setFont(mfont);
  mBottomCenter.setCharacterSize(csize);
  mBottomCenter.setColor(ccol);
  
  mTopCenter.setString("");
  mTopCenter.setFont(mfont);
  mTopCenter.setCharacterSize(csize);
  mTopCenter.setColor(ccol);

  mBottomRight.setString("");
  mBottomRight.setFont(mfont);
  mBottomRight.setCharacterSize(csize);
  mBottomRight.setColor(ccol);
//  mBottomRight.setString("Level: " + std::to_string(0));
  mBottomRight.setString("");

  mTopLeft.setString("");
  mTopLeft.setFont(mfont);
  mTopLeft.setCharacterSize(csize);
  mTopLeft.setColor(ccol);


}



void Menu::UpdateText( const sf::String &showEnemiesLeft, const  sf::String &livesLeft, const sf::String &bombsExploded,  const sf::String &timeRemaining, const sf::String &showLevel, const sf::String &speedometer)
{
  
  mBottomLeft.setString(showEnemiesLeft);
  mTopRight.setString(livesLeft);
  mBottomCenter.setString(bombsExploded);
  mTopCenter.setString(timeRemaining);
  mBottomRight.setString(showLevel);
  mTopLeft.setString(speedometer);

}


sf::Vector2f Menu::getPosition()
{
  return mposition;
}

void Menu::setPosition(sf::Vector2f pos)
{


  mposition=pos;
  mBottomLeft.setPosition(mposition+mBottomLeftPosition);
  mTopRight.setPosition(mposition+mTopRightPosition);
  mBottomCenter.setPosition(mposition+mBottomCenterPosition);
  mTopCenter.setPosition(mposition+mTopCenterPosition);
  mBottomRight.setPosition(mposition+mBottomRightPosition);
  mTopLeft.setPosition(mposition+mTopLeftPosition);
}


void Menu::move(float offsX, float offsY)
{
  mposition.x=offsX;
  mposition.y=offsY;
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

  target.draw(mBottomLeft,  states);
  target.draw(mTopRight);
  target.draw(mBottomCenter);
  target.draw(mTopCenter);
  target.draw(mBottomRight);
  target.draw(mTopLeft);

}


