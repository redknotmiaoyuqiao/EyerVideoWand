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

    /**
     * 绘制界面类型的枚举类
     */ 
    enum WandTimeLineDrawEventType
    {
        UNKNOW = -1,
        RECT = 0,
        LINE = 1
    };

    /**
     * TimeLine 的主要绘制逻辑
     */ 
    class WandTimeLine
    {
    public:
        WandTimeLine();
        ~WandTimeLine();

    
        int SetWH(float w, float h);

        int Draw(WandTimeLineDrawEventList & eventList);

    private:
        EyerVec2 wh;
    };

    /**
     * 事件队列
     */ 
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

    /**
     * 绘制事件的父类
     */ 
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

        int SetColor(EyerVec4 color);
        int SetColor(float red, float green, float blue, float alpha);

        int GetRect(EyerVec2 & start, EyerVec2 & end);
        int GetColor(EyerVec4 & color);
    private:
        EyerVec2 start;
        EyerVec2 end;
        EyerVec4 color;
    };

    class WandTimeLineDrawEvent_Line : public WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent_Line();
        ~WandTimeLineDrawEvent_Line();

        WandTimeLineDrawEvent_Line(WandTimeLineDrawEvent_Line & line);
        WandTimeLineDrawEvent_Line & operator = (WandTimeLineDrawEvent_Line & line);

        WandTimeLineDrawEventType GetType();


        int SetLine(float startX, float startY, float endX, float endY);

        int SetColor(EyerVec4 color);
        int SetColor(float red, float green, float blue, float alpha);

        int GetLine(EyerVec2 & start, EyerVec2 & end);
        int GetColor(EyerVec4 & color);

    private:
        EyerVec2 start;
        EyerVec2 end;

        EyerVec4 color;
    };
}

#endif