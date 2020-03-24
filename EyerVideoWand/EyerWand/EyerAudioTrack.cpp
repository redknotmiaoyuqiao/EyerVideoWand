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


    int EyerAudioTrack::RenderFrame(double ts, EyerAVFrame & outFrame)
    {
        EyerLinkedList<EyerAVFrame *> tempFrameManager;
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

            activeLayerList.insertBack(layer);
        }

        EyerAVAudioFrameUtil mergeAudioUtil;

        for(int i=0;i<activeLayerList.getLength();i++){
            EyerAudioLayer * layer = nullptr;
            layoutList.find(i, layer);

            if(layer == nullptr){
                continue;
            }

            EyerAVFrame * oFrame = new EyerAVFrame();
            oFrame->InitAACFrame(6);
            layer->RenderLayerFrame(ts, *oFrame);
            tempFrameManager.insertBack(oFrame);


            float w = layer->GetWeight();
            if(w < 0.0f){
                w = 1.0 / activeLayerList.getLength();
            }

            mergeAudioUtil.AddAudioFrame(*oFrame, w);
        }

        mergeAudioUtil.MergeAudioFrame(outFrame);

        activeLayerList.clear();

        for(int i=0;i<tempFrameManager.getLength();i++){
            EyerAVFrame * f = nullptr;
            tempFrameManager.find(i, f);
            if(f != nullptr){
                delete f;
            }
        }
        tempFrameManager.clear();

        return 0;
    }
}