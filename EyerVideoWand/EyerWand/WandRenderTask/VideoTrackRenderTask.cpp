#include "WandRenderTask.hpp"
#include "EyerCrop/EyerCrop.hpp"

namespace Eyer
{
    VideoTrackRenderTask::VideoTrackRenderTask(EyerVideoTrack * _videoTrack, int _frameIndex, int _fps)
    {
        videoTrack = _videoTrack;
        frameIndex = _frameIndex;
        fps = _fps;
    }

    VideoTrackRenderTask::~VideoTrackRenderTask()
    {

    }

    int VideoTrackRenderTask::SetScreenWH(int w, int h)
    {
        screenW = w;
        screenH = h;
        return 0;
    }

    int VideoTrackRenderTask::Render()
    {
        // 长宽应该为 surfaceview 大小
        EyerGLFrameBuffer screenFrameBuffer(screenW, screenH);
        screenFrameBuffer.Clear(0.5, 0.5, 0.5, 1.0);

        int videoW = videoTrack->GetVideoW();
        int videoH = videoTrack->GetVideoH();

        // EyerLog("Screen W: %d\n", screenW);
        // EyerLog("Screen H: %d\n", screenH);

        // EyerLog("Render Task Video W: %d\n", videoW);
        // EyerLog("Render Task Video H: %d\n", videoH);

        EyerGLTexture frameTargetTexture;
        EyerGLFrameBuffer frameTargetBuffer(videoW, videoH, &frameTargetTexture);
        frameTargetBuffer.Clear(0.0, 0.0, 0.0, 1.0);

        // VideoLayer
        // videoTrack->VideoLayer_GetFragmentCount();
        // 遍历 Layer
        // int layerCount = videoTrack->GetLayerCount();
        int layerCount = 1;
        for(int layerIndex=0;layerIndex<layerCount;layerIndex++){
            EyerVideoLayer * layer = nullptr;
            if(layerIndex == 0){
                layer = videoTrack->GetVideoLayer_Ptr();
            }

            if(layer == nullptr){
                continue;
            }
            if(frameIndex < layer->GetStartFrameIndex()){
                continue;
            }
            if(frameIndex > layer->GetEndFrameIndex()){
                continue;
            }

            // EyerLog("Render Layer, Frame Index: %d\n", frameIndex);
            int fragmentCount = layer->GetVideoFragmentCount();
            for(int fragmentIndex=0;fragmentIndex <fragmentCount;fragmentIndex++){
                EyerVideoFragment * fragment = nullptr;
                layer->GetVideoFragment(fragment, fragmentIndex);
                if(fragment == nullptr){
                    continue;
                }

                if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                    EyerAVFrame avframe;
                    EyerVideoFragmentVideo * videoFragmentVideo = (EyerVideoFragmentVideo *)fragment;

                    // EyerLog("Render Fragment, Fragment %d-%d   %d\n", videoFragmentVideo->GetStartIndex(), videoFragmentVideo->GetEndIndex(), frameIndex);

                    if(frameIndex < videoFragmentVideo->GetStartIndex()){
                        continue;
                    }
                    if(frameIndex > videoFragmentVideo->GetEndIndex()){
                        continue;
                    }

                    int localFrameIndex = frameIndex - videoFragmentVideo->GetStartIndex();
                    double time = 1.0 / fps * localFrameIndex;

                    // time = 14.800000;
                    // time = 15.033333;
                    // EyerLog("Time:%f\n", time);
                    int ret = videoFragmentVideo->GetVideoFrame(avframe, time);
                    if(ret){
                        EyerLog("GetVideoFrame Error\n");
                        continue;
                    }

                    // EyerLog("W:%d, H:%d\n", avframe.GetWidth(), avframe.GetHeight());

                    int frameW = avframe.GetWidth();
                    int frameH = avframe.GetHeight();


                    // 先讲视频帧渲染到一个 texture 上面，这里的长宽应该是视频帧的长宽
                    EyerGLTexture frameTexture;
                    EyerGLFrameBuffer frameTextureTargetBuffer(frameW, frameH, &frameTexture);
                    
                    EyerGLYUV2TextureComponent yuv2texture;

                    unsigned char * y = (unsigned char *)malloc(frameW * frameH);
                    unsigned char * u = (unsigned char *)malloc(frameW * frameH);
                    unsigned char * v = (unsigned char *)malloc(frameW * frameH);

                    avframe.GetYData(y);
                    avframe.GetUData(u);
                    avframe.GetVData(v);

                    EyerGLTexture yT;
                    yT.SetDataRedChannel(y, frameW, frameH);
                    EyerGLTexture uT;
                    uT.SetDataRedChannel(u, frameW / 2, frameH / 2);
                    EyerGLTexture vT;
                    vT.SetDataRedChannel(v, frameW / 2, frameH / 2);

                    yuv2texture.SetYTexture(&yT);
                    yuv2texture.SetUTexture(&uT);
                    yuv2texture.SetVTexture(&vT);
                    yuv2texture.SetReverseY(1);

                    free(y);
                    free(u);
                    free(v);

                    frameTextureTargetBuffer.ClearAllComponent();
                    frameTextureTargetBuffer.AddComponent(&yuv2texture);

                    frameTextureTargetBuffer.Clear(0.0, 0.0, 0.0, 1.0);
                    frameTextureTargetBuffer.Draw();

                    // 将视频帧渲染到最终 FrameBuffer 上
                    EyerGLMVPTextureDraw mvpTextureDraw;
                    mvpTextureDraw.SetTexture(&frameTexture);

                    EyerMat4x4 ortho;
                    ortho.SetOrtho(-videoW / 2, videoW / 2, videoH / 2, -videoH / 2, -100, 100);

                    EyerAVCropUtil cropUtil;
                    int cropTargetW = 0;
                    int cropTargetH = 0;
                    cropUtil.GetCrop(videoW, videoH, frameW, frameH, cropTargetW, cropTargetH, EyerAVCropType::FIT_CENTER);
                    EyerMat4x4 scale;
                    scale.SetScale(cropTargetW / 2.0, cropTargetH / 2.0, 1.0);
                    EyerMat4x4 mvp = ortho * scale;

                    mvpTextureDraw.SetMVP(mvp);

                    frameTargetBuffer.ClearAllComponent();
                    frameTargetBuffer.AddComponent(&mvpTextureDraw);
                    frameTargetBuffer.Draw();
                }
            }
        }


