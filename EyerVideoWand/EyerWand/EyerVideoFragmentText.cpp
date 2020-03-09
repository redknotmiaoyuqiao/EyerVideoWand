#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragmentText::EyerVideoFragmentText()
    {

    }

    EyerVideoFragmentText::~EyerVideoFragmentText()
    {

    }

    int EyerVideoFragmentText::SetFontPath(EyerString path)
    {
        return 0;
    }

    int EyerVideoFragmentText::SetText(EyerString text)
    {
        return 0;
    }

    EyerVideoFragmentType EyerVideoFragmentText::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT;
    }
}