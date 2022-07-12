#ifndef WEATHER_INCLUDE
#define WEATHER_INCLUDE
#include <SFML/Graphics.hpp>

class Weather : public sf::Drawable
{
public:
    Weather(const sf::Texture& texture,  float enemyMoveSpeed, float posx, float posy,unsigned int zlevel,unsigned int maxy);
    void updateWeather(float speedX, float timeDelta);
    sf::FloatRect getWeatherGlobalBounds() const;
    sf::Vector2f getWeatherPosition() const;
    unsigned int getZLevel() const;
    bool isWeatherAlive() const;

private:
    sf::Sprite      mSprite;
    unsigned int zlevel;
    unsigned int maxy;
    float           mSpeedPerSecond;
    float           mDistanceTravelled;
    const float     mMaximumDistance;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
#endif
