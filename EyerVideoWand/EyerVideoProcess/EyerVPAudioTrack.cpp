#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPAudioTrack::EyerVPAudioTrack()
    {

    }

    EyerVPAudioTrack::~EyerVPAudioTrack()
    {
        for(int i=0;i<audioList.size();i++){
            EyerVPAudioRes * res = audioList[i];
            delete res;
        }
        audioList.clear();
    }

    int EyerVPAudioTrack::AddAudioRes(EyerVPAudioRes & audioRes)
    {
        EyerVPAudioRes * resouse = new EyerVPAudioRes(audioRes);
        audioList.push_back(resouse);
        return 0;
    }
}
