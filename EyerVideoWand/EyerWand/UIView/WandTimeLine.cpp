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

        // 绘制背景底色
        EyerVec4 backgroundColor(0.3f, 0.3f, 0.3f, 1.0f);
        // 标尺颜色
        EyerVec4 markColor(1.0f, 1.0f, 1.0f, 1.0f);

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, canvasW, canvasH);
        rect.SetColor(backgroundColor);

        eventList.AddEvent(&rect);

        // 绘制 时间标尺

        // 显示 mark 的时间间隔
        double markDTime = 1.0;
        // 两个 mark 之间的距离
        float markD = 50.0f;

        int timeMartCount = 120;
        for(int markIndex=0;markIndex<timeMartCount;markIndex++){
            WandTimeLineDrawEvent_Line line;
            line.SetColor(markColor);
            line.SetLine(0.0f, 0.0f, 100.0f, 100.0f);
            eventList.AddEvent(&line);
        }

        return 0;
    }

    int WandTimeLine::SetWH(float w, float h)
    {
        wh.SetX(w);
        wh.SetY(h);
        return 0;
    }
}