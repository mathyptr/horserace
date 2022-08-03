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
#include "Obstacle.hpp"
#include "Layer.hpp"
#include "Menu.hpp"
#include "PropertyManager.hpp"
#include "AnimatedSprite.hpp"
#include "Observer.hpp"

#define HORSEZLEVELMIN 5
#define HORSEZLEVELMAX 8

#define DIFF_Y_BETWEEN 50
#define  HORSE1_POS_X 400
#define  HORSE1_POS_Y 450
#define  HORSE2_POS_X HORSE1_POS_X
#define  HORSE2_POS_Y HORSE1_POS_Y+DIFF_Y_BETWEEN
#define  HORSE3_POS_X HORSE1_POS_X
#define  HORSE3_POS_Y HORSE2_POS_Y+DIFF_Y_BETWEEN

#define HORSE_COUNT 3

#define NMAXPROB 10

#define EXP_SHEET_X 30
#define EXP_SHEET_Y 30

class Game;

class Race
{
public:
	Race(Game* gamePtr, int* horseNumbers,Subject* subject, const bool demo = false);
	void update(sf::Time deltaTime);
	void render(sf::RenderTarget &target);

	void horseMove(bool move, sf::Time deltaTime);
	bool horsePlayerFinished();
	unsigned int getCurrentTrackIndex();
	bool loadNextTrack(bool restart);
	const int* getRanking() const;
    bool isTimeToJump(sf::FloatRect horsepos,sf::FloatRect obstaclepos);

    std::shared_ptr<Horse> horsePlayer, horsePlayer2,horsePlayer3;
	unique_ptr<Track> track;

private:
    Game* game;
    bool demo;
    unsigned int currentTrackIndex;
    int ranking[HORSE_COUNT];
    float rspeed;
    unsigned int horseposymax[HORSE_COUNT];
	int weatherId;
    std::vector<std::shared_ptr<Weather>> weath;
    std::vector<std::shared_ptr<Obstacle>> obs;
    sf::Clock weatherDeltaTime;
    sf::Clock weatherSpawnTimer;
    sf::Clock obstacleDeltaTime;
    sf::Clock obstacleSpawnTimer;
    sf::Texture weathtexture;
    float weatherMoveSpeed;
    
    std::vector<std::shared_ptr<AnimatedSprite>> explosions;
    Animation explosionAnimation;
    sf::Texture explosionTexture;
    sf::Texture obstacletexture;
    sf::Clock explosionDeltaTimer;

    float speedX;
    bool winstate;
    bool gameoverstate;
    Subject* subject;

    void calculateRanking();
	void collision();
    bool collisionWeather(std::shared_ptr<Horse> horse,shared_ptr<Weather> w);
    void collisionObstacle();
    bool checkFinalLine();
    void horseMaxYCreate();
    int createProbability();
    void createWeather();
    void createObstacle();
    void drawWeather(sf::RenderTarget &target,unsigned int zlevel);
    void drawObstacle(sf::RenderTarget &target, unsigned int zlevel);
    void animateExplosion();
    void drawExplosions(sf::RenderTarget &target);
};
#endif
