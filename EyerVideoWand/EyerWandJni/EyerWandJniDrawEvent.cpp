#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerWand/EyerWandContext.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent * event = nullptr;
    return (jlong)event;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1uninit
(JNIEnv *, jclass, jlong eventP)
{
    Eyer::WandTimeLineDrawEvent * event = (Eyer::WandTimeLineDrawEvent *)eventP;
    if(event != nullptr){
        delete event;
    }
    
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1get_1type
(JNIEnv *, jclass, jlong eventP)
{
    Eyer::WandTimeLineDrawEvent * event = (Eyer::WandTimeLineDrawEvent *)eventP;

    if(event != nullptr){
        return (int)event->GetType();
    }

    return (int)Eyer::EyerVideoFragmentType::VIDEO_FRAGMENT_UNKNOW;
}