#ifndef	EYER_LIB_AV_WAND_H
#define	EYER_LIB_AV_WAND_H

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer {
    class EyerWand;

    class EyerWandResourse;

    class EyerWandVideoResource;

    class EyerWandAudioResource;

    class EyerTrack;

    class EyerVideoTrack;

    class EyerVideoLayout;

    class EyerWandBuilder;

    class EyerVideoFragment;

    class EyerWand {
    public:
        EyerWand();

        ~EyerWand();
    };

    class EyerWandResource {
    public:
        EyerString resPath;
    public:
        EyerWandResource();

        ~EyerWandResource();

        int SetPath(EyerString resPath);
    };

    class EyerWandVideoResource : public EyerWandResource {
    public:
        EyerWandVideoResource();
        ~EyerWandVideoResource();

        int GetVideoDuration(double & duration);
    };

    class EyerWandAudioResource : public EyerWandResource {
    public:
        EyerWandAudioResource();

        ~EyerWandAudioResource();
    };


    class EyerTrack {

    };

    /**
     * 视频轨
     */
    class EyerVideoTrack : public EyerTrack {
    public:
        EyerVideoTrack();

        ~EyerVideoTrack();

        EyerVideoTrack(const EyerVideoTrack &track);
        EyerVideoTrack & operator = (const EyerVideoTrack &track);

        int AddLayout(const EyerVideoLayout &layout);

        int GetFrameCount();

    private:
        EyerLinkedList<EyerVideoLayout *> layoutList;
    };

    class EyerVideoLayout {
    public:
        EyerVideoLayout();

        ~EyerVideoLayout();

        EyerVideoLayout(const EyerVideoLayout &layout);

        EyerVideoLayout & operator = (const EyerVideoLayout &layout);


        int AddVideoFragment(const EyerVideoFragment & fragment);

        int SetFrame(int startFrameIndex, int endFrameIndex);
        int GetStartFrameIndex();
        int GetEndFrameIndex();

    private:
        int startFrameIndex = 0;
        int endFrameIndex = 0;

        EyerLinkedList<EyerVideoFragment *> videoFragmentList;
    };

    class EyerVideoFragment
    {
    public:
        EyerVideoFragment();
        ~EyerVideoFragment();

        EyerVideoFragment(const EyerVideoFragment & fragment);
        EyerVideoFragment & operator = (const EyerVideoFragment & fragment);

        int LoadVideoFile(EyerString path);

        int SetFrameIndex(int startIndex, int endIndex);
        int SetFrameTime(double startTime, double endTime);

    private:
        EyerString path;

        int startIndex = 0;
        int endIndex = 0;
        double startTime = 0.0;
        double endTime = 0.0;

        Eyer::EyerWandVideoResource videoResource;
        double duration = 0.0;
    };



    class EyerWandBuilder
    {
    public:
        EyerWandBuilder(EyerString path);
        ~EyerWandBuilder();

        int SetVideoWH(int w, int h);
        int SetVideoFPS(int fps);

        int AddVideoTrack(const EyerVideoTrack & videoTrack);

        int Process();

    private:
        int VideoProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug = 0);

    private:
        EyerString path;

        int videoWidth = 0;
        int videoHeight = 0;
        int videoFps = 25;

        EyerVideoTrack videoTrack;
    };
}

#endif
