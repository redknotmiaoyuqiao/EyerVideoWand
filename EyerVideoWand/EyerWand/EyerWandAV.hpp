#ifndef	EYER_LIB_AV_EYER_WAND_AV_H
#define	EYER_LIB_AV_EYER_WAND_AV_H

#include "EyerAV/EyerAV.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"
#include "EyerVideoTweenAnimation/EyerVideoTweenAnimation.hpp"

#define EYER_WAND_VERSION "EyerWand 1.0.0"


// #ifdef EYER_PLATFORM_ANDROID
#include "EyerGLContext/EyerGLContext.hpp"
// #else
// #include "EyerGLWindow/EyerGLWindow.hpp"
// #include "EyerImg/stb_image.h"
// #define STB_IMAGE_IMPLEMENTATION
// #endif

namespace Eyer {
    class EyerWand;
    class EyerWandDebug;

    class EyerWandResourse;

    class EyerWandVideoResource;
    class EyerWandAudioResource;

    class EyerTrack;
    class EyerVideoTrack;
    class EyerVideoLayout;
    class EyerWandBuilder;

    class EyerVideoFragment;
    class EyerAudioFragment;

    class EyerVideoDecoderLine;
    class EyerTransKey;

    class EyerAudioLayer;

    class EyerVideoFragmentVideo;

    class EyerWand {
    public:
        EyerWand();

        ~EyerWand();
    };

    class EyerWandAudioResource : public EyerWandResource {
    public:
        EyerWandAudioResource();
        ~EyerWandAudioResource();
    };

    enum EyerVideoPanelType
    {
        YUV_DATA_PLANE,
        SINGLE_CHANNEL_PLANE
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


        EyerGLTexture targetTexture;


        EyerMat4x4 GetMVPMat();

        EyerMat4x4 mvp;
    private:
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

    /**
     * 音频轨
     */
    class EyerAudioTrack : public EyerTrack {
    public:
        EyerAudioTrack();
        ~EyerAudioTrack();

        EyerAudioTrack(const EyerAudioTrack & track);
        EyerAudioTrack & operator = (const EyerAudioTrack &track);

        int AddLayer(const EyerAudioLayer & layer);

        double GetCountTime();

        int RenderFrame(double ts, EyerAVFrame & outFrame);
    private:
        EyerLinkedList<EyerAudioLayer *> layoutList;
    };

    class EyerAudioLayer {
    public:
        EyerAudioLayer();
        ~EyerAudioLayer();

        EyerAudioLayer(const EyerAudioLayer & layer);
        EyerAudioLayer & operator = (const EyerAudioLayer & layer);

        int RenderLayerFrame(double ts, EyerAVFrame & frame);

        int SetTime(double startTime, double endTime);

        int AddAudioFragment(const EyerAudioFragment & audio);

        int SetWeight(float _weight);
        float GetWeight();

        double GetStartTime();
        double GetEndTime();
    private:
        double startTime = 0.0;
        double endTime = 0.0;

        float weight = -1.0f;

        EyerLinkedList<EyerAudioFragment *> audioFragmentList;
    };

    typedef class EyerVideoLayout {
    public:
        EyerVideoLayout();
        ~EyerVideoLayout();
        EyerVideoLayout(const EyerVideoLayout &layout);
        EyerVideoLayout & operator = (const EyerVideoLayout &layout);

        int SetFPS(int fps);
        int GetFPS();

        int AddVideoFragment(const EyerVideoFragment * fragment);

        int SetFrame(int startFrameIndex, int endFrameIndex);
        int GetStartFrameIndex();
        int GetEndFrameIndex();

        int GetVideoFragmentCount();
        int GetVideoFragment(EyerVideoFragment * & fragment, int index);

        int GetVideoPanel(EyerVideoPanel * panel, EyerVideoFragment ** fragmentP, int videoFragmentIndex, int layoutFrameIndex, int fps, EyerVideoTrackRenderParams * params);
    private:
        int fps = 30;
        int startFrameIndex = 0;
        int endFrameIndex = 0;
        int pFrameIndex = 0;

        EyerLinkedList<EyerVideoFragment *> videoFragmentList;
    } EyerVideoLayer;

    class EyerAudioFragment
    {
    public:
        EyerAudioFragment();
        ~EyerAudioFragment();

        EyerAudioFragment(const EyerAudioFragment & fragment);
        EyerAudioFragment & operator = (const EyerAudioFragment & fragment);

        int SetWeight(float _weight);
        float GetWeight();

        int LoadAudioFile(EyerString path);

        int ReaderAVFrame(double ts, EyerAVFrame & frame);

    private:
        float weight = -1.0f;

        EyerString path;
        EyerVideoDecoderLine * decoderLine = nullptr;
    };

    class EyerTransKey
    {
    public:
        double t = 0.0;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    public:
        bool operator < (const EyerTransKey &key2);

        EyerTransKey();
        EyerTransKey(const EyerTransKey & tk);

        EyerTransKey & operator = (const EyerTransKey & tk);
    };

    enum EyerVideoFragmentType
    {
        VIDEO_FRAGMENT_UNKNOW = -1,
        VIDEO_FRAGMENT_VIDEO = 0,
        VIDEO_FRAGMENT_TEXT = 1,
        VIDEO_FRAGMENT_FRAME_SEQUENTIAL = 2
    };

    class EyerVideoFragment
    {
    public:
        virtual ~EyerVideoFragment();
        virtual EyerVideoFragmentType GetType() const = 0;

        static EyerVideoFragment * CopyFragment(const EyerVideoFragment * fragment);
    };

