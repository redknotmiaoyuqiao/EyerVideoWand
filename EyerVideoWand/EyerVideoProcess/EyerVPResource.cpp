#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPResource::EyerVPResource()
    {

    }

    EyerVPResource::EyerVPResource(EyerVPResource & audioRes)
    {
        *this = audioRes;
    }

    EyerVPResource::~EyerVPResource()
    {
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }
    }

    EyerVPResource & EyerVPResource::operator = (EyerVPResource & audioRes)
    {
        resPath = audioRes.resPath;
        streamIndex = audioRes.streamIndex;
        position = audioRes.position;
        cutterStartTime = audioRes.cutterStartTime;
        cutterEndTime = audioRes.cutterEndTime;
        duration = audioRes.duration;

        reader = nullptr;
        decoder = nullptr;

        return *this;
    }

    int EyerVPResource::SetPath(EyerString _resPath)
    {
        resPath = _resPath;
        return 0;
    }

    int EyerVPResource::SetStream(int _streamIndex)
    {
        if(_streamIndex < 0){
            _streamIndex = 0;
        }
        streamIndex = _streamIndex;
        return 0;
    }

    int EyerVPResource::SetPosition(double startTime)
    {
        if(startTime < 0){
            startTime = 0;
        }
        position = startTime;
        return 0;
    }

    int EyerVPResource::SetCutter(double startTime, double endTime)
    {
        if(startTime < 0){
            startTime = 0;
        }

        if(endTime < startTime){
            endTime = startTime;
        }
        cutterStartTime = startTime;
        cutterEndTime = endTime;
        return 0;
    }

    EyerString EyerVPResource::GetRes()
    {
        return resPath;
    }

    int EyerVPResource::GetStreamIndex()
    {
        return streamIndex;
    }

    double EyerVPResource::GetPosition()
    {
        return position;
    }

    double EyerVPResource::GetCutterStartTime()
    {
        return cutterStartTime;
    }

    double EyerVPResource::GetCutterEndTime()
    {
        return cutterEndTime;
    }

    double EyerVPResource::GetDuration()
    {
        if(duration > 0.0){
            return duration;
        }

        Eyer::EyerAVReader reader(GetRes());
        int ret = reader.Open();
        if(ret){
            duration = -1.0;
            return duration;
        }

        EyerAVStream audioStream;
        ret = reader.GetStream(audioStream, streamIndex);
        if(ret){
            duration = -1.0;
            return duration;
        }

        EyerAVDecoder decoder;
        decoder.Init(&audioStream);

        int fremeSize = decoder.GetFrameSize();
        int sampleRate = decoder.GetSampleRate();

        int frameCount = 0;
        while(1){
            EyerAVPacket packet;
            ret = reader.Read(&packet);
            if(ret){
                break;
            }

            frameCount++;
        }

        duration = frameCount * fremeSize * 1.0 / sampleRate;

        reader.Close();

        return duration;
    }



    int EyerVPResource::GetFrame(EyerAVFrame * avFrame)
    {
        if(reader == nullptr){
            reader = new EyerAVReader(GetRes());
            int ret = reader->Open();
            if(ret){
                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }

            EyerAVStream stream;
            ret = reader->GetStream(stream, GetStreamIndex());
            if(ret){
                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }

            if(decoder != nullptr){
                delete decoder;
                decoder = nullptr;
            }

            decoder = new EyerAVDecoder();
            ret = decoder->Init(&stream);
            if(ret){
                delete decoder;
                decoder = nullptr;

                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }
        }

        EyerAVPacket packet;
        int ret = reader->Read(&packet);
        if(ret){
            reader->Close();
            delete reader;
            reader = nullptr;
            return -2;
        }
        decoder->SendPacket(&packet);
        while(1){
            ret = decoder->RecvFrame(avFrame);
            if(ret){
                break;
            }

            return 0;
        }

        reader->Close();
        delete reader;
        reader = nullptr;

        return -3;
    }
}
