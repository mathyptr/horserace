#include "Horse.hpp"

Horse::Horse()
{

}

Horse::Horse(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z, bool mode) : AnimatedSprite(sf::seconds(0.05f))
{
    cpu=mode;
    horseNumber = number;
    horseName = getDBInstance()->getHorseProperty(horseNumber, "name");
    totalTravelled = 0;
    jumpon= false;
    setPropHorse(1);
    zLevel = z;
    life = 10;
    money = 0;
    this->pos=pos;
    startPos(orig, pos, 1);
    sf::Texture* tex = new sf::Texture();
    tex->setSmooth(true);
    tex->loadFromFile(getDBInstance()->getHorseProperty(horseNumber, "texture"));
    texture = tex;
    Animation* an = new Animation(*texture);
    for (int i = 0; i < SHEET_COUNT; i++)
        an->addFrameRect(sf::IntRect(0, i * SHEET_HEIGHT, SHEET_WIDTH, SHEET_HEIGHT));
    play(*an);
}

void Horse::startPos(sf::Vector2f orig, sf::Vector2f pos,int indexTrack)
{
    setPropHorse(indexTrack);
    speed = 0;
    travelled = 0;
    setPosition(pos);
    setOrigin(orig);
}

int Horse::getNumber() const
{
    return horseNumber;
}

void Horse::setName(std::string name)
{
    horseName = name;
}

std::string Horse::getName() const
{
    return horseName;
}

void Horse::setPropHorse(int indexTrack)
{
    speedFactor = std::stoi(getDBInstance()->getHorse_Prop(horseNumber, "speed",indexTrack));
}

float Horse::getSpeed() const
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

void Horse::setSpeed(float sec)
{
   speed=sec;
}

void Horse::incLife()
{
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

int Horse::getLife() const
{
    return life;
}

int Horse::getMoney() const
{
    return money;
}

bool Horse::decMoney(int coin)
{
    if(money>=coin){
        money=money-coin;
        return true;
    }
    else
        return false;
}

void Horse::incMoney(int coin)
{
    money=money+coin;
}

void Horse::move(bool go, float sec)
{
    if(jumpon)
        setPosition(sf::Vector2f(pos.x,static_cast<float>(yOnJump())));

    if (go)
    {
        update(sf::seconds(sec));
        incSpeed(sec);
    }
    else
        decSpeed(sec);
    travelled -= getSpeed() * sec;
}

bool Horse::CPU()
{
    return cpu;
}

void Horse::SetJumpON(){
    if(jumpon==false)
        horseplayerJumpTimer.restart();
    jumpon=true;
}

float   Horse::yOnJump()
{
    float y,v0y;
    float t;
    const auto elapsed= horseplayerJumpTimer.getElapsedTime();
    t=elapsed.asSeconds();
    v0y=VO_Y;
    y=0.5*GRAVITY*pow(t,PW)-v0y*t+pos.y;
    if(y>=pos.y)
    {
        y=pos.y;
        jumpon=false;
        horseplayerJumpTimer.restart();
    }
    return y;
}

unsigned int Horse::getTravelled() const
{
    return travelled;
}

float Horse::getTotalTravelled() const
{
    return totalTravelled;
}

void Horse::setTotalTravelled(float inc)
{
    totalTravelled = totalTravelled + inc;
}

void Horse::move(float offsetX, float offsetY, float sec)
{
    float oX,oY;
    oX = speedFactor + offsetX / speedFactor;
    oY = offsetY * speedFactor;
    travelled += abs(oX);
    if(jumpon){
        setPosition(sf::Vector2f(AnimatedSprite::getGlobalBounds().left,static_cast<float>(yOnJump())));
        if(offsetX!=0)
           oX =0.05;
    }
    AnimatedSprite::move(oX, oY);
    update(sf::seconds(sec));
}

void Horse::draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
