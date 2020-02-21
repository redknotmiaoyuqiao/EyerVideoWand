#include "EyerWand.hpp"

namespace Eyer
{
    EyerWandVideoResource::EyerWandVideoResource()
    {

    }

    EyerWandVideoResource::~EyerWandVideoResource()
    {

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