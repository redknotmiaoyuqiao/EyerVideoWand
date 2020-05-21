#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Line::WandTimeLineDrawEvent_Line()
    {
        
    }

    WandTimeLineDrawEvent_Line::~WandTimeLineDrawEvent_Line()
    {

    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Line::GetType()
    {
        return WandTimeLineDrawEventType::LINE;
    }
}