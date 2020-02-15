include_directories (../)
include_directories (./)

add_library(
    EyerVideoProcess
    EyerVideoProcess.hpp
    EyerVPAudioTrack.cpp
    EyerVPResource.cpp
    EyerVPVideoTrack.cpp
    EyerVPVideoRes.cpp
    EyerVPVideoImage.cpp
)

target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerAV.a)
target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib/libEyerCore.a)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/include)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (EyerVideoProcess dl)
    target_link_libraries (EyerVideoProcess z)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (EyerVideoProcess z)
    target_link_libraries (EyerVideoProcess bz2)
    target_link_libraries (EyerVideoProcess ws2_32)
    target_link_libraries (EyerVideoProcess Secur32)
    target_link_libraries (EyerVideoProcess lzma)
    target_link_libraries (EyerVideoProcess iconv)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (EyerVideoProcess bz2)
    target_link_libraries (EyerVideoProcess z)
    target_link_libraries (EyerVideoProcess lzma)
    target_link_libraries (EyerVideoProcess iconv)


    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.dylib)
    target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)
    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
    TARGETS EyerVideoProcess
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

