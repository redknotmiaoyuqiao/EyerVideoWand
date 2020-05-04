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
)

target_link_libraries (EyerWandJni EyerThread)
target_link_libraries (EyerWandJni EyerGLContext)
target_link_libraries (EyerWandJni EyerCrop)
target_link_libraries (EyerWandJni EyerGLShader)
target_link_libraries (EyerWandJni EyerGLRenderTask)
target_link_libraries (EyerWandJni EyerGLCustomComponent)
target_link_libraries (EyerWandJni EyerCore)
target_link_libraries (EyerWandJni EyerGL)
target_link_libraries (EyerWandJni EyerCore)
target_link_libraries (EyerWandJni EyerGLCustomComponent)
target_link_libraries (EyerWandJni EyerGLShader)
target_link_libraries (EyerWandJni EyerAV)

target_link_libraries (EyerWandJni EyerWand)

target_link_libraries (EyerWandJni avformat)
target_link_libraries (EyerWandJni avcodec)
target_link_libraries (EyerWandJni avutil)
target_link_libraries (EyerWandJni avfilter)
target_link_libraries (EyerWandJni swresample)
target_link_libraries (EyerWandJni swscale)
target_link_libraries (EyerWandJni x264)

target_link_libraries (EyerWandJni z)
target_link_libraries (EyerWandJni android)
target_link_libraries (EyerWandJni OpenSLES)
target_link_libraries (EyerWandJni GLESv3)
target_link_libraries (EyerWandJni EGL)
target_link_libraries (EyerWandJni log)
target_link_libraries (EyerWandJni jnigraphics)

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

