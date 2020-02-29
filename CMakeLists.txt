cmake_minimum_required(VERSION 3.0)

include_directories(/usr/include/SDL)
include_directories(/usr/include/freetype2)
file(GLOB_RECURSE sources **.cc)
add_executable(splexhd ${sources})

link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(
        splexhd
        SDL GL GLU png freetype ogg vorbis vorbisfile
)

add_custom_target(echo COMMAND echo)