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