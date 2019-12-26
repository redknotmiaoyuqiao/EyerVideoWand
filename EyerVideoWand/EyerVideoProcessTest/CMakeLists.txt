add_executable(
    EyerVideoProcessTest
    Test.cpp
    )

include_directories (../)

target_link_libraries (EyerVideoProcessTest EyerVideoProcess)

INSTALL(
    TARGETS EyerVideoProcessTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )