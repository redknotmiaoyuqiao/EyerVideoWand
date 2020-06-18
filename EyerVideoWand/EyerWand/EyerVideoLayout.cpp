#include "EyerWand.hpp"
#include <math.h>
#include "EyerGPUDomino/EyerGPUDomino.hpp"

namespace Eyer
{
    EyerVideoLayout::EyerVideoLayout()
    {
        SetFrame(-1, -1);
    }

    EyerVideoLayout::~EyerVideoLayout()
    {
        for(int i=0;i<videoFragmentList.getLength();i++){
            EyerVideoFragment * vf = nullptr;
            videoFragmentList.find(i, vf);
            if(vf != nullptr){
                delete vf;
            }
        }

        videoFragmentList.clear();
    }

    EyerVideoLayout::EyerVideoLayout(const EyerVideoLayout & layout) : EyerVideoLayout()
    {
        *this = layout;
    }

    EyerVideoLayout & EyerVideoLayout::operator = (const EyerVideoLayout & layout)
    {
        if(this == &layout){
            return *this;
        }

        startFrameIndex = layout.startFrameIndex;
        endFrameIndex = layout.endFrameIndex;

        for(int i=0;i<layout.videoFragmentList.getLength();i++){
            EyerVideoFragment * vf = nullptr;
            layout.videoFragmentList.find(i, vf);
            if(vf != nullptr){
                EyerVideoFragment * f = EyerVideoFragment::CopyFragment(vf);
                videoFragmentList.insertBack(f);
            }
        }

        return *this;
    }

    int EyerVideoLayout::SetFrame(int _startFrameIndex, int _endFrameIndex)
    {
        startFrameIndex = _startFrameIndex;
        endFrameIndex = _endFrameIndex;
        return 0;
    }

    int EyerVideoLayout::SetFPS(int _fps)
    {
        fps = _fps;
        return 0;
    }

    int EyerVideoLayout::GetFPS()
    {
        return fps;
    }

    int EyerVideoLayout::GetStartFrameIndex()
    {
        return startFrameIndex;
    }

    int EyerVideoLayout::GetEndFrameIndex()
    {
        return endFrameIndex;
    }

    int EyerVideoLayout::AddVideoFragment(const EyerVideoFragment * fragment)
    {
        EyerVideoFragment * f = EyerVideoFragment::CopyFragment(fragment);
        videoFragmentList.insertBack(f);


        pFrameIndex = 0;

        for(int i=0;i<videoFragmentList.getLength();i++){
            EyerVideoFragment * vf = nullptr;
            videoFragmentList.find(i, vf);

            if(vf != nullptr){
                if(vf->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                    EyerVideoFragmentVideo * vfv = (EyerVideoFragmentVideo *)vf;
                    int frameCount = (vfv->GetEndTime() - vfv->GetStartTime()) * fps;

                    int sIndex = pFrameIndex;
                    pFrameIndex += frameCount;
                    int eIndex = pFrameIndex;
                    pFrameIndex += 1;

                    vfv->SetFrameIndex(sIndex, eIndex);
                }
            }
        }

        SetFrame(0, pFrameIndex);

        return 0;
    }

    int EyerVideoLayout::GetVideoFragmentCount()
    {
        return videoFragmentList.getLength();
    }

    int EyerVideoLayout::GetVideoFragment(EyerVideoFragment * & fragment, int index)
    {
        if(index >= GetVideoFragmentCount()){
            return -1;
        }
        videoFragmentList.find(index, fragment);

        return 0;
    }

    int EyerVideoLayout::GetVideoPanel(EyerVideoPanel * panel, EyerVideoFragment ** fragmentP,int videoFragmentIndex, int layoutFrameIndex, int fps, EyerVideoTrackRenderParams * params)
    {
        EyerVideoFragment * fragment = nullptr;
        videoFragmentList.find(videoFragmentIndex, fragment);

        if(fragment == nullptr){
            return -1;
        }

        *fragmentP = fragment;


        EyerMat4x4 ortho;
        int w = params->videoW;
        int h = params->videoH;
        ortho.SetOrtho(- w / 2.0, w / 2.0, h / 2.0, - h / 2.0, 0.0f, 1000.0f);

        EyerMat4x4 scale;
        scale.SetScale(w / 2.0, h / 2.0, 0.0);
        //scale.SetScale(200, 200, 1.0);

        EyerMat4x4 trans;


        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            EyerLog("before EyerVideoFragmentVideo fragment=======================================\n");
            EyerVideoFragmentVideo * vfv = (EyerVideoFragmentVideo *)fragment;

            EyerAVFrame avFrame;
            // double ts = 0.0;
            double ts = 1000 * 1.0 / fps * (layoutFrameIndex);
            ts = ts / 1000.0;
            // EyerLog("Ts:%f\n", ts);
            int ret = vfv->GetVideoFrame(avFrame, ts);
            if(ret){
                return -1;
            }

            // printf("==============================\n");
            // avFrame.GetInfo();

            int width = avFrame.GetWidth();
            int height = avFrame.GetHeight();


            Eyer::EyerGLTexture yuv2rgbTexture;
            EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height, &yuv2rgbTexture);
            // EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height, &panel->targetTexture);
            //EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height);

