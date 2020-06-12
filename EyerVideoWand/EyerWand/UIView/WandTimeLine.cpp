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

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, canvasW, canvasH);
        rect.SetColor(backgroundColor);

        eventList.AddEvent(&rect);

        // 当前时间指针指向的时间
        double nowTime = 0;

        // 绘制 时间标尺
        double time = 120.0; // 120 秒
        // 显示 mark 的时间间隔
        double markDTime = 1.0;
        // 两个 mark 之间的距离
        float markD = 200.0f;

        double offsetX = -(nowTime / markDTime * markD)+ canvasW / 2;

        int timeMartCount = (int)(time / markDTime);
        for(int markIndex=0;markIndex<timeMartCount;markIndex++){
            WandTimeLineDrawEvent_Line line;
            line.SetColor(markColor);

            int x = markIndex * markD + offsetX;
            
            line.SetLine(x, 0.0f, x, 40.0f);
            line.SetStrokeWidth(6);
            eventList.AddEvent(&line);
        }


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
        return 0;
    }

    int WandTimeLine::OnTouchDown(float x, float y)
    {
        return 0;
    }

    int WandTimeLine::OnTouchMove(float x, float y)
    {
        return 0;
    }
}