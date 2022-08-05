#ifndef RANKINGMENU_INCLUDE
#define RANKINGMENU_INCLUDE

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Utility.hpp"
#include "PropertyManager.hpp"
#include "Horse.hpp"

#define MENU_SIZE_X 600
#define MENU_SIZE_Y 400
#define MENU_BG_COLOR sf::Color(220, 220, 220, 220)
#define PODIUM_BG_COLOR sf::Color(220, 220, 220, 255)

#define TITLE_MSG_RACE "Race ranking"
#define TITLE_MSG_GLOBAL "Global ranking"
#define TITLE_MSG_PODIUM "Podium"
#define TITLE_MSG_REWARD "Congratulations! You have reached 5 coins so you have won a life!"
#define TITLE_X 400
#define TITLE_X_PODIUM 430
#define TITLE_Y 150
#define REWARD_X 230
#define REWARD_Y 490
#define PANEL_X 400
#define PANEL_Y 50
#define IN_SPACING_X 150
#define IN_SPACING_Y 100
#define IN_OFFSET_X 150
#define IN_OFFSET_Y 75
#define FIRST_HORSE_POS sf::Vector2f(400, 330)
#define SECOND_HORSE_POS sf::Vector2f(210, 380)
#define THIRD_HORSE_POS sf::Vector2f(575, 410)

#define HORSE_IN_RACE 3

enum class RankingMode
{
    NONE, RACE, GLOBAL, PODIUM
};

class RankingMenu : public sf::Drawable
{
public:
    RankingMenu();
    RankingMenu(const sf::Vector2f& position, int horseNumbers[HORSE_IN_RACE]);
    void update(sf::Time deltaTime);
    RankingMode getRankingMode() const;
    void setRankingMode(RankingMode mode, const int* rank,bool msg);
    void typeWriter();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f position;

    sf::Font font;
    sf::Color fontColor;
    int fontSize;

    sf::Text title;
    sf::RectangleShape panel;
    sf::Text reward;

    std::vector<sf::RectangleShape> horsePanels;
    std::vector<sf::Text> horseRankLabels;
    std::vector<sf::Text> horseNameLabels;
    std::map<int, unique_ptr<Horse>> horses;
    int horseNumbers[HORSE_IN_RACE];
    unsigned int character=0;

    sf::Sprite podiumSprite;
    sf::Texture podiumTexture;
    sf::RectangleShape podiumBackground;

    RankingMode rankingMode;
};
#endif
