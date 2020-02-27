#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoDecoderLine::EyerVideoDecoderLine(EyerString _resPath, double _initStart)
    {
        initStart = _initStart;
        resPath = _resPath;
        reader = new EyerAVReader(resPath);
        int ret = reader->Open();
        if(ret){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

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

        EyerAVStream avStream;
        ret = reader->GetStream(avStream, videoStreamIndex);

        decoder = new EyerAVDecoder();
        decoder->Init(&avStream);

        reader->SeekFrame(videoStreamIndex, initStart);
    }

    EyerVideoDecoderLine::~EyerVideoDecoderLine()
    {
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        while (frameQueue.getSize() > 0){
            EyerAVFrame * frame = nullptr;
            frameQueue.deQueue(frame);
            if(frame != nullptr){
                delete frame;
            }
        }
        frameQueue.clear();
    }
}