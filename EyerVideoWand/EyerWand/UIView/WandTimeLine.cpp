#include "WandUIView.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    WandTimeLine::WandTimeLine()
    {


    }
    
    WandTimeLine::~WandTimeLine()
    {
        
    }

    int WandTimeLine::Draw(WandTimeLineDrawEventList & eventList)
    {
        EyerLog("TimeLine draw\n");

        float canvasW = wh.x();
        float canvasH = wh.y();

        EyerVec4 backgroundColor            (0.3f, 0.3f, 0.3f, 1.0f);       // 绘制背景底色
        EyerVec4 markColor                  (1.0f, 1.0f, 1.0f, 1.0f);       // 标尺颜色
        EyerVec4 timePointerColor           (1.0f, 1.0f, 1.0f, 1.0f);       // 绘制时间针颜色
        EyerVec4 layerColor                 (0.8f, 0.8f, 0.8f, 0.8f);       // Layer颜色

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, canvasW, canvasH);
        rect.SetColor(backgroundColor);

        eventList.AddEvent(&rect);

        
        double offsetX = -(nowTime / markDTime * markD) + canvasW / 2;

        // 绘制时间标尺
        int timeMartCount = (int)(time / markDTime);
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

        // 绘制 Layer
        int layerHeight = canvasH * 0.15;
        WandTimeLineDrawEvent_Rect layerRect;
        double layerStartTime = 0.0f;
        double layerEndTime = 8.0f;

        float layerStartX = 0.0 + layerStartTime / markDTime * markD + offsetX;
        float layerEndX = 0.0 + layerEndTime / markDTime * markD + offsetX;

        layerRect.SetRect(layerStartX, canvasH * 0.5 - layerHeight * 0.5, layerEndX, canvasH * 0.5 + layerHeight * 0.5);
        layerRect.SetColor(layerColor);

        eventList.AddEvent(&layerRect);

        WandTimeLineDrawEvent_Bitmap bitmap;
        eventList.AddEvent(&bitmap);

        // 绘制时间针
        WandTimeLineDrawEvent_Line timePointer;
        timePointer.SetColor(timePointerColor);
        int h = canvasH * 0.5;
        timePointer.SetLine(canvasW / 2, canvasH * 0.5 - h * 0.5, canvasW / 2, canvasH * 0.5 + h * 0.5);
        timePointer.SetStrokeWidth(10);

        eventList.AddEvent(&timePointer);

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