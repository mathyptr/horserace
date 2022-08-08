#include "RankingMenu.hpp"

RankingMenu::RankingMenu()
{

}

RankingMenu::RankingMenu(const sf::Vector2f& position, int horseNumbers[HORSE_IN_RACE])
{
    font.loadFromFile("font/default_font.ttf");
    fontColor = Utility::getColor(getDBInstance()->getTrackProperty(1, FONT_COLOR));    //calcolare il vero track index
    fontSize = stoi(getDBInstance()->getTrackProperty(1, FONT_SIZE));                   //anche qua

    panel = sf::RectangleShape(sf::Vector2f(MENU_SIZE_X, MENU_SIZE_Y));
    panel.setFillColor(MENU_BG_COLOR);
    panel.setOrigin(panel.getLocalBounds().width / 2, panel.getLocalBounds().height / 2);
    panel.setPosition(position);

    title = sf::Text(TITLE_MSG_RACE, font, fontSize);
    title.setColor(fontColor);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(TITLE_X, TITLE_Y);
    title.setScale(1.25, 1.25);

    reward = sf::Text("", font, 12);
    reward.setColor(fontColor);
    reward.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    reward.setPosition(REWARD_X, REWARD_Y);
    reward.setScale(1.25, 1.25);

    for (int i = 0; i < HORSE_IN_RACE; i++)
    {
        horsePanels.push_back(sf::RectangleShape(sf::Vector2f(PANEL_X, PANEL_Y)));
        horsePanels[i].setFillColor(MENU_BG_COLOR);
        horsePanels[i].setOrigin(horsePanels[i].getLocalBounds().width / 2, horsePanels[i].getLocalBounds().height / 2);
        horsePanels[i].setPosition(position.x, position.y - IN_OFFSET_Y + i * IN_SPACING_Y);

        horseRankLabels.push_back(sf::Text(std::to_string((i + 1)), font, fontSize));
        horseRankLabels[i].setColor(fontColor);
        horseRankLabels[i].setOrigin(horseRankLabels[i].getLocalBounds().width / 2, horseRankLabels[i].getLocalBounds().height / 2);
        horseRankLabels[i].setPosition(position.x - IN_OFFSET_X, position.y - IN_OFFSET_Y + i * IN_SPACING_Y);

        this->horseNumbers[i] = horseNumbers[i];
        horses[horseNumbers[i]] = std::make_unique<Horse>(horseNumbers[i], sf::Vector2f(25, 25), sf::Vector2f(0, 0), 10); 
        horses[horseNumbers[i]]->setScale(0.75, 0.75);

        horseNameLabels.push_back(sf::Text(horses[horseNumbers[i]]->getName(), font, fontSize));
        horseNameLabels[i].setColor(fontColor);
        horseNameLabels[i].setOrigin(0, horseNameLabels[i].getLocalBounds().height / 2);
        horseNameLabels[i].setPosition(horseRankLabels[i].getPosition() + sf::Vector2f(IN_SPACING_X / 2, 0));
    }

    podiumTexture.loadFromFile(getDBInstance()->getMiscPath("podium_pic"));
    podiumSprite = sf::Sprite(podiumTexture);
    podiumSprite.setOrigin(podiumSprite.getLocalBounds().width / 2, podiumSprite.getLocalBounds().height / 2);
    podiumSprite.setPosition(400, 450);
    podiumBackground = sf::RectangleShape(sf::Vector2f(800, 600));
    podiumBackground.setFillColor(PODIUM_BG_COLOR);

    rankingMode = RankingMode::NONE;
}

void RankingMenu::update(sf::Time deltaTime)
{
    if(msgWin)
        typeWriter();
    if(rankingMode != RankingMode::NONE)
        for (int i = 0; i < horses.size(); i++)
            horses[horseNumbers[i]]->update(deltaTime);
}

RankingMode RankingMenu::getRankingMode() const
{
    return rankingMode;
}

void RankingMenu::setRankingMode(RankingMode mode, const int* rank,bool msg)
{
    rankingMode = mode;
    msgWin=msg;
    if(msgWin==false) {
        character=0;
        reward.setString("");
    }
    switch (rankingMode)
    {
        case RankingMode::NONE:
            return;
        case RankingMode::RACE:

            title.setString(TITLE_MSG_RACE);
            for (int i = 0; i < horses.size(); i++)
            {
                horses[rank[i]]->setScale(1, 1);
                horses[rank[i]]->setPosition(horseRankLabels[i].getPosition() + sf::Vector2f(2 * IN_SPACING_X, 0));
                horseNameLabels[i].setString(horses[rank[i]]->getName());
            }
            break;
        case RankingMode::GLOBAL:
            title.setString(TITLE_MSG_GLOBAL);
            for (int i = 0; i < horses.size(); i++)
            {
                horses[rank[i]]->setScale(1, 1);
                horses[rank[i]]->setPosition(horseRankLabels[i].getPosition() + sf::Vector2f(2 * IN_SPACING_X, 0));
                horseNameLabels[i].setString(horses[rank[i]]->getName());
            }
            break;
        case RankingMode::PODIUM:
            title.setString(TITLE_MSG_PODIUM);
            title.setPosition(TITLE_X_PODIUM,TITLE_Y);

            std::cout << "RankingMenu.cpp - podium ranking and horse numbers: ";
            for (int i = 0; i < horses.size(); i++)
            {
                std::cout << horseNumbers[i] << " ";
                std::cout << rank[i] << " ";
            }
            

            horses[rank[0]]->setPosition(FIRST_HORSE_POS);
            horses[rank[0]]->setScale(1.5, 1.5);
            horses[rank[1]]->setPosition(SECOND_HORSE_POS);
            horses[rank[1]]->setScale(1.5, 1.5);
            horses[rank[2]]->setPosition(THIRD_HORSE_POS);
            horses[rank[2]]->setScale(1.5, 1.5);
            break;
    }
}

void RankingMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(rankingMode == RankingMode::NONE)
        return;

    target.draw(panel, states);

    if(rankingMode == RankingMode::RACE || rankingMode == RankingMode::GLOBAL)
    {
        for (int i = 0; i < horses.size(); i++)
        {
            target.draw(horsePanels[i], states);
            target.draw(horseRankLabels[i], states);
            target.draw(horseNameLabels[i], states);
        }
    }
    else
    {
        target.draw(podiumBackground, states);
        target.draw(podiumSprite, states);
    }
    for (const auto &[number, horse] : horses)
        horse->draw(target, states, 10);

    target.draw(title, states);
    target.draw(reward, states);
}

void RankingMenu::typeWriter(){
    string str=TITLE_MSG_REWARD;
//    sf::Clock timer;
    if ((timer.getElapsedTime().asSeconds() > 0.01) && character < str.length())
    {
        character++;
        if (timer.getElapsedTime() > sf::milliseconds(1)){
        reward.setString(str.substr(0,character) );
        timer.restart();
        }
    }
}