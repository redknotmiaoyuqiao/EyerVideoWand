#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Bitmap::WandTimeLineDrawEvent_Bitmap()
    {
        
    }

    WandTimeLineDrawEvent_Bitmap::~WandTimeLineDrawEvent_Bitmap()
    {

    }

    WandTimeLineDrawEvent_Bitmap::WandTimeLineDrawEvent_Bitmap(WandTimeLineDrawEvent_Bitmap & bitmap)
    {
        *this = bitmap;
    }
    WandTimeLineDrawEvent_Bitmap & WandTimeLineDrawEvent_Bitmap::operator = (WandTimeLineDrawEvent_Bitmap & bitmap)
    {
        src        = bitmap.src;
        dist       = bitmap.dist;
        
        return *this;
    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Bitmap::GetType()
    {
        return WandTimeLineDrawEventType::BITMAP;
    }

    int WandTimeLineDrawEvent_Bitmap::GetRect(EyerVec4 & _src, EyerVec4 & _dist)
    {
        src = _src;
        dist = _dist;
        return 0;
    }

    int WandTimeLineDrawEvent_Bitmap::GetSrc(EyerVec4 & _src)
    {
        _src = src;
        return 0;
    }

    int WandTimeLineDrawEvent_Bitmap::GetDist(EyerVec4 & _dist)
    {
        _dist = dist;
        return 0;
    }

    int WandTimeLineDrawEvent_Bitmap::SetSrc(float x1, float y1, float x2, float y2)
    {
        src.SetXY1(x1, y1);
        src.SetXY2(x2, y2);
        return 0;
    }
    int WandTimeLineDrawEvent_Bitmap::SetDist(float x1, float y1, float x2, float y2)
    {
        dist.SetXY1(x1, y1);
        dist.SetXY2(x2, y2);
        return 0;
    }
}