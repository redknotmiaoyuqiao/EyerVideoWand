#include "EyerWand.hpp"

namespace Eyer
{
    EyerAudioFragment::EyerAudioFragment()
    {

    }

    EyerAudioFragment::~EyerAudioFragment()
    {
        if(decoderLine != nullptr){
            delete decoderLine;
            decoderLine = nullptr;
        }
    }

    EyerAudioFragment::EyerAudioFragment(const EyerAudioFragment & fragment)
    {
        *this = fragment;
    }

    EyerAudioFragment & EyerAudioFragment::operator = (const EyerAudioFragment & fragment)
    {
        path = fragment.path;
        return *this;
    }

    int EyerAudioFragment::LoadAudioFile(EyerString _path)
    {
        path = _path;
        return 0;
    }

    int EyerAudioFragment::ReaderAVFrame(double ts, EyerAVFrame & frame)
    {
        if(decoderLine == nullptr){
            decoderLine = new EyerVideoDecoderLine(path, 0.0, EyerAVStreamType::STREAM_TYPE_AUDIO);
        }

        decoderLine->GetFrame(frame, ts);

        return 0;
    }
}