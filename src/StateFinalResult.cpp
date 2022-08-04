#include "StateFinalResult.hpp"

StateFinalResult::StateFinalResult(Game *gamePtr)
{
    game = gamePtr;
    stateName = GameState::STATE_FINAL_RESULT;
    StateRace* sr = (StateRace*)(game->getStatePointer(GameState::STATE_RACE));

    rankingMenu = new RankingMenu(sf::Vector2f(GAME_VIEW_X / 2, GAME_VIEW_Y / 2), sr->getHorseNumbers());
    ranking = sr->getGlobalRanking();
    rankingMenu->setRankingMode(RankingMode::PODIUM, ranking,false);

    game->music.stop();
    game->music.openFromFile(getDBInstance()->getMiscPath("podium_music"));
    game->music.play();
}

void StateFinalResult::draw(sf::RenderWindow &window)
{
    window.draw(*rankingMenu);
}

/* void StateFinalResult::typeWriter(){
    std::string str=game->race->finalResult();
    if ((timer.getElapsedTime().asSeconds() > 0.01) && game->race->character < str.length())
    {
        game->race->character++;
        if (timer.getElapsedTime() > sf::milliseconds(1)){
            testTopCenter=(str.substr(0,game->race->character)) ;
            timer.restart();
        }
    }
}
 */

void StateFinalResult::update() 
{
    rankingMenu->update(game->getDeltaTime());
}

void StateFinalResult::handleInput(sf::Event event, sf::RenderWindow& window) 
{
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            game->restart();
        }
    }
}

GameState StateFinalResult::getStateName() const
{
    return stateName;
}
