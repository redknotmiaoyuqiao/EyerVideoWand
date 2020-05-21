#ifndef	EYER_LIB_AV_WAND_UI_VIEW_H
#define	EYER_LIB_AV_WAND_UI_VIEW_H

#include <vector>

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

        WandTimeLineDrawEventType GetType();
    };

    class WandTimeLineDrawEvent_Line : public WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent_Line();
        ~WandTimeLineDrawEvent_Line();

        WandTimeLineDrawEventType GetType();
    };
}

#endif