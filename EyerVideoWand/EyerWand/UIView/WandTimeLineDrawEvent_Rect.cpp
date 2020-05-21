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
}