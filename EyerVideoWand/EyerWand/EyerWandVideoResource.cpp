#include "EyerWand.hpp"

namespace Eyer
{
    EyerWandVideoResource::EyerWandVideoResource()
    {
        decoder = new EyerAVDecoder();
    }

    EyerWandVideoResource::~EyerWandVideoResource()
    {
        FreeReader();

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
    }

    int EyerWandVideoResource::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        if(!initFlag){
            Init();
        }
        if(!initFlag){
            return -1;
        }

        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

        // double t = frame.GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;



        return 0;
    }

    int EyerWandVideoResource::LoadFrame2List()
    {
        if(!initFlag){
            return -1;
        }

        EyerAVPacket pkt;
        int ret = reader->Read(&pkt);

        ret = decoder->SendPacket(&pkt);
        while(1){
            EyerAVFrame frame;
            ret = decoder->RecvFrame(&frame);
            if(ret){
                break;
            }
        }
        return 0;
    }

    int EyerWandVideoResource::GetVideoDuration(double & duration)
    {
        int finalRet = 0;

        Eyer::EyerAVReader reader(resPath);
        int videoStreamIndex = -1;
        int streamCount = 0;
        EyerAVStream avStream;

        int ret = reader.Open();
        if(ret){
            finalRet = -1;
            goto END;
        }

        streamCount = reader.GetStreamCount();
        for(int i=0;i<streamCount;i++){
            EyerAVStream stream;
            ret = reader.GetStream(stream, i);
            if(ret){
                continue;
            }

            if(stream.GetStreamType() == EyerAVStreamType::STREAM_TYPE_VIDEO){
                videoStreamIndex = i;
            }
        }

        if(videoStreamIndex < 0){
            finalRet = -1;
            goto END;
        }

        ret = reader.GetStream(avStream, videoStreamIndex);
        if(ret){
            finalRet = -1;
            goto END;
        }

        finalRet = 0;
        duration = avStream.GetDuration();

    END:
        ret = reader.Close();

        return finalRet;
    }

    int EyerWandVideoResource::Init()
    {
        int ret = 0;
        if(reader == nullptr){
            reader = new EyerAVReader(resPath);
            int ret = reader->Open();
            if(ret){
                FreeReader();
                return -1;
            }
        }

        // Get Video Stream
        int streamCount = reader->GetStreamCount();
        for(int i=0;i<streamCount;i++){
            EyerAVStream stream;
            ret = reader->GetStream(stream, i);
            if(ret){
                continue;
            }

            if(stream.GetStreamType() == EyerAVStreamType::STREAM_TYPE_VIDEO){
                videoStreamIndex = i;
            }
        }
        if(videoStreamIndex < 0){
            return -1;
        }

        EyerAVStream avStream;
        ret = reader->GetStream(avStream, videoStreamIndex);
        if(ret){
            return -1;
        }

        ret = decoder->Init(&avStream);
        if(ret){
            return -1;
        }

        initFlag = 1;

        return 0;
    }

    int EyerWandVideoResource::InitReader()
    {
        FreeReader();
        reader = new EyerAVReader(resPath);
        int ret = reader->Open();
        if(ret){
            FreeReader();
            return -1;
        }
        return 0;
    }

    int EyerWandVideoResource::FreeReader()
    {
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }
        return 0;
    }
}