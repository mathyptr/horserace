#include "Utility.h"

sf::Color Utility::getColor(std::string colorName)
{
    sf::Color c;

    std::transform(colorName.begin(), colorName.end(), colorName.begin(), ::toupper);
    if(colorName.compare("BLACK") == 0)
        c = sf::Color::Black;
    else if(colorName.compare("RED") == 0)
        c = sf::Color::Red;
    else if(colorName.compare("GREEN") == 0)
        c = sf::Color::Green;
    else if(colorName.compare("BLUE") == 0)
        c = sf::Color::Blue;
    else if(colorName.compare("YELLOW") == 0)
        c = sf::Color::Yellow;
    else if(colorName.compare("MAGENTA") == 0)
        c = sf::Color::Magenta;
    else if(colorName.compare("CYAN") == 0)
        c = sf::Color::Cyan;
    else if(colorName.compare("TRANSPARENT") == 0)
        c = sf::Color::Transparent;

    return c;
}