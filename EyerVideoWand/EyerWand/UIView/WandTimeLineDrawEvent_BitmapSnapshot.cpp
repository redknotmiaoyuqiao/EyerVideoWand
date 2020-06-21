#include "WandUIView.hpp"

namespace Eyer {
    WandTimeLineDrawEvent_BitmapSnapshot::WandTimeLineDrawEvent_BitmapSnapshot()
    {

    }

    WandTimeLineDrawEvent_BitmapSnapshot::~WandTimeLineDrawEvent_BitmapSnapshot()
    {

    }

    WandTimeLineDrawEventType WandTimeLineDrawEvent_BitmapSnapshot::GetType()
    {
        return WandTimeLineDrawEventType::BITMAP_SNAPSHOT;
    }

    WandTimeLineDrawEvent_BitmapSnapshot::WandTimeLineDrawEvent_BitmapSnapshot(WandTimeLineDrawEvent_BitmapSnapshot & bitmapSnapshot)
    {
        *this = bitmapSnapshot;
    }

    WandTimeLineDrawEvent_BitmapSnapshot & WandTimeLineDrawEvent_BitmapSnapshot::operator = (WandTimeLineDrawEvent_BitmapSnapshot & bitmapSnapshot)
    {
        // EyerLog("%f. %f====", time, bitmapSnapshot.time);
        path        = bitmapSnapshot.path;
        time        = bitmapSnapshot.time;
        src         = bitmapSnapshot.src;
        dist        = bitmapSnapshot.dist;
        
        return *this;
    }

    int WandTimeLineDrawEvent_BitmapSnapshot::SetPath(EyerString _path)
    {
        path = _path;
        // EyerLog("Path: %s\n", path.str);
        return 0;
    }

    EyerString WandTimeLineDrawEvent_BitmapSnapshot::GetPath()
    {
        return path;
    }


    int WandTimeLineDrawEvent_BitmapSnapshot::SetTime(double _time)
    {
        time = _time;
        return 0;
    }

    double WandTimeLineDrawEvent_BitmapSnapshot::GetTime()
    {
        return time;
    }


    int             WandTimeLineDrawEvent_BitmapSnapshot::GetSrc          (EyerVec4 & _src)
    {
        _src = src;
        return 0;
    }

    int             WandTimeLineDrawEvent_BitmapSnapshot::GetDist         (EyerVec4 & _dist)
    {
        _dist = dist;
        return 0;
    }

    int             WandTimeLineDrawEvent_BitmapSnapshot::SetSrc          (float x1, float y1, float x2, float y2)
    {
        src.SetXY1(x1, y1);
        src.SetXY2(x2, y2);
        return 0;
    }

    int             WandTimeLineDrawEvent_BitmapSnapshot::SetDist         (float x1, float y1, float x2, float y2)
    {
        dist.SetXY1(x1, y1);
        dist.SetXY2(x2, y2);
        return 0;
    }
}