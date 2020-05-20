#include "EyerWand.hpp"

namespace Eyer
{
    EyerWandVideoResource::EyerWandVideoResource()
    {

    }

    EyerWandVideoResource::~EyerWandVideoResource()
    {
        mut.lock();
        for(int i=0;i<decoderLineList.getLength();i++){
            EyerVideoDecoderLine * decoderLine = nullptr;
            decoderLineList.find(i, decoderLine);
            if(decoderLine != nullptr){
                delete decoderLine;
            }
        }
        decoderLineList.clear();
        mut.unlock();
    }

    int EyerWandVideoResource::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        mut.lock();
        // EyerLog("Deocde Line: %d\n", decoderLineList.getLength());
        // EyerLog("=============================================Start\n");

        // 将多余的 Decoder Line 删除
        while(decoderLineList.getLength() > 5){
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(0, dl);
            if(dl != nullptr){
                delete dl;
            }
            decoderLineList.deleteEle(0);
        }

        // 统计一下当前一共缓冲了多少帧 Debug 用
        int cacheFrameCount = 0;
        for(int i=0;i<decoderLineList.getLength();i++) {
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(i, dl);
            if(dl != nullptr){
                cacheFrameCount += dl->GetCacheFrameCount();
            }
        }

        // EyerLog("Cache Frame Count: %d\n", cacheFrameCount);

        // 搜索何时的 Decoder Line
        EyerVideoDecoderLine * decoderLine = nullptr;
        for(int i=0;i<decoderLineList.getLength();i++) {
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(i, dl);
            if(ts >= dl->GetStartTime()){
                decoderLine = dl;
            }
        }

        // 搜索不到的情况下新建一个 Decoder Line
        if(decoderLine == nullptr){
            // EyerLog("new EyerVideoDecoderLine  : %f\n", ts);
            decoderLine = new EyerVideoDecoderLine(resPath, ts);
            decoderLineList.insertBack(decoderLine);
        }

        decoderLine->GetFrame(avFrame, ts);

        // EyerLog("=============================================End\n");

        mut.unlock();

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
}