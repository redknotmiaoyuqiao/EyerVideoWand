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


    int EyerAudioTrack::RenderFrame(double ts, float * frameData, int frameDataSize)
    {
        EyerLinkedList<EyerAudioLayer *> activeLayerList;
        for(int i=0;i<layoutList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            layoutList.find(i, layer);

            if(layer == nullptr){
                continue;
            }

            if(layer->GetStartTime() > ts){
                continue;
            }
            if(layer->GetEndTime() < ts){
                continue;
            }

            // EyerLog("Layer\n");

            activeLayerList.insertBack(layer);
        }


        EyerLinkedList<float *> dataCache;
        for(int i=0;i<activeLayerList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            layoutList.find(i, layer);

            if(layer == nullptr){
                continue;
            }

            float * layerData = (float *)malloc(frameDataSize);
            memset(layerData, 0, frameDataSize);

            layer->RenderLayerFrame(ts, layerData, frameDataSize);

            dataCache.insertBack(layerData);
        }

        for(int j=0;j<frameDataSize / 4;j++){
            float a = 0.0;
            for(int i=0;i<dataCache.getLength();i++){
                float * arr = nullptr;
                dataCache.find(i, arr);
                if(arr != nullptr){
                    a += arr[j];
                }
            }

            a = a / dataCache.getLength();

            frameData[j] = a;
        }

        for(int i=0;i<dataCache.getLength();i++){
            float * d = nullptr;
            dataCache.find(i,d);
            if(d != nullptr){
                int layerCount = dataCache.getLength();

            }
        }

        for(int i=0;i<dataCache.getLength();i++){
            float * d = nullptr;
            dataCache.find(i,d);
            if(d != nullptr){
                free(d);
            }
        }

        return 0;
    }
}