#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>


TEST(EyerWand, EyerWandRes_Base){

}

TEST(EyerVideoTrack, EyerWandRes_Base){
    /*
    Eyer::EyerWandBuilder builder("./struct_builder_mp4.mp4");

    Eyer::EyerVideoTrack videoTrack;

    for(int i=0;i<1000;i++){
        Eyer::EyerVideoLayout layout;
        layout.SetFrame(i, i + 1000);

        Eyer::EyerVideoFragment videoFragment;
        videoFragment.SetFrameIndex(i, i + 1000);
        videoFragment.SetFrameTime(0.0, 10.0);

        layout.AddVideoFragment(videoFragment);

        videoTrack.AddLayout(layout);
    }

    int frameCount = videoTrack.GetFrameCount();
    ASSERT_EQ(frameCount, 999 + 1000) << "Get Frame Count Error!!!!";

    builder.AddVideoTrack(videoTrack);
     */
}

TEST(EyerVideoBuild, EyerVideoBuild_Test){
    int fps = 30;

    Eyer::EyerWandBuilder builder("./struct_builder_vidoe_mp4.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    Eyer::EyerVideoTrack videoTrack;

<<<<<<< HEAD
    Eyer::EyerVideoLayout layout;
    layout.SetFrame(0, fps * 40
    -);
=======
    Eyer::EyerVideoLayer layer;
    layer.SetFrame(0, fps * 40);
>>>>>>> deda4b27f920ec63d67a1900456c4cd4d39b226b

    Eyer::EyerVideoFragment videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    // videoFragment.SetFrameIndex(0, fps * 30);
    // videoFragment.SetFrameTime(0.0, videoFragment.GetDuration());
    videoFragment.Print();

    layer.AddVideoFragment(videoFragment);

    videoTrack.AddLayer(layer);

    builder.AddVideoTrack(videoTrack);
    builder.Process();
}

TEST(EyerBuilder, EyerBuilder){
    /*
    Eyer::EyerWandBuilder builder("./builder_mp4.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(60);
    */
    // builder.Process();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
