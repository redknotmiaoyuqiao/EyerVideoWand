#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoTrack::EyerVideoTrack()
    {

    }

    EyerVideoTrack::~EyerVideoTrack()
    {
        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                delete l;
            }
        }

        layoutList.clear();
    }

    EyerVideoTrack::EyerVideoTrack(const EyerVideoTrack & track)
    {
        *this = track;
    }

    EyerVideoTrack & EyerVideoTrack::operator = (const EyerVideoTrack & track)
    {
        if(this == &track){
            return *this;
        }

        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                EyerVideoLayout * _l = new EyerVideoLayout(*l);
                layoutList.insertBack(_l);
            }
        }

        return *this;
    }

    int EyerVideoTrack::AddLayout(const EyerVideoLayout & layout)
    {
        EyerVideoLayout * l = new EyerVideoLayout(layout);
        layoutList.insertBack(l);
        return 0;
    }

    int EyerVideoTrack::GetFrameCount()
    {
        int frameCount = 0;

        // Find Max Frame Index
        int maxFrameIndex = 0;
        for(int i=0;i<layoutList.getLength();i++){
            EyerVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                int endFrameIndex = l->GetEndFrameIndex();
                if(endFrameIndex > maxFrameIndex){
                    maxFrameIndex = endFrameIndex;
                }
            }
        }

        frameCount = maxFrameIndex;

        return frameCount;
    }
}