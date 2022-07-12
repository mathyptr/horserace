#include "Animation.hpp"

Animation::Animation() : texture(NULL)
{

}

Animation::Animation(const sf::Texture& texture)
{
   this->texture = &texture;
}

void Animation::addFrameRect(sf::IntRect rect)
{
    frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture& texture)
{
   this->texture = &texture;
}

const sf::Texture* Animation::getSpriteSheet() const
{
    return texture;
}

std::size_t Animation::getFrameCount() const
{
    return frames.size();
}

const sf::IntRect& Animation::getFrameRect(std::size_t n) const
{
    return frames[n];
}
