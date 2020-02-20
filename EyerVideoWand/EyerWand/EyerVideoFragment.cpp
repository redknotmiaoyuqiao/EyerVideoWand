#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragment::EyerVideoFragment()
    {

    }

    EyerVideoFragment::EyerVideoFragment(EyerVideoFragment & fragment)
    {
        *this = fragment;
    }

    EyerVideoFragment::~EyerVideoFragment()
    {
    }

    EyerVideoFragment & EyerVideoFragment::operator = (EyerVideoFragment & fragment)
    {
        startIndex = fragment.startIndex;
        endIndex = fragment.endIndex;
        startTime = fragment.startTime;
        endTime = fragment.endTime;
        return *this;
    }

    int EyerVideoFragment::LoadVideoFile(EyerString _path)
    {
        path = _path;
        return 0;
    }

    int EyerVideoFragment::SetFrameIndex(int _startIndex, int _endIndex)
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
        return 0;
    }

    int EyerVideoFragment::SetFrameTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }
}