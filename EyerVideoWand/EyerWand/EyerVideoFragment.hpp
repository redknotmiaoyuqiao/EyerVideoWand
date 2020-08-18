#ifndef EYE_VIDEO_WAND_EYERVIDEOFRAGMENT_HPP
#define EYE_VIDEO_WAND_EYERVIDEOFRAGMENT_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer {
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

    class EyerVideoFragmentVideo : public EyerVideoFragment
    {
    public:
        EyerVideoFragmentVideo();
        virtual ~EyerVideoFragmentVideo();

        EyerVideoFragmentVideo(const EyerVideoFragmentVideo & fragment);
        EyerVideoFragmentVideo & operator = (const EyerVideoFragmentVideo & fragment);

        virtual EyerVideoFragmentType GetType() const;


        int Load(EyerString url);
        int SetTime(double startTime, double endTime);

        int GetFrame(EyerAVFrame & frame, double ts);

        int PrintInfo();
    private:
        Eyer::EyerWandVideoResource videoResource;

        double startTime = 0.0;
        double endTime = -1.0;
    };
}

#endif //EYE_VIDEO_WAND_EYERVIDEOFRAGMENT_HPP
