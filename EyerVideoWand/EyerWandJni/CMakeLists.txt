include_directories (../)
include_directories (./)

add_library(
    EyerWandJni
    SHARED
    EyerWandJniVersion.cpp
    EyerWandJniCrop.cpp
    EyerWandJniOGL.cpp
    EyerWandJniRenderTask.cpp
    EyerWandJniAvReader.cpp
    EyerWandJniContext.cpp
    EyerWandJniSnapshot.cpp
    EyerWandJniTimeline.cpp
    EyerWandJniDrawEventRect.cpp
    EyerWandJniDrawEventLine.cpp
    EyerWandJniDrawEventBitmap.cpp
    EyerWandJniLayer.cpp
    EyerWandJniDrawEventText.cpp
    EyerWandJniDrawEventBitmapSnapshot.cpp

    EyerWandJniVec.cpp
    JniUtil.cpp
)

target_link_libraries (EyerWandJni

    EyerWand
    EyerLib
    
    avformat
    avcodec
    avutil
    avfilter
    swresample
    swscale
    x264
    freetype

    yuv

    log
    z
    android
    OpenSLES
    GLESv3
    EGL
    jnigraphics
)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
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
    TARGETS EyerWandJni
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

