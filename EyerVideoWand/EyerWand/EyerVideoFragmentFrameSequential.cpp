//
// Created by redknot on 2020/4/9.
//
#include "EyerWand.hpp"

namespace Eyer {
    EyerVideoFragmentFrameSequential::EyerVideoFragmentFrameSequential()
    {

    }

    EyerVideoFragmentFrameSequential::~EyerVideoFragmentFrameSequential()
    {

    }

    EyerVideoFragmentFrameSequential::EyerVideoFragmentFrameSequential(const EyerVideoFragmentFrameSequential &vft)
    {
        *this = vft;
    }

    EyerVideoFragmentFrameSequential & EyerVideoFragmentFrameSequential::operator = (const EyerVideoFragmentFrameSequential &vft)
    {
        path = vft.path;
        x = vft.x;
        y = vft.y;
        z = vft.z;

        scaleX = vft.scaleX;
        scaleY = vft.scaleY;
        scaleZ = vft.scaleZ;

        fps = vft.fps;

        return *this;
    }

    EyerVideoFragmentType EyerVideoFragmentFrameSequential::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_FRAME_SEQUENTIAL;
    }


    int EyerVideoFragmentFrameSequential::GetData(EyerMat4x4 & mvp, EyerGLTexture * targetTexture, double time)
    {
        int frameIndex = (int)(time * fps);

        EyerString imagePath = path + "/" + ".png";

        unsigned char * rgba = nullptr;

        int width = 100;
        int height = 100;

        // 读取图片


        targetTexture->SetDataRGBAChannel(rgba, width, height);

        mvp.SetScale(1.0, 1.0, 1.0);

        return 0;
    }
}