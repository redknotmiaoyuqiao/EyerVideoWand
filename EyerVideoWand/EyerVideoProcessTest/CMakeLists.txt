add_executable(
    EyerVideoProcessTest
    Test.cpp

    EyerVPAudioResTest.hpp
    EyerVPAudioTrackTest.hpp
    EyerVPReadImageTest.h 
    EyerVPVideoText.h
)

include_directories (../)

target_link_libraries (EyerVideoProcessTest EyerVideoProcess)
target_link_libraries (EyerVideoProcessTest gtest)


target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerGL.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerType.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerYUV.a)

target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/freetype_install/lib/libfreetype.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/libpng_install/lib/libpng.a)
target_link_libraries (EyerVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/libyuv_install/lib/libyuv.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerVideoProcessTest dl)
    target_link_libraries (EyerVideoProcessTest z)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


INSTALL(
    TARGETS EyerVideoProcessTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )
