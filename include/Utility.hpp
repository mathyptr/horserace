#ifndef HORSERACE_UTILITY_HPP
#define HORSERACE_UTILITY_HPP

#include <SFML/Graphics.hpp>

namespace Utility
{
    const sf::Color getColor(std::string colorName);
    int* getRandom(int start, int end, const int count);
}
#endif
