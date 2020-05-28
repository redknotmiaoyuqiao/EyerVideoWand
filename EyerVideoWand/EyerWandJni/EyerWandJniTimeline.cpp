#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerWand/EyerWand.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLine * timeline = new Eyer::WandTimeLine();
    return (jlong)timeline;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1uninit
(JNIEnv *, jclass, jlong timelineP)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    delete timeline;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1draw
(JNIEnv *, jclass, jlong timelineP, jlong eventListP)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;

    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;
    timeline->Draw(*eventList);
    return 0;
}


JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEventList * eventList = new Eyer::WandTimeLineDrawEventList();
    return (jlong)eventList;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1uninit
(JNIEnv *, jclass, jlong eventListP)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;
    delete eventList;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1size
(JNIEnv *, jclass, jlong eventListP)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;
    return eventList->GetEventCount();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1event_1type
(JNIEnv *, jclass, jlong eventListP, jint eventIndex)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent * event = nullptr;

    eventList->GetEvent(event, eventIndex);

    if(event == nullptr){
        return (int)Eyer::EyerVideoFragmentType::VIDEO_FRAGMENT_UNKNOW;
    }

    return (int)event->GetType();
}


JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1event
(JNIEnv *, jclass, jlong eventListP, jlong eventP, jint eventIndex)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent * event = (Eyer::WandTimeLineDrawEvent *)eventP;

    // eventList->GetEvent(eventType, event);

    return 0;
}