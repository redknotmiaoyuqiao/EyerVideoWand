#include "WandRenderTask.hpp"
#include "EyerCrop/EyerCrop.hpp"

namespace Eyer
{
    LayerRenderTask::LayerRenderTask(EyerVideoLayer & _layer)
    {
        layer = _layer;
    }

    LayerRenderTask::~LayerRenderTask()
    {

    }

    int LayerRenderTask::SetScreenWH(int w, int h)
    {
        screenW = w;
        screenH = h;
        return 0;
    }

    int LayerRenderTask::SetVideoWH(int w, int h)
    {
        videoW = w;
        videoH = h;
        return 0;
    }

    int LayerRenderTask::Render()
    {
        // 长宽应该为 surfaceview 大小
        EyerGLFrameBuffer screenFrameBuffer(screenW, screenH);

        EyerGLTexture frameTargetTexture;
        EyerGLFrameBuffer frameTargetBuffer(videoW, videoH, &frameTargetTexture);
        frameTargetBuffer.Clear(0.0, 0.0, 0.0, 1.0);

        int fragmentCount =  layer.GetVideoFragmentCount();
        for(int fragmentIndex=0;fragmentIndex <fragmentCount;fragmentIndex++){
            EyerVideoFragment * fragment = nullptr;
            layer.GetVideoFragment(fragment, fragmentIndex);
            if(fragment == nullptr){
                continue;
            }

            if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                EyerAVFrame avframe;
                EyerVideoFragmentVideo * videoFragmentVideo = (EyerVideoFragmentVideo *)fragment;
                int ret = videoFragmentVideo->GetVideoFrame(avframe, 0.0);
                if(ret){
                    EyerLog("GetVideoFrame Error\n");
                    continue;
                }

                int frameW = avframe.GetWidth();
                int frameH = avframe.GetHeight();

                // EyerLog("W:%d, H:%d\n", frameW, frameH);

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

        // 渲染到屏幕
        EyerGLMVPTextureDraw mvpTextureDraw;
        mvpTextureDraw.SetTexture(&frameTargetTexture);

        EyerMat4x4 ortho;
        ortho.SetOrtho(-screenW / 2, screenW / 2, screenH / 2, -screenH / 2, -100, 100);

        EyerAVCropUtil cropUtil;
        int cropTargetW = 0;
        int cropTargetH = 0;
        cropUtil.GetCrop(screenW, screenH, videoW, videoH, cropTargetW, cropTargetH, EyerAVCropType::FIT_CENTER);
        EyerMat4x4 scale;
        scale.SetScale(cropTargetW / 2.0, cropTargetH / 2.0, 1.0);
        EyerMat4x4 mvp = ortho * scale;

        mvpTextureDraw.SetMVP(mvp);

        screenFrameBuffer.ClearAllComponent();
        screenFrameBuffer.AddComponent(&mvpTextureDraw);
        screenFrameBuffer.Clear(0.5, 0.5, 0.5, 1.0);
        screenFrameBuffer.Draw();



        // ReadPixel

        return 0;
    }

    int LayerRenderTask::Init()
    {
        return 0;
    }

    int LayerRenderTask::Destory()
    {
        return 0;
    }
}