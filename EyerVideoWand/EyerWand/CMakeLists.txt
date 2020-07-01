include_directories (../)
include_directories (./)



IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
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
        EyerTransKey.cpp
        EyerVideoFragmentFrameSequential.cpp
        
        )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
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
        EyerTransKey.cpp
        EyerVideoFragmentFrameSequential.cpp
        
        )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    add_library(
        EyerWand
        # SHARED

        EyerWand.cpp
        EyerWandResource.cpp
        EyerWandVideoResource.cpp
        EyerWandAudioResource.cpp
        # EyerWandBuilder.cpp
        EyerWandContext.cpp
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
        EyerTransKey.cpp
        EyerVideoFragmentFrameSequential.cpp

        WandRenderTask/LayerRenderTask.cpp
        WandRenderTask/VideoTrackRenderTask.cpp

        UIView/WandTimeLine.cpp
        UIView/WandTimeLineDrawEvent.cpp
        UIView/WandTimeLineDrawEvent_Rect.cpp
        UIView/WandTimeLineDrawEvent_Line.cpp
        UIView/WandTimeLineDrawEvent_Bitmap.cpp
        UIView/WandTimeLineDrawEvent_Text.cpp
        UIView/WandTimeLineDrawEvent_BitmapSnapshot.cpp

        UIView/WandTimeLineDrawEventList.cpp
        )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    add_library(
        EyerWand
        # SHARED

        EyerWand.cpp
        EyerWandResource.cpp
        EyerWandVideoResource.cpp
        EyerWandAudioResource.cpp
        # EyerWandBuilder.cpp
        EyerWandContext.cpp
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
        EyerTransKey.cpp
        EyerVideoFragmentFrameSequential.cpp

        WandRenderTask/LayerRenderTask.cpp
        WandRenderTask/VideoTrackRenderTask.cpp

        UIView/WandTimeLine.cpp
        UIView/WandTimeLineDrawEvent.cpp
        UIView/WandTimeLineDrawEvent_Rect.cpp
        UIView/WandTimeLineDrawEvent_Line.cpp
        UIView/WandTimeLineDrawEvent_Bitmap.cpp
        UIView/WandTimeLineDrawEvent_Text.cpp
        UIView/WandTimeLineDrawEvent_BitmapSnapshot.cpp

        UIView/WandTimeLineDrawEventList.cpp
        
        )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")






ADD_DEFINITIONS(-D EYER_DEBUG)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerWand EyerCore)
    target_link_libraries (EyerWand EyerAV)
    target_link_libraries (EyerWand EyerGLWindow)
    target_link_libraries (EyerWand EyerGL)
    target_link_libraries (EyerWand EyerYUV)
    target_link_libraries (EyerWand EyerGPUDomino)
    target_link_libraries (EyerWand EyerGLAD)
    target_link_libraries (EyerWand EyerType)
    target_link_libraries (EyerWand EyerGLShader)
    target_link_libraries (EyerWand EyerImg)
    target_link_libraries (EyerWand EyerVideoTweenAnimation)

    target_link_libraries (EyerWand avformat)
    target_link_libraries (EyerWand avdevice)
    target_link_libraries (EyerWand avcodec)
    target_link_libraries (EyerWand avutil)
    target_link_libraries (EyerWand avfilter)
    target_link_libraries (EyerWand swresample)
    target_link_libraries (EyerWand swscale)

    target_link_libraries (EyerWand x264)

    target_link_libraries (EyerWand glfw3)
    target_link_libraries (EyerWand X11)

    target_link_libraries (EyerWand libyuv.a)
    target_link_libraries (EyerWand libfreetype.a)
    target_link_libraries (EyerWand png)
    target_link_libraries (EyerWand harfbuzz)
    target_link_libraries (EyerWand bz2)
    target_link_libraries (EyerWand lzma)

    target_link_libraries (EyerWand dl)
    target_link_libraries (EyerWand z.a)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (EyerWand EyerCore)
    target_link_libraries (EyerWand EyerAV)
    target_link_libraries (EyerWand EyerGLWindow)
    target_link_libraries (EyerWand EyerGL)
    target_link_libraries (EyerWand EyerYUV)
    target_link_libraries (EyerWand EyerGPUDomino)
    target_link_libraries (EyerWand EyerGLAD)
    target_link_libraries (EyerWand EyerType)
    target_link_libraries (EyerWand EyerGLShader)
    target_link_libraries (EyerWand EyerImg)

    target_link_libraries (EyerWand avformat)
    target_link_libraries (EyerWand avdevice)
    target_link_libraries (EyerWand avcodec)
    target_link_libraries (EyerWand avutil)
    target_link_libraries (EyerWand avfilter)
    target_link_libraries (EyerWand swresample)
    target_link_libraries (EyerWand swscale)

    target_link_libraries (EyerWand libglfw3.a)

    target_link_libraries (EyerWand libyuv.a)
    target_link_libraries (EyerWand libfreetype.a)

    target_link_libraries (EyerWand z)
    target_link_libraries (EyerWand bz2)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")

    target_link_libraries (EyerWand
        avformat
        avcodec
        avutil
        avfilter
        swresample
        swscale
        x264

        log
        z
        android
        OpenSLES
        GLESv3
        EGL
        jnigraphics
    )

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (EyerWand EyerCore)
    target_link_libraries (EyerWand EyerAV)
    target_link_libraries (EyerWand EyerGLWindow)
    target_link_libraries (EyerWand EyerGL)
    target_link_libraries (EyerWand EyerYUV)
    target_link_libraries (EyerWand EyerGPUDomino)
    target_link_libraries (EyerWand EyerGLAD)
    target_link_libraries (EyerWand EyerType)
    target_link_libraries (EyerWand EyerGLShader)
    target_link_libraries (EyerWand EyerImg)

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

    target_link_libraries (EyerWand libyuv.a)
    target_link_libraries (EyerWand libfreetype.a)
    target_link_libraries (EyerWand png)
    target_link_libraries (EyerWand bz2)
    target_link_libraries (EyerWand iconv)
    target_link_libraries (EyerWand lzma)

    macro(ADD_FRAMEWORK appname fwname) 
        find_library(FRAMEWORK_${fwname} NAMES ${fwname} PATHS ${CMAKE_OSX_SYSROOT}/System/Library PATH_SUFFIXES Frameworks NO_DEFAULT_PATH) 
        if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND) 
            MESSAGE(ERROR ": Framework ${fwname} not found") 
        else() 
            TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}.tbd") 
            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}") 
        endif() 
    endmacro(ADD_FRAMEWORK)

    add_framework(EyerWand AudioToolbox)
    add_framework(EyerWand IOKit)
    add_framework(EyerWand CoreGraphics)
    add_framework(EyerWand CoreMedia)
    add_framework(EyerWand Cocoa)
    add_framework(EyerWand VideoToolbox)
    add_framework(EyerWand AVFoundation)
    add_framework(EyerWand Security)
    add_framework(EyerWand CoreFoundation)
    add_framework(EyerWand CoreVideo)
    add_framework(EyerWand OpenGL)
    add_framework(EyerWand AppKit)
    add_framework(EyerWand CoreImage)
    add_framework(EyerWand VideoDecodeAcceleration)

    set(CMAKE_EXE_LINKER_FLAGS
        "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
        TARGETS EyerWand
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

