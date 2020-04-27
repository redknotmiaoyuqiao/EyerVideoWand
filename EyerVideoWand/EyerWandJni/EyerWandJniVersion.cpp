#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_getVersion
(JNIEnv * env, jclass)
{
    return env->NewStringUTF("EyerWand 1.0.0");
}
