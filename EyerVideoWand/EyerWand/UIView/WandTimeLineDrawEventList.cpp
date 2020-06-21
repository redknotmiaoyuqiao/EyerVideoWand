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
        if(event->GetType() == WandTimeLineDrawEventType::BITMAP){
            WandTimeLineDrawEvent_Bitmap * bitmap = new WandTimeLineDrawEvent_Bitmap(*(WandTimeLineDrawEvent_Bitmap *)event);
            eventList.push_back(bitmap);
        }
        if(event->GetType() == WandTimeLineDrawEventType::TEXT){
            WandTimeLineDrawEvent_Text * text = new WandTimeLineDrawEvent_Text(*(WandTimeLineDrawEvent_Text *)event);
            eventList.push_back(text);
        }
        if(event->GetType() == WandTimeLineDrawEventType::BITMAP_SNAPSHOT){
            WandTimeLineDrawEvent_BitmapSnapshot * bitmapSnapshot = new WandTimeLineDrawEvent_BitmapSnapshot(*(WandTimeLineDrawEvent_BitmapSnapshot *)event);
            eventList.push_back(bitmapSnapshot);
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
        
        /*
        WandTimeLineDrawEvent * tempEvent = eventList[index];

        if(event->GetType() == WandTimeLineDrawEventType::LINE){
            WandTimeLineDrawEvent_Line * line = new WandTimeLineDrawEvent_Line(*(WandTimeLineDrawEvent_Line *)event);
        }
        if(event->GetType() == WandTimeLineDrawEventType::RECT){
            WandTimeLineDrawEvent_Rect * rect = new WandTimeLineDrawEvent_Rect(*(WandTimeLineDrawEvent_Rect *)event);
        }
        */

        return 0;
    }
}