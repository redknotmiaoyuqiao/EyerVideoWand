include_directories (../)
include_directories (./)

add_executable(
        EyerWandTest_C
        Main.cpp
)

target_link_libraries (EyerWandTest_C gtest)
target_link_libraries (EyerWandTest_C EyerWand)

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

INSTALL(
        TARGETS EyerWandTest_C
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
