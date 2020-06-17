#include "WandUIView.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Text::WandTimeLineDrawEvent_Text()
    {
        
    }

    WandTimeLineDrawEvent_Text::~WandTimeLineDrawEvent_Text()
    {

    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Text::GetType()
    {
        return WandTimeLineDrawEventType::TEXT;
    }

    WandTimeLineDrawEvent_Text::WandTimeLineDrawEvent_Text(WandTimeLineDrawEvent_Text & text)
    {
        *this = text;
    }

    WandTimeLineDrawEvent_Text & WandTimeLineDrawEvent_Text::operator = (WandTimeLineDrawEvent_Text & wandText)
    {
        start = wandText.start;
        color = wandText.color;
        text = wandText.text;
        fontStyle = wandText.fontStyle;
        size = wandText.size;
        return *this;
    }

    int WandTimeLineDrawEvent_Text::SetText(EyerString _text, float _size, float startX, float startY, EyerString _fontStyle)
    {
        start.SetX(startX);
        start.SetY(startY);
        text = _text;
        size = _size;
        fontStyle = _fontStyle;

        return 0;
    }

    int WandTimeLineDrawEvent_Text::SetColor(EyerVec4 _color)
    {
        color = _color;
        return 0;
    }

    int WandTimeLineDrawEvent_Text::SetColor(float red, float green, float blue, float alpha)
    {
        color.SetX(red);
        color.SetY(green);
        color.SetZ(blue);
        color.SetW(alpha);
        return 0;
    }

    int WandTimeLineDrawEvent_Text::GetText(EyerString & _text, float & _size, EyerVec2 & _start, EyerString & _fontStyle)
    {
        _start = start;
        _text = text;
        _size = size;
        _fontStyle = fontStyle;
        return 0;
    }

    int WandTimeLineDrawEvent_Text::GetColor(EyerVec4 & _color)
    {
        _color = color;
        return 0;
    }
}