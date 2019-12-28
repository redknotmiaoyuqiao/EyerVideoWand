#ifndef	EYER_LIB_AV_WAND_PROCESS_H
#define	EYER_LIB_AV_WAND_PROCESS_H

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

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
    private:
        std::vector<EyerVPAudioRes *> audioList;
        EyerAVEncoder encoder;
    public:
        EyerVPAudioTrack();
        ~EyerVPAudioTrack();

        int AddAudioRes(EyerVPAudioRes & audioRes);

        double GetDuration();
    };

    class EyerVPAudioRes
    {
    private:
        EyerString resPath;
        int streamIndex = 0;

        double position = 0;
        double cutterStartTime = 0;
        double cutterEndTime = 0;
    public:
        EyerVPAudioRes();
        EyerVPAudioRes(EyerVPAudioRes & audioRes);

        ~EyerVPAudioRes();

        EyerVPAudioRes & operator = (EyerVPAudioRes & audioRes);

        int SetPath(EyerString _resPath);
        int SetStream(int streamIndex);

        int SetPosition(double startTime);
        int SetCutter(double startTime, double endTime);

        double GetDur();


        EyerString GetRes();
        int GetStreamIndex();
        double GetPosition();
        double GetCutterStartTime();
        double GetCutterEndTime();
    };
}

#endif
