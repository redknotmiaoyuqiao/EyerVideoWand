#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>

TEST(EyerWand, Eyer_Decoder_Line){
    Eyer::EyerVideoDecoderLine decoderLine("./M_1280_720.mp4", 20.0);

    for(double ts = 20.0; ts < 40.0; ts += 0.01){
        Eyer::EyerAVFrame frame;
        decoderLine.GetFrame(frame, ts);
    }
}

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

    Eyer::EyerVideoLayout layer;
    layer.SetFrame(0, fps * 2);

    Eyer::EyerVideoLayout layer2;
    layer2.SetFrame(fps * 5, fps * 5 + fps * 5);

    Eyer::EyerVideoFragment videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    // videoFragment.SetFrameIndex(0, fps * 30);
    // videoFragment.SetFrameTime(0.0, videoFragment.GetDuration());
    videoFragment.Print();

    layer.AddVideoFragment(videoFragment);
    layer2.AddVideoFragment(videoFragment);

    videoTrack.AddLayer(layer);
    videoTrack.AddLayer(layer2);

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
