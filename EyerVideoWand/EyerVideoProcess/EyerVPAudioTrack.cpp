#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPAudioTrack::EyerVPAudioTrack()
    {
        EncoderParam param;
        param.codecId = CodecId::CODEC_ID_AAC;
        encoder.Init(&param);
    }

    EyerVPAudioTrack::~EyerVPAudioTrack()
    {
        for(int i=0;i<audioList.size();i++){
            EyerVPAudioRes * res = audioList[i];
            delete res;
        }
        audioList.clear();
    }

    int EyerVPAudioTrack::AddAudioRes(EyerVPAudioRes & audioRes)
    {
        EyerVPAudioRes * resouse = new EyerVPAudioRes(audioRes);
        audioList.push_back(resouse);
        return 0;
    }

    double EyerVPAudioTrack::GetDuration()
    {
        double duration = 0;
        for(int i=0;i<audioList.size();i++){
            EyerVPAudioRes * res = audioList[i];

            Eyer::EyerAVReader reader(res->GetRes());
            int ret = reader.Open();
            if(ret){
                continue;
            }

            int streamCount = reader.GetStreamCount();
            if(res->GetStreamIndex() < 0 || res->GetStreamIndex() >= streamCount){
                reader.Close();
                continue;
            }

            EyerAVStream stream;
            ret = reader.GetStream(stream, res->GetStreamIndex());
            if(ret){
                reader.Close();
                continue;
            }

            long long d = stream.GetDuration() + res->GetPosition();
            if(duration < d){
                duration = d;
            }

            reader.Close();
        }
        return duration;
    }
}
