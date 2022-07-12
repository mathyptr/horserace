#include "Menu.hpp"

Menu::Menu():
  mSpeedPerSecond(800.f),
  mDistanceTravelled(0),
  mMaximumDistance(900.f)
{
  
  font.loadFromFile("font/default_font.ttf");

  sf::Color ccol=sf::Color::Red;
  unsigned int csize=24;

  testBase.setFont(font);
  testBase.setCharacterSize(csize);
  testBase.setColor(ccol);

  BottomLeftLabel="";
  TopRightLabel="";
  BottomCenterLabel="";
  TopCenterLabel="";
  BottomRightLabel="";
  TopLeftLabel="";


  TopLeftPosition=sf::Vector2f(-390,-300);
  TopCenterPosition=sf::Vector2f(-120,-300);
  TopRightPosition=sf::Vector2f(240,-300);
  BottomLeftPosition=sf::Vector2f(-390,270);
  BottomCenterPosition=sf::Vector2f(-120,270);
  BottomRightPosition=sf::Vector2f(280,270);
  
  BottomLeft.setFont(font);
  BottomLeft.setString("");
  BottomLeft.setCharacterSize(csize);
  BottomLeft.setColor(ccol);

  TopRight.setFont(font);
  TopRight.setString("");
  TopRight.setCharacterSize(csize);
  TopRight.setColor(ccol);

  BottomCenter.setFont(font);
  BottomCenter.setString("");
  BottomCenter.setCharacterSize(csize);
  BottomCenter.setColor(ccol);

  TopCenter.setFont(font);
  TopCenter.setString("");
  TopCenter.setCharacterSize(csize);
  TopCenter.setColor(ccol);

  BottomRight.setFont(font);
  BottomRight.setString("");
  BottomRight.setCharacterSize(csize);
  BottomRight.setColor(ccol);

  TopLeft.setFont(font);
  TopLeft.setString("");
  TopLeft.setCharacterSize(csize);
  TopLeft.setColor(ccol);

}

void Menu::Init(sf::Text testBase, const sf::Vector2f& pos)
{
  testBase=testBase;
  font=*testBase.getFont();
  unsigned int csize=testBase.getCharacterSize();
  sf::Color ccol=testBase.getColor();

  position=pos;

  BottomLeftLabel="";
  TopRightLabel="";
  BottomCenterLabel="";
  TopCenterLabel="";
  BottomRightLabel="";
  TopLeftLabel="";

  TopLeftPosition=sf::Vector2f(-390,-300);
  TopCenterPosition=sf::Vector2f(-120,-300);
  TopRightPosition=sf::Vector2f(240,-300);
  BottomLeftPosition=sf::Vector2f(-390,270);
  BottomCenterPosition=sf::Vector2f(-120,270);
  BottomRightPosition=sf::Vector2f(280,270);

  setPosition(position);
 
  
  BottomLeft.setString("");
  BottomLeft.setFont(font);
  BottomLeft.setCharacterSize(csize);
  BottomLeft.setColor(ccol);

  TopRight.setString("");
  TopRight.setFont(font);
  TopRight.setCharacterSize(csize);
  TopRight.setColor(ccol);

  BottomCenter.setString("");
  BottomCenter.setFont(font);
  BottomCenter.setCharacterSize(csize);
  BottomCenter.setColor(ccol);
  
  TopCenter.setString("");
  TopCenter.setFont(font);
  TopCenter.setCharacterSize(csize);
  TopCenter.setColor(ccol);

  BottomRight.setString("");
  BottomRight.setFont(font);
  BottomRight.setCharacterSize(csize);
  BottomRight.setColor(ccol);
  BottomRight.setString("");

  TopLeft.setString("");
  TopLeft.setFont(font);
  TopLeft.setCharacterSize(csize);
  TopLeft.setColor(ccol);
}



void Menu::UpdateText( const sf::String BottomL, const  sf::String TopR, const sf::String BottomC,  const sf::String TopC, const sf::String BottomR, const sf::String TopL)
{
  BottomLeft.setString(BottomL);
  TopRight.setString(TopR);
  BottomCenter.setString(BottomC);
  TopCenter.setString(TopC);
  BottomRight.setString(BottomR);
  TopLeft.setString(TopL);

}


sf::Vector2f Menu::getPosition() const
{
  return position;
}

void Menu::setPosition(sf::Vector2f pos)
{
  position=pos;
  BottomLeft.setPosition(position+BottomLeftPosition);
  TopRight.setPosition(position+TopRightPosition);
  BottomCenter.setPosition(position+BottomCenterPosition);
  TopCenter.setPosition(position+TopCenterPosition);
  BottomRight.setPosition(position+BottomRightPosition);
  TopLeft.setPosition(position+TopLeftPosition);
}


void Menu::move(float offsX, float offsY)
{
  position.x=offsX;
  position.y=offsY;
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(BottomLeft,  states);
  target.draw(TopRight);
  target.draw(BottomCenter);
  target.draw(TopCenter);
  target.draw(BottomRight);
  target.draw(TopLeft);
}
