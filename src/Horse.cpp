#include "Horse.hpp"

Horse::Horse()
{

}

Horse::Horse(unsigned int number, sf::Vector2f orig, sf::Vector2f pos, unsigned int z) : AnimatedSprite(sf::seconds(0.05f))
{
    horseName = "My horse";
    horseNumber = number;
    speed = 0;
    travelled = 0;
    totalTravelled = 0;
    setPropHorse();

    setPosition(pos);
    setOrigin(orig);
    zLevel = z;

    life = 10;
    money = 0;

    sf::Texture* tex = new sf::Texture();
    tex->setSmooth(true);
    if(!tex->loadFromFile("./img/horse" + std::to_string(horseNumber) + ".png"))
        std::cerr << "Texture cavallo non caricata correttamente.\n";
    texture = tex;

    Animation* an = new Animation(*texture);
    for (int i = 0; i < SHEET_COUNT; i++)
        an->addFrameRect(sf::IntRect(0, i * SHEET_HEIGHT, SHEET_WIDTH, SHEET_HEIGHT));
    play(*an);
}

void Horse::setName(std::string name)
{
    horseName = name;
}

std::string Horse::getName() const
{
    return horseName;
}

void Horse::setPropHorse()
{
    speedFactor = horseNumber;
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

int Horse::getLife() const
{
    return life;
}

int Horse::getMoney() const
{
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

void Horse::incMoney(int coin)
{
    money=money+coin;
}

void Horse::move(bool go, float sec)
{
    if (go)
    {
        //setTexture();
        update(sf::seconds(sec));
        incSpeed(sec);
    }
    else
        decSpeed(sec);

    travelled -= getSpeed() * sec;
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
    AnimatedSprite::move(oX, oY);
    update(sf::seconds(sec));
}

void Horse::draw(sf::RenderTarget &target, sf::RenderStates states, unsigned int z)
{
    if(getZLevel() == z)
        AnimatedSprite::draw(target, states);
}
