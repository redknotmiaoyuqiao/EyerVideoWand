#include "WandUIView.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Rect::WandTimeLineDrawEvent_Rect()
    {
        
    }

    WandTimeLineDrawEvent_Rect::~WandTimeLineDrawEvent_Rect()
    {

    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Rect::GetType()
    {
        return WandTimeLineDrawEventType::RECT;
    }

    WandTimeLineDrawEvent_Rect::WandTimeLineDrawEvent_Rect(WandTimeLineDrawEvent_Rect & rect)
    {
        *this = rect;
    }

    WandTimeLineDrawEvent_Rect & WandTimeLineDrawEvent_Rect::operator = (WandTimeLineDrawEvent_Rect & rect)
    {
        return *this;
    }

    int WandTimeLineDrawEvent_Rect::SetRect(float startX, float startY, float endX, float endY)
    {
        start.SetX(startX);
        start.SetY(startY);

        start.SetX(startX);
        start.SetY(startY);

        EyerLog("(%f, %f), (%f, %f)\n", startX, startY, endX, endY);

        return 0;
    }
}