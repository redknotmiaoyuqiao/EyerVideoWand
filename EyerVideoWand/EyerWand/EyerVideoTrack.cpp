#include <EyerGL/EyerGL.hpp>
#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoTrack::EyerVideoTrack()
    {
        SetTargetVideoFPS(30);
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

    EyerVideoTrack::EyerVideoTrack(const EyerVideoTrack & track) : EyerVideoTrack()
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

        videoLayer = track.videoLayer;

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

    int EyerVideoTrack::SetTargetVideoWH(int w, int h)
    {
        videoW = w;
        videoH = h;
        return 0;
    }

    int EyerVideoTrack::SetTargetVideoFPS(int _fps)
    {
        fps = _fps;

        videoLayer.SetFPS(fps);

        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                l->SetFPS(fps);
            }
        }

        return 0;
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

        if(videoLayer.GetEndFrameIndex() >= maxFrameIndex){
            maxFrameIndex = videoLayer.GetEndFrameIndex();
        }

        frameCount = maxFrameIndex;

        return frameCount;
    }

    int EyerVideoTrack::GetLayerCount()
    {
        return layoutList.getLength();
    }
    
    int EyerVideoTrack::GetLayer(EyerVideoLayout * & layout, int index)
    {
        layoutList.find(index, layout);
        return 0;
    }

// #ifdef EYER_PLATFORM_ANDROID
    int EyerVideoTrack::RenderFrame2(int frameIndex, int fps, EyerGLContextThread * glCtx)
    {
        VideoTrackRenderTask * videoTrackRenderTask = new VideoTrackRenderTask(this, frameIndex, fps);
        videoTrackRenderTask->SetScreenWH(glCtx->GetW(), glCtx->GetH());
        glCtx->AddRenderTask(videoTrackRenderTask);
        
        return 0;
    }

// #endif

    int EyerVideoTrack::RenderFrame(int frameIndex, EyerVideoTrackRenderParams * params, int fps)
    {
        EyerLinkedList<EyerGLComponent *> frameDrawList;
        EyerLinkedList<EyerGLTexture *> textureList;
        EyerLinkedList<EyerVideoPanel *> panelList;

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
                EyerVideoPanel * panel = new EyerVideoPanel();
                EyerVideoFragment * fragmentP = nullptr;
                int ret = layout->GetVideoPanel(panel, &fragmentP, fragmentIndex, frameIndex - layout->GetStartFrameIndex(), fps, params);
                if(ret){
                    continue;
                }

                panelList.insertBack(panel);

                EyerMat4x4 panelMvp = panel->GetMVPMat();

#ifdef EYER_DEBUG
                long long TIME_END_GetVideoPanel = EyerTime::GetTime();
#endif

#ifdef EYER_DEBUG
                EyerWandDebug::DecoderTime += (TIME_END_GetVideoPanel - TIME_START_GetVideoPanel);
#endif
                // EyerLog("Get Panel Success, Width: %d, Height: %d\n", panel.GetW(), panel.GetH());

                if(fragmentP == nullptr){
                    continue;
                }

                if(fragmentP->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                    EyerGLMVPTextureDraw * mvpTextureDraw = new EyerGLMVPTextureDraw();
                    mvpTextureDraw->SetTexture(&panel->targetTexture);
                    mvpTextureDraw->SetMVP(panelMvp);
                    frameDrawList.insertBack(mvpTextureDraw);
                    params->frameBuffer->AddComponent(mvpTextureDraw);
                }
                if(fragmentP->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT){
                    EyerVideoFragmentText * vft = (EyerVideoFragmentText *)fragmentP;
                    EyerGLTextDraw * textDraw = new EyerGLTextDraw(vft->fontPath);
                    textDraw->SetText(vft->text);
                    textDraw->SetPos(vft->GetPosX(), vft->GetPosY());
                    textDraw->SetSize(vft->GetSize());
                    textDraw->SetColor(vft->GetColorR(), vft->GetColorG(), vft->GetColorB());

                    frameDrawList.insertBack(textDraw);

                    params->frameBuffer->AddComponent(textDraw);
                }
                if(fragmentP->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_FRAME_SEQUENTIAL){
                    EyerGLMVPTextureDraw * mvpTextureDraw = new EyerGLMVPTextureDraw();

                    EyerVideoFragmentFrameSequential * fragmentFrameSequential = (EyerVideoFragmentFrameSequential *)fragmentP;

                    EyerMat4x4 panelMvp;
                    // EyerGLTexture targetTexture;
                    int ret = fragmentFrameSequential->GetData(panelMvp, &panel->targetTexture, (float)frameIndex/(float)fps, params);
                    if(ret != 0){
                        break;
                    }

                    mvpTextureDraw->SetTexture(&panel->targetTexture);
                    mvpTextureDraw->SetMVP(panelMvp);

                    frameDrawList.insertBack(mvpTextureDraw);

                    params->frameBuffer->AddComponent(mvpTextureDraw);
                }


            }
        }
        params->frameBuffer->AddComponent(params->titleTextDraw);

        params->frameBuffer->Draw();
        params->frameBuffer->ClearAllComponent();

        for(int i=0;i<frameDrawList.getLength();i++){
            EyerGLComponent * frameDraw = nullptr;
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

        for(int i=0;i<panelList.getLength();i++){
            EyerVideoPanel * panel = nullptr;
            panelList.find(i, panel);
            delete panel;
        }

        panelList.clear();

        return 0;
    }

    int EyerVideoTrack::GetVideoW()
    {
        return videoW;
    }
    
    int EyerVideoTrack::GetVideoH()
    {
        return videoH;
    }

    int EyerVideoTrack::GetFPS()
    {
        return fps;
    }

    int EyerVideoTrack::VideoLayer_AddVideoFragment(EyerVideoFragmentVideo & fragmentVideo)
    {
        return videoLayer.AddVideoFragment(&fragmentVideo);
    }

    int EyerVideoTrack::VideoLayer_GetFragmentCount()
    {
        return videoLayer.GetVideoFragmentCount();
    }

    int EyerVideoTrack::VideoLayer_GetFragment(EyerVideoFragment * & fragment, int index)
    {
        return videoLayer.GetVideoFragment(fragment, index);
    }

    int EyerVideoTrack::GetVideoLayer_Copy(EyerVideoLayer & _videoLayer)
    {
        _videoLayer = videoLayer;
        return 0;
    }

    EyerVideoLayer * EyerVideoTrack::GetVideoLayer_Ptr()
    {
        return &videoLayer;
    }
}