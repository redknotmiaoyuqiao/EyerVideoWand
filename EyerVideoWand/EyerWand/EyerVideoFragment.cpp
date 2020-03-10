#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragment * EyerVideoFragment::CopyFragment(const EyerVideoFragment * fragment)
    {
        EyerVideoFragment * f = nullptr;
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            f = new EyerVideoFragmentVideo(*(EyerVideoFragmentVideo *)fragment);
        }
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT){
            f = new EyerVideoFragmentText(*(EyerVideoFragmentText *)fragment);
        }
        return f;
    }


    EyerVideoFragment::~EyerVideoFragment()
    {

    }
}