#include <gtest/gtest.h>

#include "EyerVideoProcess/EyerVideoProcess.hpp"

#include "EyerVPAudioResTest.hpp"

#include "EyerVPAudioTrackTest.hpp"

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
