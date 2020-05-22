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
            WandTimeLineDrawEvent_Line * line = new WandTimeLineDrawEvent_Line(*(WandTimeLineDrawEvent_Line *)event);
            eventList.push_back(line);
        }
        if(event->GetType() == WandTimeLineDrawEventType::RECT){
            WandTimeLineDrawEvent_Rect * rect = new WandTimeLineDrawEvent_Rect(*(WandTimeLineDrawEvent_Rect *)event);
            eventList.push_back(rect);
        }
        return 0;
    }

    int WandTimeLineDrawEventList::GetEventCount()
    {
        return eventList.size();
    }

    int WandTimeLineDrawEventList::GetEvent(WandTimeLineDrawEvent * & event, int index)
    {
        event = eventList[index];
        return 0;
    }
}