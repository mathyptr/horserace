#include "Horse.hpp"


 Horse:: Horse()
{
  zlevel=0;
  num=1;
  indeximg=0;
  speedFactor=1;
  speedX = 0;
}


void Horse::init(unsigned int n,sf::Vector2f orig,sf::Vector2f pos, unsigned int lev)
{
  zlevel=lev;
  num=n;
  indeximg=0;
  setPropHorse();
  loadImage();
  this->setTexture();
  this->setPlayerPosition(pos.x,pos.y);
  this->setPlayerOrigin(orig.x,orig.y);
}

void Horse::setPropHorse()
{
  speedFactor=num;

}

void Horse::loadImage() {

//		try {
      std::string snum=std::to_string(num);

      horse1.loadFromFile("img/horse" +  snum + "/horse.png");
      horse1.setSmooth(true);
      Sprite.setTexture(horse1);

      horse2.loadFromFile("img/horse" +  snum + "/horse1.png");
      horse2.setSmooth(true);

      horse3.loadFromFile("img/horse" +  snum + "/horse2.png");
      horse3.setSmooth(true);

      horse4.loadFromFile("img/horse" +  snum + "/horse3.png");
      horse4.setSmooth(true);

      horse5.loadFromFile("img/horse" +  snum + "/horse4.png");
      horse5.setSmooth(true);

//		} catch (Exception e) {
//			printf("errore input");
//		}
		indeximg = (int) (rand() * 5);
	}


void Horse::setTexture()
{
  
  if(indeximg==0)
    Sprite.setTexture(horse1);
  else if(indeximg==1)
    Sprite.setTexture(horse2);
  else if(indeximg==2)
    Sprite.setTexture(horse3);
  else if(indeximg==3)
    Sprite.setTexture(horse4);
  else
    Sprite.setTexture(horse5);

  indeximg = (indeximg + 1) % NUM_IMG_HORSE;

}

void Horse::setScale(float factorX, float factorY)
{
  Sprite.setScale(factorX, factorY);
}

float Horse::getSpeed()
{
 return speedX;
}


void Horse::incSpeed(float sec)
{
    if (speedX > -MAXSPEED && speedX<=0)
        speedX -= (-MAXSPEED/(speedX-SPEEDTRHESOLD))*SPEEDFACTOR;
}
void Horse::decSpeed(float sec)
{
    speedX -= speedX*SPEEDSMOOTH/MAXSPEED;
}
void Horse::move(sf::Keyboard::Key key, float sec)
{
    if (key==sf::Keyboard::Right)
    {
        setTexture();
        incSpeed(sec);
    }
    else
        decSpeed(sec);
    std::cout << "speedX:"<< speedX << std::endl;
}

void Horse::move(float offsetX, float offsetY)
{
  float oX,oY;
  oX=offsetX/speedFactor;
  oY=offsetY/speedFactor;

  Sprite.move(oX, oY);
}

sf::FloatRect Horse::getPlayerGlobalBounds() const
{
    return Sprite.getGlobalBounds();
}

sf::Vector2f Horse::getPlayerPosition() const
{
  return Sprite.getPosition();
}
void Horse::setPlayerPosition(float x, float y)
{
  Sprite.setPosition(x,y);
}

void Horse::setPlayerOrigin(float x, float y)
{
  Sprite.setOrigin(x,y);
}

void Horse::setLevel(unsigned int lev)
{
    zlevel=lev;
}
unsigned int Horse::getLevel() const
{
    return zlevel;
}


void Horse::draw(sf::RenderTarget &target, sf::RenderStates states,unsigned int zlevel)
{
    if(getLevel()==zlevel)
      target.draw(Sprite, states);
}
