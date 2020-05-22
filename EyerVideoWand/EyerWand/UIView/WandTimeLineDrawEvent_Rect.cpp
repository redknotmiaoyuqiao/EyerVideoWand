#include "WandUIView.hpp"

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
}