#include "Horse.hpp"


 Horse:: Horse()
{
  zlevel=0;
  num=1;
  indeximg=0;
  speedFactor=1;
  speedX = 0;
  travelled=0;
}
void Horse::setName(std::string name)
{
    horseName=name;
}

std::string Horse::getName()
{
    return horseName;
}
void Horse::init(unsigned int n,sf::Vector2f orig,sf::Vector2f pos, unsigned int lev)
{
  zlevel=lev;
  num=n;
  indeximg=0;
  speedX=0;
  travelled=0;
  setPropHorse();
  loadImage();
  setTexture();
  setHorsePosition(pos.x,pos.y);
  setHorseOrigin(orig.x,orig.y);
}

void Horse::setPropHorse()
{
  speedFactor=num;

}

void Horse::loadImage() {

      std::string snum=std::to_string(num);
      std::string imgdir="img/horse";
      std::string filename;

      filename="/horse.png";
      if(!horse1.loadFromFile(imgdir +  snum + filename))
          std::cout<<"file "<< filename <<" doesn't exist"<<std::endl;
      horse1.setSmooth(true);
      Sprite.setTexture(horse1);

      filename="/horse1.png";
      if(!horse2.loadFromFile(imgdir +  snum + filename))
        std::cout<<"file "<< filename <<" doesn't exist"<<std::endl;
      horse2.setSmooth(true);

      filename="/horse2.png";
      if(!horse3.loadFromFile(imgdir +  snum + filename))
        std::cout<<"file "<< filename <<" doesn't exist"<<std::endl;
      horse3.setSmooth(true);

      filename="/horse3.png";
      if(!horse4.loadFromFile(imgdir +  snum + filename))
        std::cout<<"file "<< filename <<" doesn't exist"<<std::endl;
      horse4.setSmooth(true);

      filename="/horse4.png";
      if(!horse5.loadFromFile(imgdir +  snum + filename))
        std::cout<<"file "<< filename <<" doesn't exist"<<std::endl;
      horse5.setSmooth(true);

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
    float adjsec=sec*100;
    if (speedX > -MAXSPEED && speedX<=0)
        speedX -= (-MAXSPEED/(speedX-SPEEDTRHESOLD))*SPEEDFACTOR*adjsec;
}
void Horse::decSpeed(float sec)
{
    float adjsec=sec*100;
    speedX -= speedX*SPEEDSMOOTH*adjsec/MAXSPEED;
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
    std::cout << "speedX:"<< speedX << "second:"<< sec << std::endl;
    travelled+=-getSpeed()*sec;
    std::cout << "Speed: "<< getSpeed() << std::endl;
    std::cout << "sec: "<< sec << std::endl;
    std::cout << "travelled: "<< travelled << std::endl;
}
unsigned int Horse::getTravelled()
{
    return travelled;
}
void Horse::move(float offsetX, float offsetY)
{
  float oX,oY;
  oX=offsetX/speedFactor;
  oY=offsetY/speedFactor;

  Sprite.move(oX, oY);
}

sf::FloatRect Horse::getHorseGlobalBounds() const
{
    return Sprite.getGlobalBounds();
}

sf::Vector2f Horse::getHorsePosition() const
{
  return Sprite.getPosition();
}
void Horse::setHorsePosition(float x, float y)
{
  Sprite.setPosition(x,y);
}

void Horse::setHorseOrigin(float x, float y)
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
