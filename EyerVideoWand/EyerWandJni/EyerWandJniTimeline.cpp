#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerWand/EyerWand.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1init
(JNIEnv *, jclass)
{
    Eyer::WandTimeLine * timeline = new Eyer::WandTimeLine();
    return (jlong)timeline;
}

/**
 * 释放 TimeLine
 */ 
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1uninit
(JNIEnv *, jclass, jlong timelineP)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    if(timeline != nullptr){
        delete timeline;
        timeline = nullptr;
    }
    
    return 0;
}


JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1set_1wand_1ctx
(JNIEnv *, jclass, jlong timelineP, jlong ctx)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    Eyer::EyerWandContext * wandCtx = (Eyer::EyerWandContext *)ctx;

    timeline->SetWandCtx(wandCtx);

    return 0;
}


/**
 * 设置画布宽高
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1set_1wh
(JNIEnv *, jclass, jlong timelineP, jfloat w, jfloat h)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    timeline->SetWH(w, h);
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
        return (int)Eyer::WandTimeLineDrawEventType::UNKNOW;
    }

    return (int)event->GetType();
}



JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1rect_1event
(JNIEnv *, jclass, jlong eventListP, jlong rectP, jint index)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent_Rect * rect = (Eyer::WandTimeLineDrawEvent_Rect *)rectP;

    // 验证类型是否正确
    Eyer::WandTimeLineDrawEvent * tempEvent = nullptr;
    eventList->GetEvent(tempEvent, index);

    if(tempEvent == nullptr){
        return -1;
    }

    *rect = *((Eyer::WandTimeLineDrawEvent_Rect *)tempEvent);

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1line_1event
(JNIEnv *, jclass, jlong eventListP, jlong lineP, jint index)
{

    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent_Line * line = (Eyer::WandTimeLineDrawEvent_Line *)lineP;

    // 验证类型是否正确
    Eyer::WandTimeLineDrawEvent * tempEvent = nullptr;
    eventList->GetEvent(tempEvent, index);

    if(tempEvent == nullptr){
        return -1;
    }

    *line = *((Eyer::WandTimeLineDrawEvent_Line *)tempEvent);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1text_1event
(JNIEnv *, jclass, jlong eventListP, jlong textP, jint index)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;
    Eyer::WandTimeLineDrawEvent_Text * text = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    // 验证类型是否正确
    Eyer::WandTimeLineDrawEvent * tempEvent = nullptr;
    eventList->GetEvent(tempEvent, index);

    if(tempEvent == nullptr){
        return -1;
    }

    *text = *((Eyer::WandTimeLineDrawEvent_Text *)tempEvent);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1bitmap_1event
(JNIEnv *, jclass, jlong eventListP, jlong bitmapP, jint index)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent_Bitmap * bitmap = (Eyer::WandTimeLineDrawEvent_Bitmap *)bitmapP;

    // 验证类型是否正确
    Eyer::WandTimeLineDrawEvent * tempEvent = nullptr;
    eventList->GetEvent(tempEvent, index);

    if(tempEvent == nullptr){
        return -1;
    }

    *bitmap = *((Eyer::WandTimeLineDrawEvent_Bitmap *)tempEvent);

    return 0;
}


JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1list_1get_1bitmap_1snapshot_1event
(JNIEnv *, jclass, jlong eventListP, jlong bitmapSnapshotP, jint index)
{
    Eyer::WandTimeLineDrawEventList * eventList = (Eyer::WandTimeLineDrawEventList *)eventListP;

    Eyer::WandTimeLineDrawEvent_BitmapSnapshot * bitmapSnapshot = (Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)bitmapSnapshotP;

    // 验证类型是否正确

    // 验证类型是否正确
    Eyer::WandTimeLineDrawEvent * tempEvent = nullptr;
    eventList->GetEvent(tempEvent, index);

    if(tempEvent == nullptr){
        return -1;
    }

    *bitmapSnapshot = *((Eyer::WandTimeLineDrawEvent_BitmapSnapshot *)tempEvent);

    return 0;
}









JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1on_1touch_1up
(JNIEnv *, jclass, jlong timelineP, jfloat x, jfloat y)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    return timeline->OnTouchUp(x, y);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1on_1touch_1down
(JNIEnv *, jclass, jlong timelineP, jfloat x, jfloat y)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    return timeline->OnTouchDown(x, y);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1timeline_1on_1touch_1move
(JNIEnv *, jclass, jlong timelineP, jfloat x, jfloat y)
{
    Eyer::WandTimeLine * timeline = (Eyer::WandTimeLine *)timelineP;
    return timeline->OnTouchMove(x, y);
}