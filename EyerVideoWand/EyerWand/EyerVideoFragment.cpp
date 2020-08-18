#include "EyerVideoFragment.hpp"

namespace Eyer
{
    EyerVideoFragment * EyerVideoFragment::CopyFragment(const EyerVideoFragment * fragment)
    {
        EyerVideoFragment * f = nullptr;
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            f = new EyerVideoFragmentVideo(*(EyerVideoFragmentVideo *)fragment);
        }

        return f;
    }


    EyerVideoFragment::~EyerVideoFragment()
    {

    }
}