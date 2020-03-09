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
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer;
    layer.SetFrame(0, fps * 5);

    Eyer::EyerVideoLayout layer2;
    layer2.SetFrame(fps * 5, fps * 5 + fps * 25);

    Eyer::EyerVideoFragmentVideo videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    videoFragment.Print();

    Eyer::EyerVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./M_1280_720.mp4");

    videoFragment2.AddTransKey(0.0, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(40.0, -200.0, 0.0, 0.0);

    videoFragment2.Print();


    Eyer::EyerVideoFragmentText videoFragmentText;
    videoFragmentText.SetFontPath("./xiao_xiao_yuan_pin_ying.ttf");
    videoFragmentText.SetText("这里是测试字幕");

    layer.AddVideoFragment(&videoFragment);

    layer2.AddVideoFragment(&videoFragment2);
    // layer2.AddVideoFragment(&videoFragmentText);

    videoTrack.AddLayer(layer);
    videoTrack.AddLayer(layer2);

    // 音频
    Eyer::EyerAudioTrack audioTrack;

    Eyer::EyerAudioLayer audioLayer;
    audioLayer.SetTime(0.0, 10.0);

    Eyer::EyerAudioFragment audioFragment;
    audioFragment.LoadAudioFile("./wei.mp3");

    audioLayer.AddAudioFragment(audioFragment);

    audioTrack.AddLayer(audioLayer);


    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
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
