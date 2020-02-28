#ifndef	EYER_LIB_AV_WAND_H
#define	EYER_LIB_AV_WAND_H

#include <EyerGL/EyerGL.hpp>
#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#define EYER_WAND_VERSION "1.0.0"

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

    class EyerVideoDecoderLine;

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

    class EyerVideoDecoderLine
    {
    public:
        EyerVideoDecoderLine(EyerString resPath, double initStart);
        ~EyerVideoDecoderLine();

        int GetFrame(EyerAVFrame & frame, double ts);

        double GetStartTime();
    private:
        int ReadFrame();
        int SelectFrameInList(EyerAVFrame * & frame, double ts);

        int fileEndFlag = 0;

        double initStart = 0.0;
        EyerString resPath;

        EyerAVReader * reader = nullptr;
        EyerAVDecoder * decoder = nullptr;
        int videoStreamIndex = -1;

        EyerLinkedList<EyerAVFrame *> frameList;
    };

    class EyerWandVideoResource : public EyerWandResource {
    public:
        EyerWandVideoResource();
        ~EyerWandVideoResource();

        int GetVideoDuration(double & duration);
        int GetVideoFrame(EyerAVFrame & avFrame, double ts);

    private:
        EyerLinkedList<EyerVideoDecoderLine *> decoderLineList;
    };

    class EyerWandAudioResource : public EyerWandResource {
    public:
        EyerWandAudioResource();

        ~EyerWandAudioResource();
    };


    class EyerVideoPanel
    {
    public:
        EyerVideoPanel();
        ~EyerVideoPanel();

        EyerVideoPanel(const EyerVideoPanel & panel);
        EyerVideoPanel & operator = (const EyerVideoPanel & panel);

        int GetYDate(unsigned char * yData);
        int GetUDate(unsigned char * uData);
        int GetVDate(unsigned char * vData);

        int SetData(EyerAVFrame & frame);

        int GetW();
        int GetH();
    private:
        EyerMat4x4 mvp;
        EyerAVFrame frame;
    };


    class EyerTrack {
    public:
        virtual ~EyerTrack()
        {

        }
    };

    /**
     * 视频轨
     */

    class EyerVideoTrackRenderParams
    {
    public:
        int videoW = 0;
        int videoH = 0;
        Eyer::EyerGLFrameBuffer * frameBuffer = nullptr;
        Eyer::EyerGLTextDraw * titleTextDraw = nullptr;
    };

    class EyerVideoTrack : public EyerTrack {
    public:
        EyerVideoTrack();

        ~EyerVideoTrack();

        EyerVideoTrack(const EyerVideoTrack &track);
        EyerVideoTrack & operator = (const EyerVideoTrack &track);

        int AddLayout(const EyerVideoLayout &layout);
        int AddLayer(const EyerVideoLayout &layout);

        int GetFrameCount();

        int RenderFrame(int frameIndex, EyerVideoTrackRenderParams * params, int fps);
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


        int GetVideoFragmentCount();
        int GetVideoPanel(EyerVideoPanel & panel, int videoFragmentIndex, int layoutFrameIndex, int fps);
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

        double GetDuration();

        int Print();

        EyerString GetPath();
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
        int VideoTrackProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug = 0);
    private:
        EyerString path;

        int videoWidth = 0;
        int videoHeight = 0;
        int videoFps = 25;

        EyerVideoTrack videoTrack;
    };


    typedef EyerVideoLayout EyerVideoLayer;
}

#endif