    enum EyerVideoChangeType
    {
        VIDEO_FRAGMENT_CHANGE_TRANS,
        VIDEO_FRAGMENT_CHANGE_SCALE
    };
    class EyerVideoFragmentVideo : public EyerVideoFragment
    {
    public:
        EyerVideoFragmentVideo();
        ~EyerVideoFragmentVideo();

        EyerVideoFragmentVideo(const EyerVideoFragmentVideo & fragment);
        EyerVideoFragmentVideo & operator = (const EyerVideoFragmentVideo & fragment);

        int LoadVideoFile(EyerString path);

        int SetFrameTime(double startTime, double endTime);
        double GetStartTime();
        double GetEndTime();

        int SetFrameIndex(int startIndex, int endIndex);
        int GetStartIndex();
        int GetEndIndex();
        

        int AddTransKey(double t, float x, float y, float z);
        int AddScaleKey(double t, float x, float y, float z);

        double GetDuration();

        int Print();

        EyerString GetPath();

        int GetVideoFrame(EyerAVFrame & avFrame, double ts);

        virtual EyerVideoFragmentType GetType() const;

        EyerVideoTweenAnimation transAnimation;
        EyerVideoTweenAnimation scaleAnimation;



        int GetW();
        int GetH();
    private:
        EyerString path;

        int startIndex = -1;
        int endIndex = -1;

        double startTime = 0.0;
        double endTime = 0.0;

        double duration = 0.0;

        Eyer::EyerWandVideoResource * videoResource = nullptr;

        int w = -1;
        int h = -1;
    };

    class EyerVideoFragmentText : public EyerVideoFragment
    {
    public:
        EyerVideoFragmentText();
        ~EyerVideoFragmentText();

        EyerVideoFragmentText(const EyerVideoFragmentText & vft);

        EyerVideoFragmentText & operator = (const EyerVideoFragmentText & vft);

        int SetFontPath(EyerString path);
        int SetText(EyerString text);
        int SetColor(float r, float g, float b);
        int SetSize(float size);
        int SetPos(float x, float y);

        int GetTextWidth();

        float GetColorR();
        float GetColorG();
        float GetColorB();

        float GetPosX();
        float GetPosY();

        float GetSize();

        virtual EyerVideoFragmentType GetType() const;

    public:
        EyerString fontPath;
        EyerString text;
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float size = 100.0f;
        float posX = 0.0f;
        float posY = 0.0f;
    };


    class EyerVideoFragmentFrameSequential : public EyerVideoFragment
    {
    public:
        EyerVideoFragmentFrameSequential();
        ~EyerVideoFragmentFrameSequential();

        EyerVideoFragmentFrameSequential(const EyerVideoFragmentFrameSequential & vft);
        EyerVideoFragmentFrameSequential & operator = (const EyerVideoFragmentFrameSequential & vft);

        virtual EyerVideoFragmentType GetType() const;

        int GetData(EyerMat4x4 & mvp, EyerGLTexture * targetTexture, double time, EyerVideoTrackRenderParams * params);

        int SetDirPathModel(EyerString path, int fileNum, int model);

        int SetScale(float scaleX, float scaleY, float scaleZ);

        int SetTrans(float x, float y, float z);

    private:
        EyerString path;
        int fileNum = 0;
        //model 0动画只显示一次  1动画显示一次，且停留在最后一帧   2动画循环显示
        int model = 0;
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;

        float scaleX = 0.0;
        float scaleY = 0.0;
        float scaleZ = 0.0;

        float fps = 10;
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
        int AddLayer(const EyerVideoLayout &layout);

        int GetFrameCount();

        int GetLayerCount();
        int GetLayer(EyerVideoLayout * & layout, int index);


        int RenderFrame(int frameIndex, EyerVideoTrackRenderParams * params, int fps);
// #ifdef EYER_PLATFORM_ANDROID
        int RenderFrame2(int frameIndex, int fps, EyerGLContextThread * glCtx);
// #endif

        int SetTargetVideoWH(int w, int h);
        int SetTargetVideoFPS(int fps);

        int GetVideoW();
        int GetVideoH();
        int GetFPS();


        EyerVideoLayer *  GetVideoLayer_Ptr();
        int GetVideoLayer_Copy(EyerVideoLayer & videoLayer);


        int VideoLayer_AddVideoFragment(EyerVideoFragmentVideo & fragmentVideo);
        int VideoLayer_GetFragmentCount();
        int VideoLayer_GetFragment(EyerVideoFragment * & fragment, int index);
    private:
        EyerLinkedList<EyerVideoLayout *> layoutList;

        int videoW = 0;
        int videoH = 0;

        int fps = 30;

        EyerVideoLayer videoLayer;
    };


    class EyerWandBuilder
    {
    public:
        EyerWandBuilder(EyerString path);
        ~EyerWandBuilder();

        int SetVideoWH(int w, int h);
        int SetVideoFPS(int fps);

        int AddVideoTrack(const EyerVideoTrack & videoTrack);
        int AddAudioTrack(const EyerAudioTrack & audioTrack);

        int Process();

    private:
        int VideoProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug = 0);
        int VideoTrackProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug = 0);
        int AudioTrackProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug = 0);
    private:
        EyerString path;

        int videoWidth = 0;
        int videoHeight = 0;
        int videoFps = 25;

        EyerVideoTrack videoTrack;
        EyerAudioTrack audioTrack;
    };

    class EyerWandDebug
    {
    public:
        static long long DecoderTime;
        static long long RenderTime;
    };
}

#endif
