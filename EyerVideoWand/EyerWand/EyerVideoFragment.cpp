#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragment * EyerVideoFragment::CopyFragment(const EyerVideoFragment * fragment)
    {
        EyerVideoFragment * f = nullptr;
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            f = new EyerVideoFragmentVideo(*(EyerVideoFragmentVideo *)fragment);
        }
        if(fragment->GetType() == EyerVideoFragmentType::VIDEO_FRAGMENT_TEXT){
            f = new EyerVideoFragmentText();
        }
        return f;
    }


    EyerVideoFragment::~EyerVideoFragment()
    {
        //
        EyerLinkedEle<Eyer::EyerTransKey *> * currentEle = transKeyList.head;
        for(int i=0; i<transKeyList.getLength()-1; i++){
            EyerLinkedEle<Eyer::EyerTransKey *> * temp = currentEle->next;
            while (temp != nullptr){
                if(temp->data->t < currentEle->data->t){
                    Eyer::EyerTransKey * data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if(currentEle->next != nullptr){
                currentEle = currentEle->next;
            }
        }

        Eyer::EyerTransKey * firstdata = nullptr;
        Eyer::EyerTransKey * lastdata = nullptr;
        transKeyList.find(0, firstdata);
        transKeyList.find(transKeyList.getLength()-1, lastdata);

        if(t < firstdata->t){
            x = firstdata->x;
            y = firstdata->y;
            z = firstdata->z;
            return 0;
        }else if(t > lastdata->t){
            x = lastdata->x;
            y = lastdata->y;
            z = lastdata->z;
            return 0;
        }

        for(int i=0; i<transKeyList.getLength()-1; i++){
            transKeyList.find(i, firstdata);
            transKeyList.find(i+1, lastdata);

            if(t >= firstdata->t && t < lastdata->t){
                double tPart = (t - firstdata->t)/(lastdata->t - firstdata->t);
                x = tPart * (lastdata->x - firstdata->x) + firstdata->x;
                y = tPart * (lastdata->y - firstdata->y) + firstdata->y;
                z = tPart * (lastdata->z - firstdata->z) + firstdata->z;
                return 0;
            }
        }
        return 0;
    }
}