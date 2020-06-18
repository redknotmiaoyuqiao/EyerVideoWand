#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerWand/EyerWand.hpp"

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1init
  (JNIEnv *, jclass)
{
    Eyer::WandTimeLineDrawEvent_Text * text = new Eyer::WandTimeLineDrawEvent_Text();
    return (jlong)text;
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1uninit
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * text = (Eyer::WandTimeLineDrawEvent_Text *)textP;

    if(text != nullptr){
        delete text;
        text = nullptr;
    }

    return 0;
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_start_x
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1start_1x
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerString text;
    float size = 10.0;
    Eyer::EyerVec2 start;
    Eyer::EyerString fontStyle;
    textDraw->GetText(text, size, start, fontStyle);

    return start.x();
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_start_y
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1start_1y
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerString text;
    float size = 10.0;
    Eyer::EyerVec2 start;
    Eyer::EyerString fontStyle;
    textDraw->GetText(text, size, start, fontStyle);

    return start.y();
}


/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_text
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1text
  (JNIEnv * env, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerString text;
    float size = 10.0;
    Eyer::EyerVec2 start;
    Eyer::EyerString fontStyle;
    textDraw->GetText(text, size, start, fontStyle);

    return env->NewStringUTF(text.str);
}


/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_size
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1size
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerString text;
    float size = 10.0;
    Eyer::EyerVec2 start;
    Eyer::EyerString fontStyle;
    textDraw->GetText(text, size, start, fontStyle);

    return size;
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_fontStyle
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1fontStyle
  (JNIEnv * env, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerString text;
    float size = 10.0;
    Eyer::EyerVec2 start;
    Eyer::EyerString fontStyle;
    textDraw->GetText(text, size, start, fontStyle);

    return env->NewStringUTF(fontStyle.str);
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_color_r
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1color_1r
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerVec4 color;
    textDraw->GetColor(color);

    return color.x();
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_color_g
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1color_1g
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerVec4 color;
    textDraw->GetColor(color);

    return color.y();
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_color_b
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1color_1b
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerVec4 color;
    textDraw->GetColor(color);

    return color.z();
}

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_view_draw_event_text_get_color_a
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1view_1draw_1event_1text_1get_1color_1a
  (JNIEnv *, jclass, jlong textP)
{
    Eyer::WandTimeLineDrawEvent_Text * textDraw = (Eyer::WandTimeLineDrawEvent_Text *)textP;
    Eyer::EyerVec4 color;
    textDraw->GetColor(color);

    return color.w();
}