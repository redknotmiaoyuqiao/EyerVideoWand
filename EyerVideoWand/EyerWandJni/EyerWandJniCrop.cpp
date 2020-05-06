#include "com_eyer_eyer_wand_editor_lib_EyerWandNative.h"

#include "EyerCrop/EyerCrop.hpp"
#include "EyerWand/EyerWandContext.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1init
(JNIEnv *, jclass, jint viewW, jint viewH, jint imageW, jint imageH)
{
    Eyer::EyerAVCrop * crop = new Eyer::EyerAVCrop(viewW, viewH, imageW, imageH);
    return (jlong)crop;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1uninit
(JNIEnv *, jclass, jlong crop_p)
{
    Eyer::EyerAVCrop * crop = (Eyer::EyerAVCrop *)crop_p;
    delete crop;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1get_1crop_1width
(JNIEnv *, jclass, jlong crop_p)
{
    Eyer::EyerAVCrop * crop = (Eyer::EyerAVCrop *)crop_p;
    return crop->GetCropW();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1get_1crop_1height
(JNIEnv *, jclass, jlong crop_p)
{
    Eyer::EyerAVCrop * crop = (Eyer::EyerAVCrop *)crop_p;
    return crop->GetCropH();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1crop
(JNIEnv *, jclass, jlong crop_p, jint type)
{
    Eyer::EyerAVCrop * crop = (Eyer::EyerAVCrop *)crop_p;
    return crop->Crop((Eyer::EyerAVCropType)type);
}