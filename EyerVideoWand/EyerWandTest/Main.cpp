#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>

TEST(EyerWand, EyerWandRes_Base){

}

TEST(EyerBuilder, EyerBuilder){
    Eyer::EyerWandBuilder builder("/home/redknot/Videos/builder_mp4.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(25);
    builder.Process();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
