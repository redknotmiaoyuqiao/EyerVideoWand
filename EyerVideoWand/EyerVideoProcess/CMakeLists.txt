include_directories (../)
include_directories (./)

add_library(
    EyerVideoProcess

    EyerVideoProcess.hpp

    EyerVPAudioTrack.cpp
    EyerVPAudioRes.cpp
)

target_link_libraries (EyerVideoProcess bz2)
target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/3rdpart/EyerLib/lib/libEyerAV.a)
target_link_libraries (EyerVideoProcess ${CMAKE_SOURCE_DIR}/3rdpart/EyerLib/lib/libEyerCore.a)

INSTALL(
    TARGETS EyerVideoProcess
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

