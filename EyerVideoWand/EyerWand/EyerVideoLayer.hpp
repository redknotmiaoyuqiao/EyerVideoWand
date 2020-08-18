#ifndef EYE_VIDEO_WAND_EYERVIDEOLAYER_HPP
#define EYE_VIDEO_WAND_EYERVIDEOLAYER_HPP

#include "EyerVideoFragment.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    class EyerVideoLayer {
    public:
        EyerVideoLayer();
        ~EyerVideoLayer();

        EyerVideoLayer(const EyerVideoLayer & videoLayer);
        const EyerVideoLayer & operator = (const EyerVideoLayer &videoLayer);

        int AddVideoFragment(const Eyer::EyerVideoFragment * fragment);

        int SetFPS(int fps);
        int GetFPS();

    private:
        int fps = 30;

        EyerLinkedList<EyerVideoFragment *> videoFragmentList;
    };
}


#endif //EYE_VIDEO_WAND_EYERVIDEOLAYER_HPP
