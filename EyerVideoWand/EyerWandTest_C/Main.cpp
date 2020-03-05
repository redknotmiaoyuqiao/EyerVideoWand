#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>
#include <EyerWand/InterfaceC.h>

TEST(EyerWand, Version){
    char version[128];
    int ret = eyer_wand_c_get_version(version);
    ASSERT_EQ(ret, 0) << "eyer_wand_c_get_version fail";
    EyerLog("Eyer Wand Version: %s\n", version);
}

TEST(EyerWand, Demo){
    int width = 1280;
    int height = 720;
    int fps = 30;

    void * builder = eyer_wand_c_builder_init("c_interface_test.mp4", width, height, fps);

    void * video_track = eyer_wand_c_video_track_init();

    eyer_wand_c_builder_add_video_track(builder, video_track);





    eyer_wand_c_video_track_uninit(video_track);

    eyer_wand_c_builder_uninit(builder);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
