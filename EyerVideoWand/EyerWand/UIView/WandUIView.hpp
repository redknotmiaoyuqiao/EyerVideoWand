#ifndef	EYER_LIB_AV_WAND_UI_VIEW_H
#define	EYER_LIB_AV_WAND_UI_VIEW_H

#include <vector>
#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    class WandTimeLine;
    class WandTimeLineDrawEvent;
    class WandTimeLineDrawEvent_Rect;
    class WandTimeLineDrawEvent_Line;
    class WandTimeLineDrawEvent_Bitmap;
    class WandTimeLineDrawEventList;

    /**
     * 绘制界面类型的枚举类
     */ 
    enum WandTimeLineDrawEventType
    {
        UNKNOW      = -1,
        RECT        = 0,
        LINE        = 1,
        BITMAP      = 2,
        TEXT        = 3
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

        int OnTouchUp(float x, float y);
        int OnTouchDown(float x, float y);
        int OnTouchMove(float x, float y);

        int Draw(WandTimeLineDrawEventList & eventList);

    private:
        EyerVec2 wh;

        int isMove = 0;
        float lastX = -1;

        // 绘制 时间标尺
        double time = 120.0; // 120 秒
        // 当前时间指针指向的时间
        double nowTime = 0;
        // 显示 mark 的时间间隔
        double markDTime = 1.0;
        // 两个 mark 之间的距离
        double markD = 200.0f;
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

        int SetStrokeWidth(int strokeWidth);
        int GetStrokeWidth();

    private:
        EyerVec2 start;
        EyerVec2 end;

        EyerVec4 color;

        int strokeWidth = 1;
    };


    class WandTimeLineDrawEvent_Bitmap : public WandTimeLineDrawEvent
    {
    public:
        WandTimeLineDrawEvent_Bitmap();
        ~WandTimeLineDrawEvent_Bitmap();

        WandTimeLineDrawEvent_Bitmap(WandTimeLineDrawEvent_Bitmap & bitmap);
        WandTimeLineDrawEvent_Bitmap & operator = (WandTimeLineDrawEvent_Bitmap & bitmap);

        WandTimeLineDrawEventType GetType();

        int GetRect(EyerVec2 & srcStart, EyerVec2 & srcEnd, EyerVec2 & distStart, EyerVec2 & distEnd);

    private:
        EyerVec2 srcStart;
        EyerVec2 srcEnd;

        EyerVec2 distStart;
        EyerVec2 distEnd;
    };
}

#endif