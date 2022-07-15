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

    Track chall;
    std::string name="Desert";
    chall.setName(name);
    ASSERT_EQ(chall.getName(),"Desert");
}



TEST(gameTest, checkWinner){
    Horse horsePlayer1,horsePlayer2,horsePlayer3;

    unsigned int zlevel;
    float posx,posy,posx2,posy2,posx3,posy3;

    posx3=HORSE3_POSX;
    posy3=HORSE3_POSY;
    posx2=HORSE2_POSX;
    posy2=HORSE2_POSY;
    posx=HORSE1_POSX;
    posy=HORSE1_POSY;
    zlevel=5;
    horsePlayer2.init(2,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx2),static_cast<float>(posy2)),zlevel);
    zlevel++;
    horsePlayer3.init(3,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx3),static_cast<float>(posy3)),zlevel);
    zlevel++;
    horsePlayer1.init(1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx),static_cast<float>(posy)),zlevel);

    unsigned pathlen;
    float m;
    pathlen=500;
    for(m=0;m<pathlen;m+=10)
    {
        horsePlayer1.move(m,0);
        horsePlayer2.move(m,0);
        horsePlayer3.move(m,0);
        if (horsePlayer1.getTravelled() >= pathlen ||horsePlayer3.getTravelled() >= pathlen ||horsePlayer3.getTravelled() >= pathlen)
        {
            break;
        }
    }
    ASSERT_TRUE(horsePlayer1.getTravelled() >= pathlen);
    ASSERT_TRUE(horsePlayer2.getTravelled() < pathlen);
    ASSERT_TRUE(horsePlayer3.getTravelled() < pathlen);
}
