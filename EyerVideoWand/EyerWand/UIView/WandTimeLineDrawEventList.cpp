#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEventList::WandTimeLineDrawEventList()
    {

    }
    
    WandTimeLineDrawEventList::~WandTimeLineDrawEventList()
    {

    }

    int WandTimeLineDrawEventList::AddEvent(WandTimeLineDrawEvent * event)
    {
        if(event->GetType() == WandTimeLineDrawEventType::LINE){

        }
        if(event->GetType() == WandTimeLineDrawEventType::RECT){

        }
        return 0;
    }
}