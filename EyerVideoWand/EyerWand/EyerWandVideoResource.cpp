#include "EyerWand.hpp"

namespace Eyer
{
    EyerWandVideoResource::EyerWandVideoResource()
    {

    }

    EyerWandVideoResource::~EyerWandVideoResource()
    {

    }

    int EyerWandVideoResource::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        int finalRet = 0;

        Eyer::EyerAVReader reader(resPath);
        int videoStreamIndex = -1;
        int streamCount = 0;
        EyerAVStream avStream;
        EyerAVDecoder decoder;

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

        ret = decoder.Init(&avStream);
        if(ret){
            finalRet = -1;
            goto END;
        }

        reader.SeekFrame(videoStreamIndex, ts);
        while(1){
            EyerAVPacket pkt;
            ret = reader.Read(&pkt);
            if(ret){
                break;
            }
            if(pkt.GetStreamId() != videoStreamIndex){
                continue;
            }

            ret = decoder.SendPacket(&pkt);

            while(1){
                EyerAVFrame frame;
                ret = decoder.RecvFrame(&frame);
                if(ret){
                    break;
                }

                Eyer::EyerAVRational streamTimebase;
                reader.GetStreamTimeBase(streamTimebase, videoStreamIndex);

                double t = frame.GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

                if(t < ts){
                }
                if(t >= ts){
                    avFrame = frame;
                    finalRet = 0;
                    goto END;
                }
            }
        }

        decoder.SendPacket(nullptr);
        while(1){
            EyerAVFrame frame;
            ret = decoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            Eyer::EyerAVRational streamTimebase;
            reader.GetStreamTimeBase(streamTimebase, videoStreamIndex);

            double t = frame.GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

            if(t < ts){
            }
            if(t >= ts){

                avFrame = frame;
                finalRet = 0;
                goto END;
            }
        }

    END:
        ret = reader.Close();

        return finalRet;
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
}