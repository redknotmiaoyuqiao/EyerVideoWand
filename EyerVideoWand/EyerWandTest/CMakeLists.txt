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

INSTALL(
        TARGETS EyerWandTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
