#include "StateRace.hpp"

StateRace::StateRace(Game *gamePtr) 
{
    game = gamePtr;
    stateName = GameState::STATE_RACE;
    subject = new Subject;
    observerMenuRace = new Observer(*subject);

    int selectedHorseNumber = ((StateHorseMenu*)(game->getStatePointer(GameState::STATE_HORSE_MENU)))->getSelectedHorseIndex() + 1;
    std::vector<int> numbers = { selectedHorseNumber };
    //altri due numeri random per gli avversari
    for (int i = 0; i < 2; i++)
    {
        int r = 0;
        do
            r = 1 + rand() % getDBInstance()->getHorseCount();
        while (std::count(numbers.begin(), numbers.end(), r) != 0);
        numbers.push_back(r);
    }
    
    horseNumbers = (int*)malloc(sizeof(int) * HORSE_COUNT);
    for (int i = 0; i < HORSE_COUNT; i++)
        horseNumbers[i] = numbers.data()[i];        

    race = new Race(game, horseNumbers,subject, false);
    rankingMenu = new RankingMenu(sf::Vector2f(GAME_VIEW_X / 2, GAME_VIEW_Y / 2), horseNumbers);
    rankingMenu->setRankingMode(RankingMode::NONE, nullptr,false);
    raceMenu = new RaceMenu(sf::Vector2f(GAME_VIEW_X / 2, GAME_VIEW_Y / 2),race->getCurrentTrackIndex());
}

void StateRace::draw(sf::RenderWindow &window) 
{
    race->render(window);
    window.draw(*raceMenu);
    window.draw(*rankingMenu);
}

void StateRace::update() 
{
    if(observerMenuRace->getMessage(LIFE_MSG)=="0")
    game->changeState(GameState::STATE_FINAL_RESULT);
    if(!race->horsePlayerFinished())
    {
        race->update(game->getDeltaTime());
        raceMenu->update(game->getDeltaTime(),race->getCurrentTrackIndex());
        raceMenu->setTrackText( observerMenuRace->getMessage(TRACK_MSG));
        raceMenu->setLifeText("Life: "+observerMenuRace->getMessage(LIFE_MSG));
        raceMenu->setMoneyText("Money: " + observerMenuRace->getMessage(MONEY_MSG));
    }
    else
    {
        if(rankingMenu->getRankingMode() == RankingMode::NONE){
            msg=race->reward();
            raceMenu->setLifeText("Life: "+observerMenuRace->getMessage(LIFE_MSG));
            raceMenu->setMoneyText("Money: " + observerMenuRace->getMessage(MONEY_MSG));
            int ranking[HORSE_COUNT];
            ranking[0]=stoi(observerMenuRace->getMessage(FIRST_MSG));
            ranking[1]=stoi(observerMenuRace->getMessage(SECOND_MSG));
            ranking[2]=stoi(observerMenuRace->getMessage(THIRD_MSG));
            rankingMenu->setRankingMode(RankingMode::RACE, ranking,msg);
    }
        rankingMenu->update(game->getDeltaTime());
    }
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Enter)
        {
            if(race->horsePlayerFinished())
            {
                switch (rankingMenu->getRankingMode())
                {
                    case RankingMode::RACE:
                        getGlobalRanking();
                        rankingMenu->setRankingMode(RankingMode::GLOBAL, globalRanking,msg);
                        break;
                    case RankingMode::GLOBAL:
                        rankingMenu->setRankingMode(RankingMode::NONE, nullptr,false);
                        if(!race->loadNextTrack(false))
                            game->changeState(GameState::STATE_FINAL_RESULT);
                        break;
                }
            }
        }
    }
}

GameState StateRace::getStateName() const
{
    return stateName;
}

void StateRace::getGlobalRanking()
{
    race->calculateGlobalRanking();
    globalRanking[0]=stoi(observerMenuRace->getMessage(FIRST_MSG));
    globalRanking[1]=stoi(observerMenuRace->getMessage(SECOND_MSG));
    globalRanking[2]=stoi(observerMenuRace->getMessage(THIRD_MSG));
}

int* StateRace::getHorseNumbers() const
{
    return horseNumbers;
}
