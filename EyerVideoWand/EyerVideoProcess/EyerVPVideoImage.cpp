//
// Created by redknot on 2020/1/5.
//

#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPVideoImage::EyerVPVideoImage()
    {

    }

    EyerVPVideoImage::~EyerVPVideoImage()
    {

    }

    int EyerVPVideoImage::GetBitmap(EyerAVBitmap & bitmap)
    {
        return 0;
    }

    int EyerVPVideoImage::LoadFromImageFile(EyerString path)
    {
        EyerAVReader reader(path);

        int ret = reader.Open();
        if(ret){
            return -1;
        }

        EyerAVStream stream;
        ret = reader.GetStream(stream, 0);
        if(ret){
            return -1;
        }

        EyerAVDecoder decoder;
        decoder.Init(&stream);

        while(1){
            EyerAVPacket pkt;
            ret = reader.Read(&pkt);

            if(ret){
                break;
            }

            decoder.SendPacket(&pkt);

            while(1){
                EyerAVFrame frame;
                ret = decoder.RecvFrame(&frame);
                if(ret){
                    break;
                }

                EyerLog("Width:%d\n", frame.GetWidth());
                EyerLog("Height:%d\n", frame.GetHeight());
                // frame.GetInfo();

                return 0;
            }
        }

        return -2;
    }
}

