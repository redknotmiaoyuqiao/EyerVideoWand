//
// Created by redknot on 2020/4/9.
//
#include "EyerWand.hpp"
#include <stdio.h>

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
        fileNum = vft.fileNum;
        model = vft.model;

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


    int EyerVideoFragmentFrameSequential::GetData(EyerMat4x4 & mvp, EyerGLTexture * targetTexture, double time, EyerVideoTrackRenderParams * params)
    {
        int frameIndex = (int)(time * fps);

        if(model == 0 && frameIndex >= fileNum){
            return -1;
        }
        if(model == 1 && frameIndex >= fileNum){
            frameIndex = fileNum -1;
        }
        if(model == 2 && frameIndex >= fileNum){
            frameIndex = frameIndex%fileNum;
        }

        EyerString picNameNum = EyerString::Number(frameIndex, "%03d");

        EyerString imagePath = path + "/" + picNameNum +".png";

        // 读取图片
        int width, height, nrChannels;
        unsigned char * rgba = stbi_load(imagePath.str, &width, &height, &nrChannels, 0);
        if(width <= 0){
            EyerLog("imagePath:%s, width:%d, height:%d, nrChannels:%d\n",imagePath.str, width, height, nrChannels);
        }

        /*
        FILE * f = fopen("./aaa.rgba", "wb");
        fwrite(rgba, 1, width * height * nrChannels, f);
        fclose(f);
        */

        targetTexture->SetDataRGBAChannel(rgba, width, height);

        EyerMat4x4 ortho;
        int w = params->videoW;
        int h = params->videoH;
        ortho.SetOrtho(- w / 2.0, w / 2.0, h / 2.0, - h / 2.0, 0.0f, 1000.0f);

        EyerMat4x4 scale;
        scale.SetScale(scaleX / 2, scaleY / 2, scaleY / 2);
        EyerMat4x4 trans;
        trans.SetTrans(x, y, z);
        mvp = ortho * trans * scale ;

        return 0;
    }

    int EyerVideoFragmentFrameSequential::SetDirPathModel(EyerString _path, int _fileNum, int _model)
    {
        path = _path;
        fileNum = _fileNum;
        model = _model;
        return 0;
    }

    int EyerVideoFragmentFrameSequential::SetScale(float _scaleX, float _scaleY, float _scaleZ)
    {
        scaleX = _scaleX;
        scaleY = _scaleY;
        scaleZ = _scaleZ;
        return 0;
    }

    int EyerVideoFragmentFrameSequential::SetTrans(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
        return 0;
    }
}