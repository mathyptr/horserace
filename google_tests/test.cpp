#include "./test.hpp"

TEST(horseraceTest, setName){

    Horse horsePlayer;
    std::string name="Zoe";
        getDBInstance()->connect();
    horsePlayer.setName(name);
    ASSERT_EQ(horsePlayer.getName(),"Zoe");
}

TEST(trackTest, setNameTrack){
    getDBInstance()->connect();
    int currentTrackIndex=1;
    Track chall(getDBInstance()->getTrackProperty(currentTrackIndex, "name"));
    std::string name="Desert";
    chall.setName(name);
    ASSERT_EQ(chall.getName(),"Desert");
}


TEST(gameTest, checkWinner){
    getDBInstance()->connect();
    Horse *horsePlayer1,*horsePlayer2,*horsePlayer3;
    unsigned int zlevel;
    float posx,posy,posx2,posy2,posx3,posy3;

    posx3=HORSE3_POSX;
    posy3=HORSE3_POS_Y;
    posx2=HORSE2_POSX;
    posy2=HORSE2_POS_Y;
    posx=HORSE1_POS_X;
    posy=HORSE1_POS_Y;

    zlevel=5;
    horsePlayer2= new Horse (2,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx2),static_cast<float>(posy2)),zlevel);
    zlevel++;
    horsePlayer3= new Horse (3,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx3),static_cast<float>(posy3)),zlevel);
    zlevel++;
    horsePlayer1= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx),static_cast<float>(posy)),zlevel);

    float pathlen;
    float m;
    pathlen=500;
    for(m=0;m<pathlen;m+=10)
    {
        horsePlayer1->move(m,0,0);
        horsePlayer2->move(m,0,0);
        horsePlayer3->move(m,0,0);
        if (horsePlayer1->getTravelled() >= pathlen ||horsePlayer3->getTravelled() >= pathlen ||horsePlayer3->getTravelled() >= pathlen)
        {
            break;
        }
    }
    ASSERT_TRUE(horsePlayer1->getTravelled() >= pathlen);
    ASSERT_TRUE(horsePlayer2->getTravelled() < pathlen);
    ASSERT_TRUE(horsePlayer3->getTravelled() < pathlen);
}

TEST(horseTest, incMoney){
     getDBInstance()->connect();
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POS_X),static_cast<float>(HORSE1_POS_Y)),7);
    int startMoney,finalMoney;
    startMoney= horsePlayer->getMoney();
    horsePlayer->incMoney(100);
    finalMoney= horsePlayer->getMoney();;
    ASSERT_TRUE(finalMoney >startMoney);
}

TEST(horseTest, decLife){
    getDBInstance()->connect();
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POS_X),static_cast<float>(HORSE1_POS_Y)),7);
    int startLife,finalLife;
    startLife= horsePlayer->getLife();
    horsePlayer->decLife();
    finalLife= horsePlayer->getLife();;
    ASSERT_TRUE(startLife >finalLife);
}


TEST(raceTest, createProbability){
    int probability;
    int actprob;
    int prob[NMAXPROB];
    getDBInstance()->connect();
    for(int i=1,j=0;i<4;i++){
    probability=std::stoi(getDBInstance()->getProbability(std::to_string(1),std::to_string(i)));
    while(j<NMAXPROB&&probability>0){
        prob[j]=i;
        probability--;
        j++;
    }
    }
    actprob=prob[rand()%(10-1)];
    ASSERT_EQ(actprob,1);
}


TEST(raceTest, result){
    sf::View gameview;
    getDBInstance()->connect();
    int* ranking=(int*)malloc(sizeof(int) * 3);
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POS_X),static_cast<float>(HORSE1_POS_Y)),7);
    Horse *horsePlayer2= new Horse (2,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE2_POSX),static_cast<float>(HORSE2_POS_Y)),7);
    Horse *horsePlayer3= new Horse (3,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE3_POSX),static_cast<float>(HORSE3_POS_Y)),7);
    horsePlayer->setPosition(1000,200);
    horsePlayer2->setPosition(350,200);
    horsePlayer3->setPosition(200,200);
    std::vector<float> distances = { horsePlayer->getPosition().x, horsePlayer2->getPosition().x, horsePlayer3->getPosition().x };
    map<float, int> pairs = { { horsePlayer->getPosition().x, horsePlayer->getNumber() }, { horsePlayer2->getPosition().x, horsePlayer2->getNumber() }, { horsePlayer3->getPosition().x, horsePlayer3->getNumber() } };
    std::sort(distances.begin(), distances.end());
    for (int i = 0; i < HORSE_COUNT; i++)
        ranking[HORSE_COUNT - i - 1] = pairs[distances[i]];
    ASSERT_EQ(1,ranking[0]);
  }

TEST(stateTest, changeState){
    getDBInstance()->connect();
    Game* game= new Game("Horse Racing");
    game->changeState(GameState::STATE_RACE);
    ASSERT_EQ(game->getCurrentState()->getStateName(),GameState::STATE_RACE);
}


TEST(raceTest, collision){
    sf::View gameview;
    getDBInstance()->connect();
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POS_X),static_cast<float>(HORSE1_POS_Y)),7);
    bool collision=false;
    sf::Texture weathtexture;
    weathtexture.loadFromFile(getDBInstance()->getCurrentWeatherTexture(std::to_string(1)));
    Weather weath = Weather(weathtexture,100,HORSE1_POS_X,HORSE1_POS_Y,7,HORSE1_POS_Y);
    if(horsePlayer->getZLevel()==weath.getZLevel())
    {
        sf::FloatRect playerbox = horsePlayer->getGlobalBounds();
        if (playerbox.intersects(weath.getWeatherGlobalBounds()))
        {
            cout<<"Hit!!\n";
            collision=true;
        }
    }
    ASSERT_TRUE(collision);
}

TEST(observerTest, checkMsg){
    Subject* subject = new Subject;
    Observer * obsTest = new Observer(*subject);
    subject->CreateMessage("2",LIFE_MSG);
    string msg=obsTest->getMessage(LIFE_MSG);
    ASSERT_EQ("2",msg);
}