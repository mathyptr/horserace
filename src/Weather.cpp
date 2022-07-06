#include "Weather.hpp"

Weather::Weather(const sf::Texture& texture, float enemeyMoveSpeed, float posx, float posy) :
     mSprite(texture),
     mDistanceTravelled(0),
     mMaximumDistance(472.f)
{
    this->mSpeedPerSecond = enemeyMoveSpeed;
    this->mSprite.setPosition(posx, posy);
}

void Weather::updateWeather(float speedX, float timeDelta)
{
    auto distanceTravelledThisUpdate = mSpeedPerSecond * timeDelta;

    mDistanceTravelled += distanceTravelledThisUpdate;

    mSprite.move(speedX*timeDelta, distanceTravelledThisUpdate);

    if (mSprite.getPosition().x > 1600)
    {
        mSprite.setPosition(-800, mSprite.getPosition().y);
    }
    if (mSprite.getPosition().x < -800)
    {
        mSprite.setPosition(1600, mSprite.getPosition().y);
    }
}

sf::FloatRect Weather::getWeatherGlobalBounds() const
{
    return mSprite.getGlobalBounds();
}

sf::Vector2f Weather::getWeatherPosition() const
{
  return mSprite.getPosition();
}
bool Weather::isWeatherAlive() const
{
    return mDistanceTravelled < mMaximumDistance;
}

void Weather::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
