#include <EyerGL/EyerGL.hpp>
#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoTrack::EyerVideoTrack()
    {

    }

    EyerVideoTrack::~EyerVideoTrack()
    {
        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                delete l;
            }
        }

        layoutList.clear();
    }

    EyerVideoTrack::EyerVideoTrack(const EyerVideoTrack & track)
    {
        *this = track;
    }

    EyerVideoTrack & EyerVideoTrack::operator = (const EyerVideoTrack & track)
    {
        if(this == &track){
            return *this;
        }

        for(int i=0;i<track.layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            track.layoutList.find(i, l);
            if(l != nullptr){
                EyerVideoLayout * _l = new EyerVideoLayout(*l);
                layoutList.insertBack(_l);
            }
        }

        return *this;
    }

    int EyerVideoTrack::AddLayout(const EyerVideoLayout & layout)
    {
        EyerVideoLayout * l = new EyerVideoLayout(layout);
        layoutList.insertBack(l);
        return 0;
    }

    int EyerVideoTrack::AddLayer(const EyerVideoLayout &layout)
    {
        return AddLayout(layout);
    }

    int EyerVideoTrack::GetFrameCount()
    {
        int frameCount = 0;

        // Find Max Frame Index
        int maxFrameIndex = 0;
        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                int endFrameIndex = l->GetEndFrameIndex();
                if(endFrameIndex > maxFrameIndex){
                    maxFrameIndex = endFrameIndex;
                }
            }
        }

        frameCount = maxFrameIndex;

        return frameCount;
    }


    int EyerVideoTrack::RenderFrame(int frameIndex, EyerVideoTrackRenderParams * params, int fps)
    {
        EyerLinkedList<EyerGLFrameDraw *> frameDrawList;
        EyerLinkedList<EyerGLTexture *> textureList;

        params->frameBuffer->Clear();

        for(int i=0;i<layoutList.getLength();i++){

            EyerVideoLayout * layout = nullptr;
            layoutList.find(i, layout);
            if(layout == nullptr){
                continue;
            }

            if(frameIndex < layout->GetStartFrameIndex()){
                continue;
            }
            if(frameIndex > layout->GetEndFrameIndex()){
                continue;
            }

            // EyerLog("Layout Frame Index: %d====Layer: %d\n", frameIndex, i);

            int videoFragmentCount = layout->GetVideoFragmentCount();

            for(int fragmentIndex=0;fragmentIndex<videoFragmentCount;fragmentIndex++){
#ifdef EYER_DEBUG
                long long TIME_START_GetVideoPanel = EyerTime::GetTime();
#endif
                EyerVideoPanel panel;
                int ret = layout->GetVideoPanel(panel, fragmentIndex, frameIndex - layout->GetStartFrameIndex(), fps);
                if(ret){
                    continue;
                }

#ifdef EYER_DEBUG
                long long TIME_END_GetVideoPanel = EyerTime::GetTime();
#endif

#ifdef EYER_DEBUG
                EyerWandDebug::DecoderTime += (TIME_END_GetVideoPanel - TIME_START_GetVideoPanel);
#endif
                // EyerLog("Get Panel Success, Width: %d, Height: %d\n", panel.GetW(), panel.GetH());

                unsigned char * yData = (unsigned char *)malloc(panel.GetW() * panel.GetH());
                panel.GetYDate(yData);
                unsigned char * uData = (unsigned char *)malloc(panel.GetW() / 2 * panel.GetH() / 2);
                panel.GetUDate(uData);
                unsigned char * vData = (unsigned char *)malloc(panel.GetW() / 2 * panel.GetH() / 2);
                panel.GetVDate(vData);

                EyerGLTexture * y = new EyerGLTexture();
                y->SetDataRedChannel(yData, panel.GetW(), panel.GetH());
                textureList.insertBack(y);

                EyerGLTexture * u = new EyerGLTexture();
                u->SetDataRedChannel(uData, panel.GetW() / 2, panel.GetH() / 2);
                textureList.insertBack(u);

                EyerGLTexture * v = new EyerGLTexture();
                v->SetDataRedChannel(vData, panel.GetW() / 2, panel.GetH() / 2);
                textureList.insertBack(v);

                EyerGLFrameDraw * frameDraw = new EyerGLFrameDraw();
                frameDraw->SetYTexture(y);
                frameDraw->SetUTexture(u);
                frameDraw->SetVTexture(v);
                frameDrawList.insertBack(frameDraw);

                params->frameBuffer->AddComponent(frameDraw);

                free(yData);
                free(uData);
                free(vData);
            }
        }
        params->frameBuffer->AddComponent(params->titleTextDraw);

        params->frameBuffer->Draw();
        params->frameBuffer->ClearAllComponent();

        for(int i=0;i<frameDrawList.getLength();i++){
            EyerGLFrameDraw * frameDraw = nullptr;
            frameDrawList.find(i, frameDraw);
            delete frameDraw;
        }
        frameDrawList.clear();

        for(int i=0;i<textureList.getLength();i++){
            EyerGLTexture * texture = nullptr;
            textureList.find(i, texture);
            delete texture;
        }
        textureList.clear();

        return 0;
    }
}