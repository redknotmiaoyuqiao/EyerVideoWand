#include "EyerWandAV.hpp"
#include <math.h>

namespace Eyer
{
    EyerVideoDecoderLine::EyerVideoDecoderLine(EyerString _resPath, double _initStart, EyerAVStreamType type)
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

            if(stream.GetStreamType() == type){
                videoStreamIndex = i;
            }
        }

        EyerAVStream avStream;
        ret = reader->GetStream(avStream, videoStreamIndex);

        decoder = new EyerAVDecoder();
        decoder->Init(&avStream);

        reader->SeekFrame(-1, (int64_t)(initStart * 1000000));
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

        for(int i=0;i<frameList.getLength();i++){
            EyerAVFrame * f = nullptr;
            frameList.find(i, f);
            if(f != nullptr){
                delete f;
            }
        }
        frameList.clear();
    }

    int EyerVideoDecoderLine::GetFrame(EyerAVFrame & frame, double ts)
    {
        int finalRet = 0;
        if(ts < GetStartTime()){
            finalRet = -1;
            return finalRet;
        }

        while(1){
            int ret = SelectFrameInList(frame, ts);
            if(ret){
                // EyerLog("Find Error\n");
                if(fileEndFlag){
                    // EyerLog("Find Error=======Size:%d\n", frameList.getLength());
                    int length = frameList.getLength();
                    // 已经到了末尾，取最后一帧，退出
                    if(frameList.getLength() <= 0){
                        finalRet = -2;
                        break;
                    }
                    int lastInex = frameList.getLength() - 1;

                    EyerAVFrame * pFrame = nullptr;
                    frameList.find(lastInex, pFrame);
                    if(pFrame != nullptr){
                        frame = *pFrame;
                        finalRet = 0;
                        break;
                    }
                }
                ReadFrame();
                continue;
            }
            else{
                // EyerLog("Find Ok\n");
                finalRet = 0;
                break;
            }
        }

        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

        double t = frame.GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        return finalRet;
    }

    double EyerVideoDecoderLine::GetStartTime()
    {
        if(frameList.getLength() <= 0){
            return initStart;
        }

        EyerAVFrame * f = nullptr;
        frameList.find(0, f);
        if(f == nullptr){
            return initStart;
        }

        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

        double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        return t;
    }

    int EyerVideoDecoderLine::GetCacheFrameCount()
    {
        return frameList.getLength();
    }












    int EyerVideoDecoderLine::ReadFrame()
    {
        if(reader == nullptr){
            return -1;
        }
        EyerAVPacket pkt;
        int ret = reader->Read(&pkt);

        if(ret){
            decoder->SendPacket(nullptr);
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }
                // EyerLog("Frame %d %d\n", frame->GetWidth(), frame->GetHeight());
                frameList.insertBack(frame);
            }
            fileEndFlag = 1;
        }
        else{
            if(pkt.GetStreamId() != videoStreamIndex){
                return -1;
            }

            decoder->SendPacket(&pkt);
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }

                frameList.insertBack(frame);
            }
        }
        
        return 0;
    }
    int EyerVideoDecoderLine::SelectFrameInList(EyerAVFrame & frame, double ts)
    {
        EyerAVFrame * ff = nullptr;

        for(int i=0;i<frameList.getLength();i++){   
            EyerAVFrame * f = nullptr;
            frameList.find(i, f);
            if(f == nullptr){
                continue;
            }

            Eyer::EyerAVRational streamTimebase;
            reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

            double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

            // EyerLog("t: %f ts: %f\n", t, ts);

            if(t > ts){
                if(i <= 1){
                    ff = f;
                }
                else{
                    // 向前检索一帧进行比较
                    EyerAVFrame * lastF = nullptr;
                    frameList.find(i - 1, lastF);
                    if(lastF == nullptr){
                        break;
                    }

                    double lastFT = lastF->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

                    if(abs(lastFT - ts) < abs(t - ts)){
                        ff = lastF;
                    }
                    else{
                        ff = f;
                    }
                }

                break;
            }
            if(t == ts){
                ff = f;
                break;
            }
        }

        int isError = -1;
        if(ff != nullptr){
            frame = *ff;
            isError = 0;
        }

        // 无论成功还是失败，都要丢帧
        while(frameList.getLength() > 5){
            EyerAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f != nullptr){
                delete f;
            }
            frameList.deleteEle(0);
        }

        return isError;
    }
}