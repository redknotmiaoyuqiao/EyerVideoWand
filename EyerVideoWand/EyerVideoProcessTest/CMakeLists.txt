add_executable(
    EyerVideoProcessTest
    Test.cpp

    EyerVPAudioResTest.hpp
    EyerVPAudioTrackTest.hpp
        EyerVPReadImageTest.h)

include_directories (../)

target_link_libraries (EyerVideoProcessTest EyerVideoProcess)
target_link_libraries (EyerVideoProcessTest gtest)

INSTALL(
    TARGETS EyerVideoProcessTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )
