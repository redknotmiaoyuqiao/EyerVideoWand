PROJECT(EYE_Video_Wand)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/)

include_directories (googletest/googletest/include)
include_directories (${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/include)

link_directories (${CMAKE_SOURCE_DIR}/../../Lib/EyerLib/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/libyuv_install/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/freetype_install/lib)
link_directories (${CMAKE_SOURCE_DIR}/../../Lib/libpng_install/lib)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wl,-Bsymbolic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-Bsymbolic")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wl,-Bsymbolic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-Bsymbolic")
    
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    set(CMAKE_EXE_LINKER_FLAGS
        "-framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


# ADD_SUBDIRECTORY(EyerVideoProcessTest)
# ADD_SUBDIRECTORY(EyerVideoProcess)
ADD_SUBDIRECTORY(EyerWandTest)
ADD_SUBDIRECTORY(EyerWand)
ADD_SUBDIRECTORY(EyerWandTest_C)

ADD_SUBDIRECTORY(googletest)
