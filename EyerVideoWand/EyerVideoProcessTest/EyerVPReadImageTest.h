//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H
#define EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

TEST(EyerVideoWand, Read_Image){
    Eyer::EyerVPVideoImage image;
    int ret = image.LoadFromImageFile("/home/redknot/Videos/timg.jpeg");
}

#endif //EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H
