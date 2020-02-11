#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerVideoProcess/EyerVideoProcess.hpp"


// #include "EyerVPAudioTrackTest.hpp"

// #include "EyerVPReadImageTest.h"
// #include "EyerVPAudioResTest.hpp"
#include "EyerVPVideoText.h"

int main(int argc,char **argv)
{
    EyerLog("This is Test\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
