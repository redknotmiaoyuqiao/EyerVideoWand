#ifndef	EYER_LIB_AV_H
#define	EYER_LIB_AV_H

#include "EyerCore/Red.hpp"

namespace Eyer
{
    class EyerVPAudioRes;
    class EyerVPTrack;
    class EyerVPVideoTrack;
    class EyerVPAudioTrack;

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

        int AddAudioRes(EyerVPAudioRes & audioRes);
    };

    class EyerVPAudioRes
    {
    private:
        RedString resPath;
        int streamIndex = 0;

        long long position = 0;
        long long cutterStartTime = 0;
        long long cutterEndTime = 0;
    public:
        EyerVPAudioRes();
        EyerVPAudioRes(EyerVPAudioRes & res);

        ~EyerVPAudioRes();


        int SetPath(RedString _resPath);
        int SetStream(int streamIndex);

        int SetPosition(long long startTime);
        int SetCutter(long long startTime, long long endTime);

        long long GetDur();
        
    };
}

#endif