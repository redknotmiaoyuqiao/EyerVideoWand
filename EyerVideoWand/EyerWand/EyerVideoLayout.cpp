#include "EyerWand.hpp"
#include <math.h>
#include "EyerGPUDomino/EyerGPUDomino.hpp"

namespace Eyer
{
    EyerVideoLayout::EyerVideoLayout()
    {

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

    int EyerVideoLayout::SetFrame(int _startFrameIndex, int _endFrameIndex)
    {
        startFrameIndex = _startFrameIndex;
        endFrameIndex = _endFrameIndex;
        return 0;
    }

    EyerVideoLayout::EyerVideoLayout(const EyerVideoLayout & layout)
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

        return 0;
    }

    int EyerVideoLayout::GetVideoFragmentCount()
    {
        return videoFragmentList.getLength();
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
        printf("++++++++++++++++++++videoW:%d, videoH:%d\n", w,h);
        ortho.SetOrtho(- w / 2.0, w / 2.0, h / 2.0, - h / 2.0, 0.0f, 1000.0f);

        EyerMat4x4 scale;
        scale.SetScale(w / 2.0, h / 2.0, 0.0);
        //scale.SetScale(200, 200, 1.0);

        EyerMat4x4 trans;


        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
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

            // avFrame.GetInfo();

            int width = avFrame.GetWidth();
            int height = avFrame.GetHeight();


            Eyer::EyerGLTexture yuv2rgbTexture;
            EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height, &yuv2rgbTexture);
            // EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height, &panel->targetTexture);
            //EyerGLFrameBuffer * frameBuffer = new EyerGLFrameBuffer(width, height);

            EyerGLYUV2TextureComponent * yuv2texture = new EyerGLYUV2TextureComponent();

            unsigned char * yData = nullptr;
            unsigned char * uData = nullptr;
            unsigned char * vData = nullptr;
            EyerGLTexture * y = new EyerGLTexture();
            EyerGLTexture * u = new EyerGLTexture();
            EyerGLTexture * v = new EyerGLTexture();

            if(avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
                yData = (unsigned char *)malloc(width * height);
                avFrame.GetYData(yData);
                uData = (unsigned char *)malloc(width / 2 * height / 2);
                avFrame.GetUData(uData);
                vData = (unsigned char *)malloc(width / 2 * height / 2);
                avFrame.GetVData(vData);

                y->SetDataRedChannel(yData, width, height);
                u->SetDataRedChannel(uData, width / 2, height / 2);
                v->SetDataRedChannel(vData, width / 2, height / 2);

                yuv2texture->SetYTexture(y);
                yuv2texture->SetUTexture(u);
                yuv2texture->SetVTexture(v);
            }

            if(avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || avFrame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
                yData = (unsigned char *)malloc(width * height);
                avFrame.GetYData(yData);
                uData = (unsigned char *)malloc(width * height);
                avFrame.GetUData(uData);
                vData = (unsigned char *)malloc(width * height);
                avFrame.GetVData(vData);

                y->SetDataRedChannel(yData, width, height);
                u->SetDataRedChannel(uData, width, height);
                v->SetDataRedChannel(vData, width, height);

                yuv2texture->SetYTexture(y);
                yuv2texture->SetUTexture(u);
                yuv2texture->SetVTexture(v);
            }


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
            pip << &zb0;

            pip.Go(&yuv2rgbTexture, &panel->targetTexture, width, height);

            {
                float x = 0.0;
                float y = 0.0;
                float z = 0.0;

                vfv->GetLinearValue(EyerVideoChangeType::VIDEO_FRAGMENT_CHANGE_TRANS, ts, x, y, z);
                trans.SetTrans(x, y, z);

                float scale_x = 0.0;
                float scale_y = 0.0;
                float scale_z = 0.0;
                
                vfv->GetLinearValue(EyerVideoChangeType::VIDEO_FRAGMENT_CHANGE_SCALE, ts, scale_x, scale_y, scale_z);
                
                scale.SetScale(scale_x / 2, scale_y / 2, scale_z / 2);
                // scale.SetScale(1920.0 / 2, 1080.0 / 2, scale_z);

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