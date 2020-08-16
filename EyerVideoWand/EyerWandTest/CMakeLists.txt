include_directories (../)
include_directories (./)

add_executable(
        EyerWandTest
        Main.cpp
)

target_link_libraries (EyerWandTest gtest)
target_link_libraries (EyerWandTest EyerWand)
target_link_libraries (EyerWandTest EyerLib)

target_link_libraries (EyerWandTest avcodec)
target_link_libraries (EyerWandTest avformat)
target_link_libraries (EyerWandTest avdevice)
target_link_libraries (EyerWandTest avfilter)
target_link_libraries (EyerWandTest swscale)
target_link_libraries (EyerWandTest avutil)

target_link_libraries (EyerWandTest freetype)
target_link_libraries (EyerWandTest glfw3)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/Manjari-Bold.otf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/M_1280_720.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/xiao_xiao_yuan_pin_ying.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/han_yi_xing_kai_jian.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/mulan.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/wei.mp3
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/wei.aac
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )


file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/1.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )


file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/2.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/3.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )


file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/4.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/5.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/6.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/earl
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )


INSTALL(
        TARGETS EyerWandTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
