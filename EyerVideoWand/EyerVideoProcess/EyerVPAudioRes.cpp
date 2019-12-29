#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPAudioRes::EyerVPAudioRes()
    {

    }

    EyerVPAudioRes::EyerVPAudioRes(EyerVPAudioRes & audioRes)
    {
        *this = audioRes;
    }

    EyerVPAudioRes::~EyerVPAudioRes()
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

    EyerVPAudioRes & EyerVPAudioRes::operator = (EyerVPAudioRes & audioRes)
    {
        resPath = audioRes.resPath;
        streamIndex = audioRes.streamIndex;
        position = audioRes.position;
        cutterStartTime = audioRes.cutterStartTime;
        cutterEndTime = audioRes.cutterEndTime;

        reader = nullptr;
        decoder = nullptr;

        return *this;
    }

    int EyerVPAudioRes::SetPath(EyerString _resPath)
    {
        resPath = _resPath;
        return 0;
    }

    int EyerVPAudioRes::SetStream(int _streamIndex)
    {
        if(_streamIndex < 0){
            _streamIndex = 0;
        }
        streamIndex = _streamIndex;
        return 0;
    }

    int EyerVPAudioRes::SetPosition(double startTime)
    {
        if(startTime < 0){
            startTime = 0;
        }
        position = startTime;
        return 0;
    }

    int EyerVPAudioRes::SetCutter(double startTime, double endTime)
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

    EyerString EyerVPAudioRes::GetRes()
    {
        return resPath;
    }

    int EyerVPAudioRes::GetStreamIndex()
    {
        return streamIndex;
    }

    double EyerVPAudioRes::GetPosition()
    {
        return position;
    }

    double EyerVPAudioRes::GetCutterStartTime()
    {
        return cutterStartTime;
    }

    double EyerVPAudioRes::GetCutterEndTime()
    {
        return cutterEndTime;
    }









    int EyerVPAudioRes::GetFrame(EyerAVFrame * avFrame)
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

        return -3;
    }
}
