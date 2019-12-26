#ifndef	EYER_LIB_AV_H
#define	EYER_LIB_AV_H

#include "EyerCore/Red.hpp"

namespace Eyer
{
    class EyerVPTrack
    {
    public:
    };

    class EyerVPVideoTrack : public EyerVPTrack
    {
    public:
    };

    class EyerVPAudioTrack : public EyerVPTrack
    {
    public:
        EyerVPAudioTrack();
        ~EyerVPAudioTrack();

        int AddAudioRes(RedString resPath, int stream = -1);
    };
}

#endif