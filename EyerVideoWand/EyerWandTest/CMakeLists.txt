include_directories (../)
include_directories (./)

add_executable(
        EyerWandTest
        Main.cpp
)

target_link_libraries (EyerWandTest gtest)
target_link_libraries (EyerWandTest EyerWand)

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

INSTALL(
        TARGETS EyerWandTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
