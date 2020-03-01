#include "EyerWand.hpp"

namespace Eyer
{
    EyerAudioFragment::EyerAudioFragment()
    {

    }

    EyerAudioFragment::~EyerAudioFragment()
    {

    }

    EyerAudioFragment::EyerAudioFragment(const EyerAudioFragment & fragment)
    {
        *this = fragment;
    }

    EyerAudioFragment & EyerAudioFragment::operator = (const EyerAudioFragment & fragment)
    {
        return *this;
    }

    int EyerAudioFragment::LoadAudioFile(EyerString _path)
    {
        path = _path;
        return 0;
    }
}