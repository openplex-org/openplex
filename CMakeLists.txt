cmake_minimum_required(VERSION 3.0)

project(openplex)

include_directories(/usr/include/SDL)
include_directories(/usr/include/freetype2)
include_directories(/usr/include/opencv2/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE sources **.cc)
file(GLOB_RECURSE headers **.hh)
add_executable(openplex ${sources} ${headers})

link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(
        openplex
        opencv_imgproc
        opencv_imgcodecs
        opencv_core
        SDL GL GLU png freetype ogg vorbis vorbisfile
)
