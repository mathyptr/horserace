#ifndef WEATHER_INCLUDE
#define WEATHER_INCLUDE
#include <SFML/Graphics.hpp>

class Weather : public sf::Drawable
{
public:
    Weather(const sf::Texture& texture,  float enemyMoveSpeed, float posx, float posy);
    void updateWeather(float speedX, float timeDelta);
    sf::FloatRect getWeatherGlobalBounds() const;
    sf::Vector2f getWeatherPosition() const;
    bool isWeatherAlive() const;

private:
    sf::Sprite      mSprite;
    float           mSpeedPerSecond;
    float           mDistanceTravelled;
    const float     mMaximumDistance;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
#endif
