cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories ( ${OpenCV_INCLUDE_DIRS} )

add_library(aschelper aschelper.cpp)

add_executable(ascimg2 ascimgv2.cpp)
target_link_libraries(ascimg2 aschelper)
target_link_libraries(ascimg2  ${OpenCV_LIBS} )
