#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_Bitmap::WandTimeLineDrawEvent_Bitmap()
    {
        srcStart.SetX(0.0);
        srcStart.SetY(0.0);

        srcEnd.SetX(100.0);
        srcEnd.SetY(100.0);

        distStart.SetX(0.0);
        distStart.SetY(0.0);

        distEnd.SetX(100.0);
        distEnd.SetY(100.0);
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
        srcStart        = bitmap.srcStart;
        srcEnd          = bitmap.srcEnd;
        distStart       = bitmap.distStart;
        distEnd         = bitmap.distEnd;

        return *this;
    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_Bitmap::GetType()
    {
        return WandTimeLineDrawEventType::BITMAP;
    }

    int WandTimeLineDrawEvent_Bitmap::GetRect(EyerVec2 & _srcStart, EyerVec2 & _srcEnd, EyerVec2 & _distStart, EyerVec2 & _distEnd)
    {
        _srcStart       = srcStart;
        _srcEnd         = srcEnd;
        _distStart      = distStart;
        _distEnd        = distEnd;
        return 0;
    }
}