#include "./test.hpp"

TEST(spriteTest, setZlevel){

    MovingSprite sprite;
    float posx,posy;
    unsigned int zlevel=1;
    posx=HORSE3_POSX;
    posy=HORSE3_POSY;
    sprite.setZLevel(zlevel);
    ASSERT_EQ(sprite.getZLevel(),zlevel);
}

TEST(horseraceTest, setName){

    Horse horsePlayer;
    std::string name="Zoe";
    horsePlayer.setName(name);
    ASSERT_EQ(horsePlayer.getName(),"Zoe");
}

TEST(trackTest, setNameTrack){
    PropertyManager propmgr(true);
    int currentTrackIndex=1;
    Track chall(propmgr, propmgr.getTrackProperty(currentTrackIndex, "name"));
    std::string name="Desert";
    chall.setName(name);
    ASSERT_EQ(chall.getName(),"Desert");
}



TEST(gameTest, checkWinner){
    Horse *horsePlayer1,*horsePlayer2,*horsePlayer3;

    unsigned int zlevel;
    float posx,posy,posx2,posy2,posx3,posy3;

    posx3=HORSE3_POSX;
    posy3=HORSE3_POSY;
    posx2=HORSE2_POSX;
    posy2=HORSE2_POSY;
    posx=HORSE1_POSX;
    posy=HORSE1_POSY;

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
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POSX),static_cast<float>(HORSE1_POSY)),7);
    int startMoney,finalMoney;
    startMoney= horsePlayer->getMoney();
    horsePlayer->incMoney(100);
    finalMoney= horsePlayer->getMoney();;
    ASSERT_TRUE(finalMoney >startMoney);
}

TEST(horseTest, decLife){
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POSX),static_cast<float>(HORSE1_POSY)),7);
    int startLife,finalLife;
    startLife= horsePlayer->getLife();
    horsePlayer->decLife();
    finalLife= horsePlayer->getLife();;
    ASSERT_TRUE(startLife >finalLife);
}

TEST(raceTest, createProbability){
    sf::View gameview;
    int weathIndex;
    PropertyManager propmgr =  PropertyManager(true);
    Race* race= new Race(propmgr,gameview.getCenter());
    weathIndex= race->weatherId;
    ASSERT_EQ(weathIndex,1);
}

TEST(raceTest, result){
    sf::View gameview;
    PropertyManager propmgr =  PropertyManager(true);
    Race* race= new Race(propmgr,gameview.getCenter());
    Horse *horsePlayer= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE1_POSX),static_cast<float>(HORSE1_POSY)),7);
    Horse *horsePlayer2= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE2_POSX),static_cast<float>(HORSE2_POSY)),7);
    Horse *horsePlayer3= new Horse (1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(HORSE3_POSX),static_cast<float>(HORSE3_POSY)),7);
    horsePlayer->setPosition(1000,200);
    horsePlayer2->setPosition(350,200);
    horsePlayer3->setPosition(200,200);
    std::string str="Result\n1. Player\n2. Salazar\n3. Sarah\n";
    ASSERT_EQ(str,race->order({{"Player",horsePlayer->getPosition().x},{"Salazar",horsePlayer2->getPosition().x},{"Sarah",horsePlayer3->getPosition().x}}));
}