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
        // EyerVec4 backgroundColor            (0.3f, 0.3f, 0.3f, 1.0f);       // 绘制背景底色
        EyerVec4 backgroundColor            (0.0f, 0.0f, 0.0f, 1.0f);       // 绘制背景底色
        EyerVec4 markColor                  (0.4f, 0.4f, 0.4f, 1.0f);       // 标尺颜色
        EyerVec4 timePointerColor           (1.0f, 1.0f, 1.0f, 1.0f);       // 绘制时间针颜色
        EyerVec4 layerColor                 (0.8f, 0.8f, 0.8f, 0.8f);       // Layer颜色
        EyerVec4 textColor                  (1.0f, 0.0f, 0.0f, 1.0f);       // text颜色
        EyerVec4 fragmentBoxColor           (1.0f, 1.0f, 0.0f, 1.0f);       // fragmentBoxColor


        // EyerLog("TimeLine draw\n");
        if(ctx == nullptr){
            return 0;
        }

        float canvasW = wh.x();
        float canvasH = wh.y();

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, canvasW, canvasH);
        rect.SetColor(backgroundColor);

        eventList.AddEvent(&rect);

        
        double offsetX = -(nowTime / markDTime * markD) + canvasW / 2;

        int fps = ctx->GetFPS();

        // EyerVideoTrack videoTrack;
        // ctx->GetVideoTrack(videoTrack);



        
        time = 0.0;
        // 统计 Layer 总时间
        /***
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
         */

        

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

            WandTimeLineDrawEvent_Text text;
            text.SetColor(markColor);

            char s[32];
            int intTime = markIndex * markDTime;
            int min = intTime / 60 % 60;
            int sec = intTime % 60;
            sprintf(s, "%02d:%02d", min, sec);

            EyerString timeStr(s);
            text.SetText(timeStr, 40.0, x - 50.0, 80.0f, "");

            eventList.AddEvent(&text);
        }

        double offsetTime = 0.0;
        // 绘制 Video Fragment Layer
        /*
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

            double layerStartTime = 0;      /////// = vf->GetStartIndex()       *       1.0  /  fps;
            double layerEndTime = 0;        ///////= vf->GetEndIndex()         *       1.0  /  fps;

            int layerHeight = canvasH * 0.2;

            WandTimeLineDrawEvent_Rect layerRect;

            float layerStartX   = 0.0 + layerStartTime / markDTime * markD + offsetX;
            float layerEndX     = 0.0 + layerEndTime / markDTime * markD + offsetX;

            float layerStartY   = canvasH * 0.5 - layerHeight * 0.5;
            float layerEndY     = canvasH * 0.5 + layerHeight * 0.5;


            layerStartX         = layerStartX   +   25;
            layerEndX           = layerEndX     -   25;


            layerRect.SetRect(layerStartX, layerStartY, layerEndX, layerEndY);
            layerRect.SetColor(layerColor);

            eventList.AddEvent(&layerRect);

            int imgW = layerHeight;
            int imgH = layerHeight;
            imgW = vf->GetW() * 1.0 / vf->GetH() * imgH;

            // EyerLog("W:%d, H:%d\n", vf->GetW(), vf->GetH());

            int imgCount = (layerEndX - layerStartX) / imgW;
            for(int imgIndex = 0; imgIndex < imgCount; imgIndex++){
                WandTimeLineDrawEvent_BitmapSnapshot bitmapSnapshot;

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

                bitmapSnapshot.SetPath  (vf->GetPath());
                bitmapSnapshot.SetTime  (imgIndex * imgW * 1.0 / markD * markDTime);
                bitmapSnapshot.SetDist  (x1, y1, x2, y2);
                bitmapSnapshot.SetSrc   (0, 0, vf->GetW(), vf->GetH());
                eventList.AddEvent(&bitmapSnapshot);
            }

            
            int lastSnapshotW = (int)(layerEndX - layerStartX) % imgW;
            if(lastSnapshotW > 0){
                WandTimeLineDrawEvent_BitmapSnapshot bitmapSnapshot;

                float x1 = (imgCount - 0) * imgW + layerStartX;
                float y1 = layerStartY;

                float x2 = (imgCount - 0) * imgW + lastSnapshotW + layerStartX;
                float y2 = layerEndY;

                if(x1 < canvasW && x2 > 0){
                    bitmapSnapshot.SetPath  (vf->GetPath());
                    bitmapSnapshot.SetTime  ((imgCount - 1) * imgW * 1.0 / markD * markDTime);
                    bitmapSnapshot.SetDist  (x1, y1, x2, y2);
                    bitmapSnapshot.SetSrc   (0, 0, vf->GetW(), vf->GetH());
                    eventList.AddEvent(&bitmapSnapshot);
                }
            }



            if(nowTime >= layerStartTime && nowTime <= layerEndTime){
                {
                    WandTimeLineDrawEvent_Line line;
                    line.SetColor(fragmentBoxColor);
                    line.SetStrokeWidth(5);
                    line.SetLine(layerStartX, layerStartY, layerEndX, layerStartY);
                    eventList.AddEvent(&line);
                }
                {
                    WandTimeLineDrawEvent_Line line;
                    line.SetColor(fragmentBoxColor);
                    line.SetStrokeWidth(5);
                    line.SetLine(layerStartX, layerEndY, layerEndX, layerEndY);
                    eventList.AddEvent(&line);
                }
                {
                    WandTimeLineDrawEvent_Line line;
                    line.SetColor(fragmentBoxColor);
                    line.SetStrokeWidth(5);
                    line.SetLine(layerStartX, layerStartY, layerStartX, layerEndY);
                    eventList.AddEvent(&line);
                }
                {
                    WandTimeLineDrawEvent_Line line;
                    line.SetColor(fragmentBoxColor);
                    line.SetStrokeWidth(5);
                    line.SetLine(layerEndX, layerStartY, layerEndX, layerEndY);
                    eventList.AddEvent(&line);
                }
            }
        }
        
        DrawTimePointer(eventList, canvasW, canvasH, timePointerColor);
    */
        return 0;
    }

    int WandTimeLine::DrawTimePointer(WandTimeLineDrawEventList & eventList, float canvasW, float canvasH, EyerVec4 & timePointerColor){
        int fps = ctx->GetFPS();

        // 绘制时间针
        WandTimeLineDrawEvent_Line timePointer;
        timePointer.SetColor(timePointerColor);
        int h = canvasH * 0.5;
        timePointer.SetLine(canvasW / 2, canvasH * 0.5 - h * 0.5, canvasW / 2, canvasH * 0.5 + h * 0.5);
        timePointer.SetStrokeWidth(7);

        eventList.AddEvent(&timePointer);

        if(lastRenderFrameIndex != nowTime * fps){
            ////// ctx->RenderFrameByIndex(nowTime * fps);
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