//
// Created by lichi on 2020/8/17.
//

#include "EyerVideoLayer.hpp"

namespace Eyer {
    EyerVideoLayer::EyerVideoLayer()
    {

    }

    EyerVideoLayer::~EyerVideoLayer()
    {
        int fragmentLength = videoFragmentList.getLength();
        for(int i=0;i<fragmentLength;i++){
            EyerVideoFragment * fsrc = nullptr;
            videoFragmentList.find(i, fsrc);
            if(fsrc == nullptr){
                continue;
            }
            delete fsrc;
        }
        videoFragmentList.clear();
    }

    EyerVideoLayer::EyerVideoLayer(const EyerVideoLayer & videoLayer) : EyerVideoLayer()
    {
        *this = videoLayer;
    }

    const EyerVideoLayer & EyerVideoLayer::operator = (const EyerVideoLayer & videoLayer)
    {
        /// 拷贝所有的 Fragment
        int fragmentLength = videoLayer.videoFragmentList.getLength();
        for(int i=0;i<fragmentLength;i++){
            EyerVideoFragment * fsrc = nullptr;
            videoLayer.videoFragmentList.find(i, fsrc);
            if(fsrc == nullptr){
                continue;
            }

            EyerVideoFragment * fdist = EyerVideoFragment::CopyFragment(fsrc);
            videoFragmentList.insertBack(fdist);
        }

        return *this;
    }

    int EyerVideoLayer::AddVideoFragment(const Eyer::EyerVideoFragment * fragment)
    {
        EyerVideoFragment * f = EyerVideoFragment::CopyFragment(fragment);
        videoFragmentList.insertBack(f);

        return 0;
    }

    int EyerVideoLayer::SetFPS(int _fps)
    {
        fps = _fps;
        return 0;
    }

    int EyerVideoLayer::GetFPS()
    {
        return fps;
    }
}