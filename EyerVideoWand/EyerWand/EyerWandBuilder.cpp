#include "EyerWand.hpp"

#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    EyerWandBuilder::EyerWandBuilder(EyerString _path)
    {
        path = _path;
    }

    EyerWandBuilder::~EyerWandBuilder()
    {

    }

    int EyerWandBuilder::SetVideoWH(int w, int h)
    {
        videoWidth = w;
        videoHeight = h;
        return 0;
    }

    int EyerWandBuilder::Process()
    {
        Eyer::EyerAVWriter writer(path);
        writer.Open();

        // AddVideoStream
        Eyer::EyerAVEncoder encoder;
        Eyer::EncoderParam encoderParam;
        encoderParam.width = videoWidth;
        encoderParam.height = videoHeight;
        encoderParam.codecId = Eyer::CodecId::CODEC_ID_H264;
        encoder.Init(&encoderParam);

        int videoStreamIndex = writer.AddStream(&encoder);

        // AddAudioStream

        writer.WriteHand();

        // Video
        // Audio

        writer.Close();
        return 0;
    }
}