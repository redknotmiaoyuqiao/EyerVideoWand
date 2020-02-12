add_executable(
    EyerVideoProcessTest
    Test.cpp

    EyerVPAudioResTest.hpp
    EyerVPAudioTrackTest.hpp
        EyerVPReadImageTest.h EyerVPVideoText.h)

include_directories (../)

target_link_libraries (EyerVideoProcessTest EyerVideoProcess)
target_link_libraries (EyerVideoProcessTest gtest)


target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerGL.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerType.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/freetype_install/lib/libfreetype.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/libpng_install/lib/libpng.a)
target_link_libraries (EyerVideoProcessTest dl)
target_link_libraries (EyerVideoProcessTest harfbuzz)
target_link_libraries (EyerVideoProcessTest X11)

INSTALL(
    TARGETS EyerVideoProcessTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )
