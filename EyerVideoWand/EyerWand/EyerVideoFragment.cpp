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
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_FRAME_SEQUENTIAL){
            f = new EyerVideoFragmentFrameSequential(*(EyerVideoFragmentFrameSequential *)fragment);
        }
        return f;
    }


    EyerVideoFragment::~EyerVideoFragment()
    {

    }
}