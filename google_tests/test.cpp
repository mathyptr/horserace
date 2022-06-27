#include "./test.hpp"

TEST(horseraceTest, setZlevel){

    Horse horsePlayer;
    float posx,posy;
    unsigned int zlevel=1;
    posx=HORSE3_POSX;
    posy=HORSE3_POSY;
//    horsePlayer.init(1,sf::Vector2f(static_cast<float>(32),static_cast<float>(16)),sf::Vector2f(static_cast<float>(posx),static_cast<float>(posy)),zlevel);
    horsePlayer.setLevel(zlevel);
    ASSERT_EQ(horsePlayer.getLevel(),zlevel+1);
}

TEST(horseraceTest, setName){

    Horse horsePlayer;
    std::string name="Zoe";
    horsePlayer.setName(name);
    ASSERT_EQ(horsePlayer.getName(),"Salazar");
}