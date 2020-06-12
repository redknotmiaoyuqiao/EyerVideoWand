#include "WandUIView.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Rect::WandTimeLineDrawEvent_Rect()
    {
        
    }

    WandTimeLineDrawEvent_Rect::~WandTimeLineDrawEvent_Rect()
    {

    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Rect::GetType()
    {
        return WandTimeLineDrawEventType::RECT;
    }

    WandTimeLineDrawEvent_Rect::WandTimeLineDrawEvent_Rect(WandTimeLineDrawEvent_Rect & rect)
    {
        *this = rect;
    }

    WandTimeLineDrawEvent_Rect & WandTimeLineDrawEvent_Rect::operator = (WandTimeLineDrawEvent_Rect & rect)
    {
        start = rect.start;
        end = rect.end;
        color = rect.color;
        return *this;
    }

    int WandTimeLineDrawEvent_Rect::SetRect(float startX, float startY, float endX, float endY)
    {
        start.SetX(startX);
        start.SetY(startY);

        end.SetX(endX);
        end.SetY(endY);

        return 0;
    }

    int WandTimeLineDrawEvent_Rect::SetColor(EyerVec4 _color)
    {
        color = _color;
        return 0;
    }

    int WandTimeLineDrawEvent_Rect::SetColor(float red, float green, float blue, float alpha)
    {
        color.SetX(red);
        color.SetY(green);
        color.SetZ(blue);
        color.SetW(alpha);
        return 0;
    }

    int WandTimeLineDrawEvent_Rect::GetRect(EyerVec2 & _start, EyerVec2 & _end)
    {
        _start = start;
        _end = end;
        return 0;
    }

    int WandTimeLineDrawEvent_Rect::GetColor(EyerVec4 & _color)
    {
        _color = color;
        return 0;
    }
}