        // 渲染到屏幕
        EyerMat4x4 ortho;
        ortho.SetOrtho(-screenW / 2, screenW / 2, screenH / 2, -screenH / 2, -100, 100);

        EyerAVCropUtil cropUtil;
        int cropTargetW = 0;
        int cropTargetH = 0;
        cropUtil.GetCrop(screenW, screenH, videoW, videoH, cropTargetW, cropTargetH, EyerAVCropType::FIT_CENTER);
        EyerMat4x4 scale;
        scale.SetScale(cropTargetW / 2.0, cropTargetH / 2.0, 1.0);
        EyerMat4x4 mvp = ortho * scale;

        

        EyerGLMVPTextureDraw mvpTextureDraw;
        mvpTextureDraw.SetTexture(&frameTargetTexture);
        mvpTextureDraw.SetMVP(mvp);

        screenFrameBuffer.ClearAllComponent();
        screenFrameBuffer.AddComponent(&mvpTextureDraw);
        screenFrameBuffer.Clear(0.5, 0.5, 0.5, 1.0);
        screenFrameBuffer.Draw();

        // ReadPixel

        return 0;
    }

    int VideoTrackRenderTask::Init()
    {
        return 0;
    }
    
    int VideoTrackRenderTask::Destory()
    {
        return 0;
    }
}