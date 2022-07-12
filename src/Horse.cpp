#include "Horse.hpp"

Horse::Horse()
{
    zlevel = 0;
    horseNumber = 1;
    sheetIndex = 0;
    speedFactor = 1;
    speed = 0;
    sheets = {};
    sprite = MovingSprite();
    travelled=0;
    life=10;
    money=0;
    totalTravelled=0;
}

void Horse::setName(std::string name)
{
    horseName = name;
}

std::string Horse::getName()
{
    return horseName;
}

void Horse::init(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z)
{
    zlevel = z;
    horseNumber = number;
    sheetIndex = 0;
    speed = 0;
    travelled=0;
    setPropHorse();
    loadImage();
    setTexture();
    setHorsePosition(pos.x, pos.y);
    setHorseOrigin(orig.x, orig.y);
    sprite.init(sheets.at(sheetIndex), pos, z);
}

void Horse::setPropHorse()
{
    speedFactor = horseNumber;
}

void Horse::loadImage()
{
    std::string dir = "img/horse" + std::to_string(horseNumber);
    std::string filename;

    for (int i = 0; i < HORSE_SHEETS_NUM; i++)
    {
        filename = "/horse" + ((i != 0) ? std::to_string(i) : "") + ".png";
        sheets.push_back(sf::Texture());

        if(!sheets.at(i).loadFromFile(dir + filename))
            std::cerr << "file " << filename << " doesn't exist!\n";
        sheets.at(i).setSmooth(true);
    }
    sheetIndex = (int)(rand() % HORSE_SHEETS_NUM);
}

void Horse::setTexture()
{
    sprite.setTexture(sheets.at(sheetIndex));
    sheetIndex = (sheetIndex + 1) % HORSE_SHEETS_NUM;
}

void Horse::setScale(float factorX, float factorY)
{
    sprite.setScale(factorX, factorY);
}

float Horse::getSpeed()
{
    return speed;
}

void Horse::incSpeed(float sec)
{
    float adjsec = sec * 100;
    if (speed > -MAXSPEED && speed <= 0)
        speed -= (-MAXSPEED / (speed - SPEEDTHRESHOLD)) * SPEEDFACTOR * adjsec;
}

void Horse::decSpeed(float sec)
{
    float adjsec = sec * 100;
    speed -= speed * SPEEDSMOOTH * adjsec / MAXSPEED;
}

void Horse::incLife()
{
    if(life<10)
        life++;
}

bool Horse::decLife()
{
    if(life>0){
        life--;
        std::cout<<"hit! actual life: "<<life<<"\n";
        return true;
    }
    else
        return false;
}

int Horse::getLife(){
    return life;
}

int Horse::getMoney(){
    return money;
}

bool Horse::decMoney()
{
    if(money>0){
        money--;
        return true;
    }
    else
        return false;
}

void Horse::incMoney(int coin){
    money=money+coin;
}


void Horse::move(bool go, float sec)
{
    if (go)
    {
        setTexture();
        incSpeed(sec);
    }
    else
        decSpeed(sec);
//    std::cout << "speed:"<< speed << "second:"<< sec << std::endl;
    travelled+=-getSpeed()*sec;
//    std::cout << "Horse num: "<<horseNumber<<"; Speed: "<< getSpeed() << "; sec: "<< sec << "; travelled: "<< travelled << std::endl;
}
unsigned int Horse::getTravelled()
{
    return travelled;
}

float Horse::getTotalTravelled()
{
    return totalTravelled;
}

void Horse::setTotalTravelled(float inc)
{
    totalTravelled=totalTravelled+inc;
}

void Horse::move(float offsetX, float offsetY)
{
    float oX,oY;
    oX=speedFactor+offsetX/speedFactor;
    oY=offsetY*speedFactor;
//    incSpeed(oX);
    travelled+=abs(oX);
    setTexture();
    sprite.move(oX, oY);
//    std::cout <<"Horse num: "<<horseNumber<<"; Speed: "<< getSpeed() << "; travelled: "<< travelled << std::endl;
}

sf::FloatRect Horse::getHorseGlobalBounds() const
{
    return sprite.getBounds();
}

sf::Vector2f Horse::getHorsePosition() const
{
    return sprite.getPosition();
}

void Horse::setHorsePosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Horse::setHorseOrigin(float x, float y)
{
    sprite.setOrigin(x, y);
}
unsigned int Horse::getZLevel()
{
    return zlevel;
}

void Horse::draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z)
{
    if(sprite.getZLevel() == z)
        target.draw(sprite, states);
}
