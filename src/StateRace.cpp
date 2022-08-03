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
    rankingMenu->setRankingMode(RankingMode::NONE, nullptr);
    raceMenu = new RaceMenu(sf::Vector2f(GAME_VIEW_X / 2, GAME_VIEW_Y / 2));
}

void StateRace::draw(sf::RenderWindow &window) 
{
    race->render(window);
    window.draw(*raceMenu);
    window.draw(*rankingMenu);
}

void StateRace::update() 
{
    if(!race->horsePlayerFinished())
    {
        race->update(game->getDeltaTime());
        raceMenu->update(game->getDeltaTime());
        raceMenu->setTrackText(race->track->getName());
        raceMenu->setLifeText("Life: "+observerMenuRace->getMessage(LIFE_MSG));
        raceMenu->setMoneyText("Money: " + std::to_string(race->horsePlayer->getMoney()));
    }
    else
    {
        if(rankingMenu->getRankingMode() == RankingMode::NONE)
            rankingMenu->setRankingMode(RankingMode::RACE, race->getRanking());
        rankingMenu->update(game->getDeltaTime());
    }
}

void StateRace::handleInput(sf::Event event, sf::RenderWindow &window)
{
    //ogni volta che la tappa finisce:
    //si va alla successiva (negozio?)
    //se sono finite, si va alla premiazione

    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Enter)
        {
            if(race->horsePlayerFinished())
            {
                switch (rankingMenu->getRankingMode())
                {
                    case RankingMode::RACE:
                        calculateRanking();
                        rankingMenu->setRankingMode(RankingMode::GLOBAL, getGlobalRanking());
                        break;
                    case RankingMode::GLOBAL:
                        rankingMenu->setRankingMode(RankingMode::NONE, nullptr);
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

void StateRace::calculateRanking()
{
    race->horsePlayer->setTotalTravelled(race->horsePlayer->getPosition().x);
    race->horsePlayer2->setTotalTravelled(race->horsePlayer2->getPosition().x);
    race->horsePlayer3->setTotalTravelled(race->horsePlayer3->getPosition().x);

    std::vector<float> distances = { race->horsePlayer->getTotalTravelled(), race->horsePlayer2->getTotalTravelled(), race->horsePlayer3->getTotalTravelled() };
    map<float, int> pairs = { { race->horsePlayer->getTotalTravelled(), race->horsePlayer->getNumber() }, { race->horsePlayer2->getTotalTravelled(), race->horsePlayer2->getNumber() }, { race->horsePlayer3->getTotalTravelled(), race->horsePlayer3->getNumber() } };

    std::sort(distances.begin(), distances.end());
    for (int i = 0; i < HORSE_COUNT; i++)
        globalRanking[HORSE_COUNT - i - 1] = pairs[distances[i]];
}

const int* StateRace::getGlobalRanking() const
{
    return globalRanking;
}

int* StateRace::getHorseNumbers() const
{
    return horseNumbers;
}
