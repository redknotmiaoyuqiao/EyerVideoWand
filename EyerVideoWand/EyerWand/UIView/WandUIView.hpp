#ifndef	EYER_LIB_AV_WAND_UI_VIEW_H
#define	EYER_LIB_AV_WAND_UI_VIEW_H

#include <vector>
#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    class WandTimeLine;
    class WandTimeLineDrawEvent;
    class WandTimeLineDrawEvent_Rect;
    class WandTimeLineDrawEvent_Line;
    class WandTimeLineDrawEventList;

    enum WandTimeLineDrawEventType
    {
        UNKNOW = 0,
        RECT = 1,
        LINE = 2
    };

    class WandTimeLine
    {
    public:
        WandTimeLine();
        ~WandTimeLine();

        int Draw(WandTimeLineDrawEventList & eventList);
    };
    
    class WandTimeLineDrawEventList
    {
    public:
        WandTimeLineDrawEventList();
        ~WandTimeLineDrawEventList();

        int AddEvent(WandTimeLineDrawEvent * event);

        int GetEventCount();
        int GetEvent(WandTimeLineDrawEvent * & event, int index);

    private:
        std::vector<WandTimeLineDrawEvent *> eventList;
    };


    class WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent();
        virtual ~WandTimeLineDrawEvent();

        virtual WandTimeLineDrawEventType GetType();
    };

    class WandTimeLineDrawEvent_Rect : public WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent_Rect();
        ~WandTimeLineDrawEvent_Rect();

        WandTimeLineDrawEvent_Rect(WandTimeLineDrawEvent_Rect & rect);
        WandTimeLineDrawEvent_Rect & operator = (WandTimeLineDrawEvent_Rect & rect);

        WandTimeLineDrawEventType GetType();

        int SetRect(float startX, float startY, float endX, float endY);
    private:
        EyerVec2 start;
        EyerVec2 end;
    };

    class WandTimeLineDrawEvent_Line : public WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent_Line();
        ~WandTimeLineDrawEvent_Line();

        WandTimeLineDrawEvent_Line(WandTimeLineDrawEvent_Line & line);
        WandTimeLineDrawEvent_Line & operator = (WandTimeLineDrawEvent_Line & line);

        WandTimeLineDrawEventType GetType();
    };
}

#endif