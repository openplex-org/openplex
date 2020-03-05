cmake_minimum_required(VERSION 3.0)

project(openplex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
include_directories(/usr/include/SDL)
include_directories(/usr/include/freetype2)

if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
    add_definitions(-D__MACOSX__)
    include_directories(/usr/local/include)
    include_directories(/usr/local/include/SDL)
    include_directories(/usr/local/include/freetype2)
    include_directories(/usr/local/include/libpng16)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/Headers)
    link_directories(/usr/local/lib/)
    link_directories(/System/Library/Frameworks/OpenGL.framework/Libraries)
endif()
#include_directories(/usr/include/opencv2/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE sources **.cc)
file(GLOB_RECURSE headers **.hh)
add_executable(openplex ${sources} ${headers} src/common/openplex-gl.h)

link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(
        openplex
#        opencv_imgproc
#        opencv_imgcodecs
#        opencv_core
        SDLmain
        SDL
        GL GLU png freetype ogg vorbis vorbisfile
)
