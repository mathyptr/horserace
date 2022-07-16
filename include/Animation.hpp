#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
    Animation();
    Animation(const sf::Texture& texture);
    void addFrameRect(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getFrameCount() const;
    const sf::IntRect& getFrameRect(std::size_t n) const;

private:
    std::vector<sf::IntRect> frames;
    const sf::Texture* texture;
};

#endif // ANIMATION_INCLUDE
