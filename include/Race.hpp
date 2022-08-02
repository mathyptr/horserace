#ifndef RACE_INCLUDE
#define RACE_INCLUDE
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Game.hpp"
#include "Track.hpp"
#include "Horse.hpp"
#include "Weather.hpp"
#include "Layer.hpp"
#include "Menu.hpp"
#include "PropertyManager.hpp"
#include "AnimatedSprite.hpp"

#define HORSEZLEVELMIN 5
#define HORSEZLEVELMAX 8

#define HORSE1_POS_X 400
#define HORSE1_POS_Y 472
#define HORSE2_POS_X HORSE1_POS_X
#define HORSE2_POS_Y 522
#define HORSE3_POS_X HORSE1_POS_X
#define HORSE3_POS_Y 562
#define HORSE_COUNT 3

#define NMAXPROB 10

#define EXP_SHEET_X 30
#define EXP_SHEET_Y 30

class Game;

class Race
{
public:
	Race(Game* gamePtr, int* horseNumbers, const bool demo = false);
	void update(sf::Time deltaTime);
	void render(sf::RenderTarget &target);

	void horseMove(bool move, sf::Time deltaTime);
	bool horsePlayerFinished();
	unsigned int getCurrentTrackIndex();
	bool loadNextTrack(bool restart);
	const int* getRanking() const;

	unique_ptr<Horse> horsePlayer, horsePlayer2, horsePlayer3;
	unique_ptr<Track> track;
private:
    Game* game;
    bool demo;
    unsigned int currentTrackIndex;
    int ranking[HORSE_COUNT];

    unsigned int horseposymax[HORSE_COUNT];
	int weatherId;
    std::vector<std::shared_ptr<Weather>> weath;
    sf::Clock weatherDeltaTime;
    sf::Clock weatherSpawnTimer;
    sf::Texture weathtexture;
    float weatherMoveSpeed;
    
    std::vector<std::shared_ptr<AnimatedSprite>> explosions;
    Animation explosionAnimation;
    sf::Texture explosionTexture;
    sf::Clock explosionDeltaTimer;

    float speedX;
    bool winstate;
    bool gameoverstate;

    void calculateRanking();
	void collision();
    bool checkFinalLine();
    void horseMaxYCreate();
    int createProbability();
    void createWeather();
    void drawWeather(sf::RenderTarget &target);
    void animateExplosion();
    void drawExplosions(sf::RenderTarget &target);
};
#endif
