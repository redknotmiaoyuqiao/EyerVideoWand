#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEvent::WandTimeLineDrawEvent()
    {

    }

    WandTimeLineDrawEvent::~WandTimeLineDrawEvent()
    {
        
    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent::GetType()
    {
        return WandTimeLineDrawEventType::UNKNOW;
    }
}