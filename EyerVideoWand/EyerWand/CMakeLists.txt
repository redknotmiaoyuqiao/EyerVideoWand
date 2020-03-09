include_directories (../)
include_directories (./)

add_library(
        EyerWand
        SHARED

        EyerWand.cpp
        EyerWandResource.cpp
        EyerWandVideoResource.cpp
        EyerWandAudioResource.cpp
        EyerWandBuilder.cpp
        EyerVideoTrack.cpp
        EyerVideoLayout.cpp

        EyerVideoPanel.cpp
        InterfaceC.cpp
        InterfaceCSharp.cpp
        EyerVideoDecoderLine.cpp
        EyerAudioTrack.cpp
        EyerAudioLayer.cpp
        EyerAudioFragment.cpp
        EyerWandDebug.cpp
        EyerVideoFragmentText.cpp
        EyerVideoFragmentVideo.cpp
        EyerVideoFragment.cpp
        )

target_link_libraries (EyerWand EyerAV)
target_link_libraries (EyerWand EyerCore)
target_link_libraries (EyerWand EyerGL)
target_link_libraries (EyerWand EyerYUV)
target_link_libraries (EyerWand EyerType)

ADD_DEFINITIONS(-D EYER_DEBUG)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerWand avformat)
    target_link_libraries (EyerWand avdevice)
    target_link_libraries (EyerWand avcodec)
    target_link_libraries (EyerWand avutil)
    target_link_libraries (EyerWand avfilter)
    target_link_libraries (EyerWand swresample)
    target_link_libraries (EyerWand swscale)

    target_link_libraries (EyerWand dl)
    target_link_libraries (EyerWand z)

    target_link_libraries (EyerWand x264)

    target_link_libraries (EyerWand glfw3)
    target_link_libraries (EyerWand X11)

    target_link_libraries (EyerWand libyuv.a)
    target_link_libraries (EyerWand libfreetype.a)
    target_link_libraries (EyerWand png)
    target_link_libraries (EyerWand harfbuzz)
    target_link_libraries (EyerWand bz2)
    target_link_libraries (EyerWand lzma)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (EyerWand avformat)
    target_link_libraries (EyerWand avdevice)
    target_link_libraries (EyerWand avcodec)
    target_link_libraries (EyerWand avutil)
    target_link_libraries (EyerWand avfilter)
    target_link_libraries (EyerWand swresample)
    target_link_libraries (EyerWand swscale)

    target_link_libraries (EyerWand libglfw3.a)

    target_link_libraries (EyerWand libEyerCore.a)
    target_link_libraries (EyerWand libyuv.a)
    target_link_libraries (EyerWand libfreetype.a)

    target_link_libraries (EyerWand z)
    target_link_libraries (EyerWand bz2)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
        TARGETS EyerWand
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

