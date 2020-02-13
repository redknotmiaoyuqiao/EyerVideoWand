include_directories (../)
include_directories (./)

add_executable(
        EyerWandTest
        Main.cpp
)

target_link_libraries (EyerWandTest gtest)
target_link_libraries (EyerWandTest EyerWand)

INSTALL(
        TARGETS EyerWandTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
