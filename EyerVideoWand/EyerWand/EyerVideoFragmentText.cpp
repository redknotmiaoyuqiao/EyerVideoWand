#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragmentText::EyerVideoFragmentText()
    {

    }

    EyerVideoFragmentText::~EyerVideoFragmentText()
    {

    }

    EyerVideoFragmentText::EyerVideoFragmentText(const EyerVideoFragmentText & vft)
    {
        *this = vft;
    }

    EyerVideoFragmentText & EyerVideoFragmentText::operator = (const EyerVideoFragmentText & vft)
    {
        fontPath = vft.fontPath;
        text = vft.text;

        return *this;
    }

    int EyerVideoFragmentText::SetFontPath(EyerString path)
    {
        fontPath = path;
        return 0;
    }

    int EyerVideoFragmentText::SetText(EyerString _text)
    {
        text = _text;
        return 0;
    }

    EyerVideoFragmentType EyerVideoFragmentText::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT;
    }
}