#include "EyerWand.hpp"

namespace Eyer
{
    EyerAudioLayer::EyerAudioLayer()
    {

    }

    int EyerAudioLayer::SetWeight(float _weight)
    {
        weight = _weight;
        return 0;
    }

    float EyerAudioLayer::GetWeight()
    {
        return weight;
    }

    EyerAudioLayer::~EyerAudioLayer()
    {
        for(int i=0;i<audioFragmentList.getLength();i++){
            EyerAudioFragment * audio = nullptr;
            audioFragmentList.find(i, audio);
            if(audio != nullptr){
                delete audio;
            }
        }
        audioFragmentList.clear();
    }

    EyerAudioLayer::EyerAudioLayer(const EyerAudioLayer & layer)
    {
        *this = layer;
    }

    EyerAudioLayer & EyerAudioLayer::operator = (const EyerAudioLayer & layer)
    {
        startTime = layer.startTime;
        endTime = layer.endTime;

        for(int i=0;i<layer.audioFragmentList.getLength();i++){

            EyerAudioFragment * audio = nullptr;
            layer.audioFragmentList.find(i, audio);

            if(audio != nullptr){
                EyerAudioFragment * a = new EyerAudioFragment(*audio);
                this->audioFragmentList.insertBack(a);
            }
        }

        return *this;
    }

    int EyerAudioLayer::SetTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    int EyerAudioLayer::AddAudioFragment(const EyerAudioFragment & audio)
    {
        EyerAudioFragment * a = new EyerAudioFragment(audio);
        audioFragmentList.insertBack(a);
        return 0;
    }

    double EyerAudioLayer::GetStartTime()
    {
        return startTime;
    }

    double EyerAudioLayer::GetEndTime()
    {
        return endTime;
    }

    int EyerAudioLayer::RenderLayerFrame(double ts, EyerAVFrame & outFrame)
    {
        EyerAVAudioFrameUtil mergeAudioUtil;

        int audioCount = audioFragmentList.getLength();
        for(int i=0;i<audioFragmentList.getLength();i++){
            EyerAudioFragment * audio = nullptr;
            audioFragmentList.find(i, audio);
            if(audio != nullptr){
                EyerAVFrame frame;
                audio->ReaderAVFrame(ts, frame);

                float w = audio->GetWeight();
                if(w < 0.0f){
                    w = 1.0 / audioCount;
                }
                mergeAudioUtil.AddAudioFrame(frame, w);
            }
        }
        
        mergeAudioUtil.MergeAudioFrame(outFrame);

        return 0;
    }
}