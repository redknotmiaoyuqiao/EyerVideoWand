#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"
#include "EyerWand/EyerWand.hpp"

JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_get_1version
(JNIEnv * env, jclass)
{
    return env->NewStringUTF(EYER_WAND_VERSION);
}
