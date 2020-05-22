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

    WandTimeLineDrawEvent_Line::WandTimeLineDrawEvent_Line(WandTimeLineDrawEvent_Line & line)
    {
        *this = line;
    }

    WandTimeLineDrawEvent_Line & WandTimeLineDrawEvent_Line::operator = (WandTimeLineDrawEvent_Line & line)
    {
        return *this;
    }
}