#include "WandUIView.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    WandTimeLine::WandTimeLine()
    {


    }
    
    WandTimeLine::~WandTimeLine()
    {
        
    }

    int WandTimeLine::SetWandCtx(Eyer::EyerWandContext * _ctx)
    {
        ctx = _ctx;
        return 0;
    }

    int WandTimeLine::Draw(WandTimeLineDrawEventList & eventList)
    {
        // EyerLog("TimeLine draw\n");
        if(ctx == nullptr){
            return 0;
        }

        float canvasW = wh.x();
        float canvasH = wh.y();

        // EyerVec4 backgroundColor            (0.3f, 0.3f, 0.3f, 1.0f);       // 绘制背景底色
        EyerVec4 backgroundColor            (0.0f, 0.0f, 0.0f, 1.0f);       // 绘制背景底色
        EyerVec4 markColor                  (0.4f, 0.4f, 0.4f, 1.0f);       // 标尺颜色
        EyerVec4 timePointerColor           (1.0f, 1.0f, 1.0f, 1.0f);       // 绘制时间针颜色
        EyerVec4 layerColor                 (0.8f, 0.8f, 0.8f, 0.8f);       // Layer颜色
        EyerVec4 textColor                  (1.0f, 0.0f, 0.0f, 1.0f);       // text颜色

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, canvasW, canvasH);
        rect.SetColor(backgroundColor);

        eventList.AddEvent(&rect);

        
        double offsetX = -(nowTime / markDTime * markD) + canvasW / 2;

        int fps = ctx->GetFPS();

        EyerVideoTrack videoTrack;
        ctx->GetVideoTrack(videoTrack);



        time = 0.0;
        // 统计 Layer 总时间
        int videoFragmentCount = videoTrack.VideoLayer_GetFragmentCount();
        for(int videoFragmentIndex = 0; videoFragmentIndex < videoFragmentCount; videoFragmentIndex++){
            EyerVideoFragment * fragment = nullptr;
            videoTrack.VideoLayer_GetFragment(fragment, videoFragmentIndex);
            if(fragment == nullptr){
                continue;
            }
            if(fragment->GetType() != EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                continue;
            }
            EyerVideoFragmentVideo * vf = (EyerVideoFragmentVideo *)fragment;
            time += vf->GetDuration();
        }

        // 绘制时间标尺
        int timeMartCount = (int)(time / markDTime) + 1;
        for(int markIndex=0;markIndex<timeMartCount;markIndex++){
            WandTimeLineDrawEvent_Line line;
            line.SetColor(markColor);

            int x = markIndex * markD + offsetX;

            if(x <= -20){
                continue;
            }
            if(x >= canvasW + 20){
                continue;
            }
            
            line.SetLine(x, 0.0f, x, 40.0f);
            line.SetStrokeWidth(6);
            eventList.AddEvent(&line);
        }

        double offsetTime = 0.0;
        // 绘制 Video Fragment Layer
        for(int videoFragmentIndex = 0; videoFragmentIndex < videoFragmentCount; videoFragmentIndex++){
            EyerVideoFragment * fragment = nullptr;
            videoTrack.VideoLayer_GetFragment(fragment, videoFragmentIndex);
            if(fragment == nullptr){
                continue;
            }
            if(fragment->GetType() != EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                continue;
            }
            EyerVideoFragmentVideo * vf = (EyerVideoFragmentVideo *)fragment;

            double layerStartTime = offsetTime + vf->GetStartTime();
            double layerEndTime = offsetTime + vf->GetEndTime();

            offsetTime += (vf->GetEndTime() - vf->GetStartTime());

            int layerHeight = canvasH * 0.2;

            WandTimeLineDrawEvent_Rect layerRect;

            float layerStartX   = 0.0 + layerStartTime / markDTime * markD + offsetX;
            float layerEndX     = 0.0 + layerEndTime / markDTime * markD + offsetX;

            float layerStartY   = canvasH * 0.5 - layerHeight * 0.5;
            float layerEndY     = canvasH * 0.5 + layerHeight * 0.5;

            layerStartX     = layerStartX   +   25;
            layerEndX       = layerEndX     -   25;

            layerRect.SetRect(layerStartX, layerStartY, layerEndX, layerEndY);
            layerRect.SetColor(layerColor);

            eventList.AddEvent(&layerRect);

            int imgW = layerHeight;
            int imgCount = (layerEndX - layerStartX) / imgW;
            for(int imgIndex = 0; imgIndex < imgCount; imgIndex++){
                WandTimeLineDrawEvent_Bitmap bitmap;

                float x1 = imgIndex * imgW + layerStartX;
                float y1 = layerStartY;

                float x2 = imgIndex * imgW + imgW + layerStartX;
                float y2 = layerEndY;

                if(x1 > canvasW){
                    continue;
                }
                if(x2 < 0){
                    continue;
                }

                bitmap.SetDist(x1, y1, x2, y2);
                eventList.AddEvent(&bitmap);
            }
        }
        
        // 绘制时间针
        WandTimeLineDrawEvent_Line timePointer;
        timePointer.SetColor(timePointerColor);
        int h = canvasH * 0.5;
        timePointer.SetLine(canvasW / 2, canvasH * 0.5 - h * 0.5, canvasW / 2, canvasH * 0.5 + h * 0.5);
        timePointer.SetStrokeWidth(10);

        eventList.AddEvent(&timePointer);




        //绘制文字
        WandTimeLineDrawEvent_Text text;
        text.SetColor(textColor);
        text.SetText("咪咪 么么哒", 75.0, 10, 100, "");

        eventList.AddEvent(&text);


        

        if(lastRenderFrameIndex != nowTime * fps){
            ctx->RenderFrameByIndex(nowTime * fps);
            lastRenderFrameIndex = nowTime * fps;
        }

        
        

        return 0;
    }

    int WandTimeLine::SetWH(float w, float h)
    {
        wh.SetX(w);
        wh.SetY(h);
        return 0;
    }

    int WandTimeLine::OnTouchUp(float x, float y)
    {
        isMove = 0;
        lastX = -1.0f;
        return 0;
    }

    int WandTimeLine::OnTouchDown(float x, float y)
    {
        isMove = 1;
        lastX = -1.0f;
        return 0;
    }

    int WandTimeLine::OnTouchMove(float x, float y)
    {
        if(lastX >= 0.0f){
            float d = x - lastX;
            nowTime -= d / markD * markDTime;

            if(nowTime <= 0){
                nowTime = 0.0;
            }
            if(nowTime >= time){
                nowTime = time;
            }
        }
        lastX = x;

        return 0;
    }
}