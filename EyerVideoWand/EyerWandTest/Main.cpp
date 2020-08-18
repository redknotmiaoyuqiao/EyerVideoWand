#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>
#include "EyerCore/EyerCore.hpp"

TEST(EyerWandContext, EyerWandContextTest){
    int screenW = 1920;
    int screenH = 1080;

    Eyer::EyerGLContextThread glCtx;
    glCtx.SetWH(screenW, screenH);

    Eyer::EyerWandContext context(1920, 1080, 30);
    context.SetGLCtx(&glCtx);

    Eyer::EyerVideoFragmentVideo videoFragmentVideo;
    videoFragmentVideo.Load("./M_1280_720.mp4");
    context.AddFragment2Layer(Eyer::EyerString("video_layer"), videoFragmentVideo);
    context.AddFragment2Layer(Eyer::EyerString("video_layer"), videoFragmentVideo);
    context.AddFragment2Layer(Eyer::EyerString("video_layer"), videoFragmentVideo);

    for(int i=0;i<1;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    glCtx.Run();

    glCtx.Stop();
}

TEST(EyerVideoFragment, whiteBG){
    /*
    int fps = 30;

    Eyer::EyerWandBuilder builder("./struct_builder_vidoe_mp4_png.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer1;
    layer1.SetFrame(0, fps * 15);

    Eyer::EyerVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./white.jpeg");
    videoFragment2.AddScaleKey(0.0, 1280, 720, 1.0);
    videoFragment2.AddScaleKey(5.0, 1280, 720, 1.0);

    Eyer::EyerVideoFragmentVideo videoFragment4;
    videoFragment4.LoadVideoFile("./eggCooker.jpg");
    videoFragment4.AddScaleKey(0.0, 100, 100, 1.0);
    videoFragment4.AddScaleKey(5.0, 100, 100, 1.0);
    videoFragment4.AddTransKey(0.0, -400, 0,0);
    videoFragment4.AddTransKey(5.0, -400, 0,0);

    Eyer::EyerVideoFragmentVideo videoFragment3;
    videoFragment3.LoadVideoFile("./qipao.mp4");
    videoFragment3.AddScaleKey(0.0, 400, 400, 1.0);
    videoFragment3.AddScaleKey(5.0, 400, 400, 1.0);

    Eyer::EyerVideoFragmentVideo videoFragment5;
    videoFragment5.LoadVideoFile("./start.mp4");
    videoFragment5.AddScaleKey(0.0, 500, 500, 1.0);
    videoFragment5.AddScaleKey(5.0, 500, 500, 1.0);
    videoFragment5.AddTransKey(0.0, 500, 0,0);
    videoFragment5.AddTransKey(5.0, 500, 0,0);

    layer1.AddVideoFragment(&videoFragment2);
    layer1.AddVideoFragment(&videoFragment3);
    layer1.AddVideoFragment(&videoFragment4);
    layer1.AddVideoFragment(&videoFragment5);

    videoTrack.AddLayout(layer1);

    builder.AddVideoTrack(videoTrack);

    builder.Process();
    */
}

TEST(EyerVideoFragment, readpng){
    /*
    int fps = 30;

    Eyer::EyerWandBuilder builder("./struct_builder_vidoe_mp4_png.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer1;
    layer1.SetFrame(0, fps * 5);

    Eyer::EyerVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./1.jpg");
    videoFragment2.AddScaleKey(0.0, 1280, 720, 1.0);
    videoFragment2.AddScaleKey(5.0, 1280, 720, 1.0);

    Eyer::EyerVideoFragmentFrameSequential fragmentFrameSequential;
    fragmentFrameSequential.SetDirPathModel("./earl", 24, 1);
    fragmentFrameSequential.SetScale(400.0, 150.0, 0.0);
    fragmentFrameSequential.SetTrans(0.0, 0.0, 0.0);
    layer1.AddVideoFragment(&videoFragment2);
    layer1.AddVideoFragment(&fragmentFrameSequential);

    videoTrack.AddLayout(layer1);

    builder.AddVideoTrack(videoTrack);

    builder.Process();
     */
}

TEST(EyerWand, Eyer_Decoder_Line){
    /*
    Eyer::EyerVideoDecoderLine decoderLine("./M_1280_720.mp4", 20.0);

    for(double ts = 20.0; ts < 40.0; ts += 0.01){
        Eyer::EyerAVFrame frame;
        decoderLine.GetFrame(frame, ts);
    }
     */
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

/*

TEST(EyerVideoBuild, EyerVideoBuild_Test){
    int fps = 30;

    Eyer::EyerWandBuilder builder("./struct_builder_vidoe_mp4.mp4");
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer1;
    layer1.SetFrame(0, fps * 5);

    Eyer::EyerVideoLayout layer2;
    layer2.SetFrame(fps * 5, fps * 10);

    Eyer::EyerVideoLayout layer3;
    layer3.SetFrame(fps * 10, fps * 15);

    Eyer::EyerVideoLayout layer4;
    layer4.SetFrame(fps * 15, fps * 20);

    Eyer::EyerVideoLayout layer5;
    layer5.SetFrame(fps * 20, fps * 25);

    Eyer::EyerVideoFragmentVideo videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    videoFragment.AddTransKey(0.0, 5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.1, -5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.2, 3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.3, -3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.4, 2.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.5, 0.0, 0.0, 0.0);

    videoFragment.AddScaleKey(0.0, 1920.0, 1080.0, 0.0);
    videoFragment.AddScaleKey(5.0, 1920.0 / 2, 1080.0 / 2, 0.0);

    videoFragment.Print();

    Eyer::EyerVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./demo.mp4");
    videoFragment2.AddTransKey(0.0, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(0.1, -30.0, -30.0, 0.0);
    videoFragment2.AddTransKey(0.2, 30.0, 30.0, 0.0);
    videoFragment2.AddTransKey(0.3, -20.0, -20.0, 0.0);
    videoFragment2.AddTransKey(0.4, 20.0, 20.0, 0.0);
    videoFragment2.AddTransKey(0.5, 10.0, 10.0, 0.0);
    videoFragment2.AddTransKey(0.6, 0.0, 0.0, 0.0);


    videoFragment2.AddTransKey(2.1, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(2.2, 0.0, 20.0, 0.0);
    videoFragment2.AddTransKey(2.3, 0.0, -20.0, 0.0);
    videoFragment2.AddTransKey(2.4, 0.0, 10.0, 0.0);
    videoFragment2.AddTransKey(2.5, 0.0, -10.0, 0.0);
    videoFragment2.AddTransKey(2.6, 0.0, 6.0, 0.0);
    videoFragment2.AddTransKey(2.7, 0.0, 0.0, 0.0);

    videoFragment2.AddScaleKey(0.0, 1920.0 , 1080.0, 0.0);
    videoFragment2.AddScaleKey(5.0, 1920.0, 1080.0, 0.0);

    videoFragment2.AddTransKey(4.1, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.2, 30.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.3, -30.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.4, 20.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.5, -20.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.6, 10.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.7, 0.0, 0.0, 0.0);

    videoFragment2.AddTransKey(6.3, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(6.4, -30.0, -30.0, 0.0);
    videoFragment2.AddTransKey(6.5, 30.0, 30.0, 0.0);
    videoFragment2.AddTransKey(6.6, -20.0, -20.0, 0.0);
    videoFragment2.AddTransKey(6.7, 20.0, 20.0, 0.0);
    videoFragment2.AddTransKey(6.8, 10.0, 10.0, 0.0);
    videoFragment2.AddTransKey(6.9, 0.0, 0.0, 0.0);


    videoFragment2.Print();


    Eyer::EyerVideoFragmentText videoFragmentText;
    videoFragmentText.SetFontPath("./xiao_xiao_yuan_pin_ying.ttf");
    videoFragmentText.SetText("这里是测试字幕");
    videoFragmentText.SetSize(100.0f);
    videoFragmentText.SetColor(1.0, 1.0, 0.0);
    int width = videoFragmentText.GetTextWidth();
    EyerLog("Text Width: %d\n", width);
    videoFragmentText.SetPos(1920 / 2.0 - width / 2.0, 400.0f);


    layer1.AddVideoFragment(&videoFragment);
    layer1.AddVideoFragment(&videoFragmentText);
    layer2.AddVideoFragment(&videoFragment2);

    Eyer::EyerVideoFragmentVideo videoFragmentImage;
    videoFragmentImage.LoadVideoFile("./2.jpg");
    videoFragmentImage.AddScaleKey(0.0, 960.0, 540.0, 0.0);
    videoFragmentImage.AddScaleKey(5.0, 1460.0, 840.0, 0.0);

    layer3.AddVideoFragment(&videoFragmentImage);

    Eyer::EyerVideoFragmentVideo videoFragmentImage2;
    videoFragmentImage2.LoadVideoFile("./4.jpg");
    videoFragmentImage2.AddScaleKey(0.0, 1460.0, 840.0, 0.0);
    videoFragmentImage2.AddScaleKey(5.0, 960.0, 540.0, 0.0);

    layer4.AddVideoFragment(&videoFragmentImage2);


    Eyer::EyerVideoFragmentVideo videoFragmentImage3;
    videoFragmentImage3.LoadVideoFile("./1.jpg");
    videoFragmentImage3.AddScaleKey(0.0, 200.0, 200.0, 0.0);
    videoFragmentImage3.AddScaleKey(5.0, 200.0, 200.0, 0.0);

    layer5.AddVideoFragment(&videoFragmentImage3);

    videoTrack.AddLayer(layer1);
    videoTrack.AddLayer(layer2);
    videoTrack.AddLayer(layer3);
    videoTrack.AddLayer(layer4);
    videoTrack.AddLayer(layer5);


    
    // 音频
    Eyer::EyerAudioTrack audioTrack;

    Eyer::EyerAudioLayer audioLayer;
    audioLayer.SetTime(0.0, 5.0);

    Eyer::EyerAudioLayer audioLayer2;
    audioLayer2.SetTime(5.0, 25.0);

    // Eyer::EyerAudioFragment audioFragment;
    // audioFragment.LoadAudioFile("./error_test_video.mp4");

    Eyer::EyerAudioFragment audioFragment2;
    audioFragment2.LoadAudioFile("./wei.aac");

    Eyer::EyerAudioFragment audioFragment3;
    audioFragment3.LoadAudioFile("./M_1280_720.mp4");

    // audioLayer.AddAudioFragment(audioFragment);
    audioLayer.AddAudioFragment(audioFragment2);
    audioLayer2.AddAudioFragment(audioFragment3);

    audioTrack.AddLayer(audioLayer);
    audioTrack.AddLayer(audioLayer2);

    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
    builder.Process();
}

*/


TEST(EyerVideoBuild, EyerVideoBuild_Test){
    /*
    int fps = 30;

    Eyer::EyerWandBuilder builder("./time_clock_1h_1920x1080_60fps.mp4");
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer1;
    // layer1.SetFrame(0, fps * 60 * 60 * 4);
    layer1.SetFrame(0, fps * 6);

    videoTrack.AddLayer(layer1);
    
    // 音频
    Eyer::EyerAudioTrack audioTrack;

    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
    builder.Process();
    */
}

TEST(EyerBuilder, EyerBuilder){
    /*
    int fps = 30;

    Eyer::EyerWandBuilder builder("./yao_test.mp4");
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer1;
    // layer1.SetFrame(0, fps * 60 * 60 * 4);
    layer1.SetFrame(0, fps * 3);
    Eyer::EyerVideoFragmentVideo videoFragmentImage2;
    videoFragmentImage2.LoadVideoFile("./M_1280_720.mp4");
    videoFragmentImage2.AddTransKey(0.0, 300.0, 0.0, 0.0);

    videoFragmentImage2.AddScaleKey(0.0, 100.0, 100.0, 0.0);
    videoFragmentImage2.AddScaleKey(3.0, 200.0, 200.0, 0.0);
    videoFragmentImage2.AddTransKey(3.0, 0.0, 0.0, 0.0);

    layer1.AddVideoFragment(&videoFragmentImage2);
    videoTrack.AddLayer(layer1);

    // 音频
    Eyer::EyerAudioTrack audioTrack;

    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
    builder.Process();

    Eyer::EyerWandBuilder builder("./builder_mp4.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(25);

    Eyer::EyerVideoTrack videoTrack;
    Eyer::EyerVideoLayout layer;
    layer.SetFrame(0, 25*5);

    Eyer::EyerVideoFragmentVideo videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    videoFragment.AddTransKey(0.0, 5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.1, -5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.2, 3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.3, -3.0, 0.0, 0.0);

    videoFragment.AddScaleKey(0.0, 1920.0, 1080.0, 0.0);
    videoFragment.AddScaleKey(5.0, 1920.0 / 2, 1080.0 / 2, 0.0);

    layer.AddVideoFragment(&videoFragment);
    videoTrack.AddLayout(layer);

    builder.AddVideoTrack(videoTrack);
    builder.Process();*/
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
