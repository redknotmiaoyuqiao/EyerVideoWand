#ifndef	EYER_LIB_AV_WAND_H
#define	EYER_LIB_AV_WAND_H

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerWand;
    class EyerWandResourse;
    class EyerWandVideoResource;
    class EyerWandAudioResource;

    class EyerWandBuilder;

    class EyerWand
    {
    public:
        EyerWand();
        ~EyerWand();
    };

    class EyerWandResource
    {
    private:
        EyerString resPath;
    public:
        EyerWandResource();
        ~EyerWandResource();

        int SetPath(EyerString resPath);
    };

    class EyerWandVideoResource : public EyerWandResource
    {
    public:
        EyerWandVideoResource();
        ~EyerWandVideoResource();
    };

    class EyerWandAudioResource : public EyerWandResource
    {
    public:
        EyerWandAudioResource();
        ~EyerWandAudioResource();
    };

    class EyerWandBuilder
    {
    private:
        EyerString path;

        int videoWidth = 0;
        int videoHeight = 0;
    public:
        EyerWandBuilder(EyerString path);
        ~EyerWandBuilder();

        int SetVideoWH(int w, int h);

        int Process();
    };
}

#endif
