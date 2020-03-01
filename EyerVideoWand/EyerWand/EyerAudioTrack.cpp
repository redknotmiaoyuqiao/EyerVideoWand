#include "EyerWand.hpp"

namespace Eyer
{
    EyerAudioTrack::EyerAudioTrack()
    {

    }

    EyerAudioTrack::~EyerAudioTrack()
    {
        for(int i=0;i<layoutList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            layoutList.find(i, layer);
            if(layer != nullptr){
                delete layer;
            }
        }

        layoutList.clear();
    }

    EyerAudioTrack::EyerAudioTrack(const EyerAudioTrack & track)
    {
        *this = track;
    }

    EyerAudioTrack & EyerAudioTrack::operator = (const EyerAudioTrack &track)
    {
        for(int i=0;i<track.layoutList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            track.layoutList.find(i, layer);
            if(layer != nullptr){
                EyerAudioLayer * l = new EyerAudioLayer(*layer);
                layoutList.insertBack(l);
            }
        }
        return *this;
    }

    int EyerAudioTrack::AddLayer(const EyerAudioLayer & layer)
    {
        EyerAudioLayer * l = new EyerAudioLayer(layer);
        layoutList.insertBack(l);
        return 0;
    }

    double EyerAudioTrack::GetCountTime()
    {
        double countTime = 0.0;
        for(int i=0;i<layoutList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            layoutList.find(i, layer);
            if(layer != nullptr){
                if(countTime <= layer->GetEndTime()){
                    countTime = layer->GetEndTime();
                }
            }
        }

        return countTime;
    }
}