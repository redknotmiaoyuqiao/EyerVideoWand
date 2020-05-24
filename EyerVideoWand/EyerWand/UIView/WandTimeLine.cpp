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

        WandTimeLineDrawEvent_Rect rect;
        rect.SetRect(0.0f, 0.0f, 100.0f, 100.0f);

        eventList.AddEvent(&rect);

        return 0;
    }
}