#ifndef	EYER_LIB_AV_WAND_PROCESS_H
#define	EYER_LIB_AV_WAND_PROCESS_H

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    class EyerVPResource;
    class EyerVPAudioRes;
    class EyerVPTrack;

    class EyerVPVideoTrack;
    class EyerVPAudioTrack;

    class EyerVPVideoImage;

    class EyerVPTrack
    {
    public:
    };

    class EyerVPVideoTrack : public EyerVPTrack
    {
    public:
        EyerVPVideoTrack();
        ~EyerVPVideoTrack();
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

        int RenderToFile(EyerString outPath);
    };

    class EyerVPResource
    {
    private:
        EyerString resPath;
        int streamIndex = 0;

        double position = 0;
        double cutterStartTime = 0;
        double cutterEndTime = 0;

        double duration = -1.0;

        // 读取器和解码器不可复制
        EyerAVReader * reader = nullptr;
        EyerAVDecoder * decoder = nullptr;
    public:
        EyerVPResource();
        EyerVPResource(EyerVPResource & audioRes);

        ~EyerVPResource();

        EyerVPResource & operator = (EyerVPResource & audioRes);

        int SetPath(EyerString _resPath);
        int SetStream(int streamIndex);
        int SetPosition(double startTime);
        int SetCutter(double startTime, double endTime);

        EyerString GetRes();
        int GetStreamIndex();
        double GetPosition();
        double GetCutterStartTime();
        double GetCutterEndTime();

        double GetDuration();

        int GetFrame(EyerAVFrame * avFrame);
    };


    class EyerVPAudioRes : public EyerVPResource
    {
    public:

    };

    class EyerVPVideoImage
    {
    public:
        EyerVPVideoImage();
        ~EyerVPVideoImage();

        int GetBitmap(EyerAVBitmap & bitmap);

        int LoadFromImageFile(EyerString path);
    };

    class EyerVPVideoRes : public EyerVPResource
    {
    private:

    public:
        EyerVPVideoRes();
        ~EyerVPVideoRes();
    };
}

#endif
