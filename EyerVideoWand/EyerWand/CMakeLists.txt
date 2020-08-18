include_directories (../)
include_directories (./)


add_library(
        EyerWand
        # SHARED

        EyerWandContext.cpp

        EyerWandDebug.cpp
        EyerVideoFragmentVideo.cpp
        EyerVideoFragment.cpp

        UIView/WandTimeLine.cpp
        UIView/WandTimeLineDrawEvent.cpp
        UIView/WandTimeLineDrawEvent_Rect.cpp
        UIView/WandTimeLineDrawEvent_Line.cpp
        UIView/WandTimeLineDrawEvent_Bitmap.cpp
        UIView/WandTimeLineDrawEvent_Text.cpp
        UIView/WandTimeLineDrawEvent_BitmapSnapshot.cpp

        UIView/WandTimeLineDrawEventList.cpp
        EyerVideoLayer.cpp EyerVideoLayer.hpp EyerVideoFragment.hpp)


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



INSTALL(FILES EyerWand.hpp DESTINATION include/EyerWand)
INSTALL(FILES EyerWandAV.hpp DESTINATION include/EyerWand)
INSTALL(FILES EyerWandContext.hpp DESTINATION include/EyerWand)
INSTALL(FILES WandRenderTask/WandRenderTask.hpp DESTINATION include/EyerWand/WandRenderTask/)
INSTALL(FILES UIView/WandUIView.hpp DESTINATION include/EyerWand/UIView/)

INSTALL(
        TARGETS EyerWand
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

