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
        start = line.start;
        end = line.end;
        color = line.color;
        strokeWidth = line.strokeWidth;
        return *this;
    }

    int WandTimeLineDrawEvent_Line::SetLine(float startX, float startY, float endX, float endY)
    {
        start.SetX(startX);
        start.SetY(startY);

        end.SetX(endX);
        end.SetY(endY);

        return 0;
    }

    int WandTimeLineDrawEvent_Line::SetColor(EyerVec4 _color)
    {
        color = _color;
        return 0;
    }

    int WandTimeLineDrawEvent_Line::SetColor(float red, float green, float blue, float alpha)
    {
        color.SetX(red);
        color.SetY(green);
        color.SetZ(blue);
        color.SetW(alpha);
        return 0;
    }

    int WandTimeLineDrawEvent_Line::GetLine(EyerVec2 & _start, EyerVec2 & _end)
    {
        _start = start;
        _end = end;
        return 0;
    }

    int WandTimeLineDrawEvent_Line::GetColor(EyerVec4 & _color)
    {
        _color = color;
        return 0;
    }

    int WandTimeLineDrawEvent_Line::SetStrokeWidth(int _strokeWidth)
    {
        strokeWidth = _strokeWidth;
        return 0;
    }

    int WandTimeLineDrawEvent_Line::GetStrokeWidth()
    {
        return strokeWidth;
    }

}