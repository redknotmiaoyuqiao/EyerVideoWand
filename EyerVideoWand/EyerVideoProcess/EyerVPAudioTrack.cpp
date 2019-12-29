#include "EyerVideoProcess.hpp"

#include <math.h>

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

    int EyerVPAudioTrack::RenderToFile(EyerString outPath)
    {
        Eyer::EyerAVWriter writer(outPath);
        int streamIndex = writer.AddStream(&encoder);
        writer.Open();

        // 记录当前写入的长度
        double wirteTime = 0.0;

        while(1){
            if(wirteTime >= GetDuration()){
                break;
            }

            int bufferSize = encoder.GetBufferSize();
            int sampSize = bufferSize / 4 / 2;
            double dTime = sampSize * 1.0 / 44100;

            std::vector<EyerVPAudioRes *> alternateList;
            for(int i=0;i<audioList.size();i++){
                EyerVPAudioRes * res = audioList[i];

                double startTime = res->GetPosition();
                double endTime = startTime + 10000.0;

                if(wirteTime >= startTime && wirteTime <= endTime){
                    alternateList.push_back(res);
                }
            }

            // Create Frame
            Eyer::EyerAVFrame avFrame;
            avFrame.SetZero(&encoder);

            for(int i=0;i<alternateList.size();i++){
                EyerVPAudioRes * res = alternateList[i];
                Eyer::EyerAVFrame resAvFrame;
                int ret = res->GetFrame(&resAvFrame);
                if(ret){
                    continue;
                }
            }

            // avFrame.SetPTS((long long)(wirteTime * 90000));

            encoder.SendFrame(&avFrame);
            while(1){
                Eyer::EyerAVPacket avPacket;
                int ret = encoder.RecvPacket(&avPacket);
                if(ret){
                    break;
                }

                avPacket.SetStreamId(streamIndex);

                printf("PTS:%lld\n", avPacket.GetPTS());

                writer.WritePacket(&avPacket);

                wirteTime += dTime;
            }
        }

        writer.Close();

        return 0;
    }
}
