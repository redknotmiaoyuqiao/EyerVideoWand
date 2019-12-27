include_directories (../)
include_directories (./)

add_library(
    EyerVideoProcess

    EyerVideoProcess.hpp

    EyerVPAudioTrack.cpp
    EyerVPAudioRes.cpp
)

target_link_libraries (EyerVideoProcess bz2)
target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/EyerLib/lib/libEyerAV.a)
target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/EyerLib/lib/libEyerCore.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    include_directories (../3rdpart/linux/ffmpeg_install/include)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/linux/x264_install/lib/libx264.a)
    target_link_libraries (EyerVideoProcess dl)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    include_directories (../3rdpart/mac/ffmpeg_install/include)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerVideoProcess bz2)
    target_link_libraries (EyerVideoProcess z)
    target_link_libraries (EyerVideoProcess lzma)
    target_link_libraries (EyerVideoProcess iconv)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../3rdpart/mac/x264_install/lib/libx264.a)
    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
    TARGETS EyerVideoProcess
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