            EyerGLYUV2TextureComponent * yuv2texture = new EyerGLYUV2TextureComponent();

            
            EyerGLTexture * y = new EyerGLTexture();
            EyerGLTexture * u = new EyerGLTexture();
            EyerGLTexture * v = new EyerGLTexture();

            EyerGLYUV2TextureComponentColorRange colorRange = EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_FULL;
            if(avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P){
                colorRange = EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_FULL;
            }
            else{
                colorRange = EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_JPEG;
            }

            EyerYUVLen memLen;
            EyerAVTool::GetYUVLen(width, height, memLen, avFrame.GetPixFormat());


            unsigned char * yData = (unsigned char *)malloc(memLen.yLen);
            unsigned char * uData = (unsigned char *)malloc(memLen.uLen);
            unsigned char * vData = (unsigned char *)malloc(memLen.vLen);

            avFrame.GetYData(yData);
            avFrame.GetUData(uData);
            avFrame.GetVData(vData);

            y->SetDataRedChannel(yData, memLen.yWidth, memLen.yHeight);
            u->SetDataRedChannel(uData, memLen.uWidth, memLen.uHeight);
            v->SetDataRedChannel(vData, memLen.vWidth, memLen.vHeight);

            yuv2texture->SetColoRange(colorRange);
            yuv2texture->SetYTexture(y);
            yuv2texture->SetUTexture(u);
            yuv2texture->SetVTexture(v);


            frameBuffer->Clear();

            frameBuffer->AddComponent(yuv2texture);

            frameBuffer->Draw();

            frameBuffer->ClearAllComponent();


            free(yData);
            free(uData);
            free(vData);

            delete y;
            delete u;
            delete v;

            delete frameBuffer;
            delete yuv2texture;

            Eyer::EyerGominoGaussianBlur gb0;
            Eyer::EyerGominoGaussianBlur gb1;
            Eyer::EyerGominoGaussianBlur gb2;
            Eyer::EyerGominoGaussianBlur gb3;

            Eyer::EyerGominoCopy cp0;

            Eyer::EyerGominoZoomBlur zb0;

            Eyer::EyerGominoPip pip;
            pip << &cp0;
            // pip << &zb0;

            pip.Go(&yuv2rgbTexture, &panel->targetTexture, width, height);

            {
                EyerVideoAnimationKey transAnimationKey(ts, 0.0, 0.0, 0.0);

                vfv->transAnimation.GetLinearValue(transAnimationKey);
                trans.SetTrans(transAnimationKey.x, transAnimationKey.y, transAnimationKey.z);

                EyerVideoAnimationKey scaleAnimationKey(ts, 0.0, 0.0, 0.0);
                vfv->scaleAnimation.GetLinearValue(scaleAnimationKey);
                scale.SetScale(scaleAnimationKey.x / 2, scaleAnimationKey.y / 2, scaleAnimationKey.z / 2);

                panel->mvp = ortho * trans * scale ;
            }
        }

        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT){
            /*
            EyerVideoFragmentText * vft = (EyerVideoFragmentText *)fragment;

            double ts = 1000 * 1.0 / fps * (layoutFrameIndex);
            ts = ts / 1000.0;

            int width = 0;
            int height = 100;

            EyerGLTextDraw textDraw(vft->fontPath);

            textDraw.SetText(vft->text);
            textDraw.SetPos(0.0, 0.0);
            textDraw.SetSize(height);
            textDraw.SetColor(1.0, 0.0, 0.0);

            width = textDraw.GetTextWidth();

            textDraw.Viewport(width, height);

            // EyerLog("Font W:%d, H:%d\n", width, height);

            EyerGLFrameBuffer frameBuffer(width, height, &panel->targetTexture);

            frameBuffer.Clear();

            frameBuffer.AddComponent(&textDraw);
            frameBuffer.Draw();

            frameBuffer.ClearAllComponent();


            scale.SetScale(100, 100, 1.0);
            panel->mvp = ortho * trans * scale;
            */
        }

        return 0;
    }
}