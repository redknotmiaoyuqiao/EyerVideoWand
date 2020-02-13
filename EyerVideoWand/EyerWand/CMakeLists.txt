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
)

target_link_libraries (EyerWand EyerAV)
target_link_libraries (EyerWand EyerCore)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerWand avformat)
    target_link_libraries (EyerWand avdevice)
    target_link_libraries (EyerWand avcodec)
    target_link_libraries (EyerWand avutil)
    target_link_libraries (EyerWand avfilter)
    target_link_libraries (EyerWand swresample)
    target_link_libraries (EyerWand swscale)

    target_link_libraries (EyerWand x264)

    target_link_libraries (EyerWand dl)
    target_link_libraries (EyerWand z)

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
        TARGETS EyerWand
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

