#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(concentration)

option(set_clang "set clang as default compiler" 0)
option(cros_compile "cros compile" 0)

if(set_clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    message(STATUS "Use option set_clang")
endif()
if(cros_compile)
    set(PROJECT_NAME ${PROJECT_NAME}.exe)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++-posix)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    message(STATUS "Use option cros_compile")
endif()

message(STATUS "Project      " ${PROJECT_NAME})
message(STATUS "c compiler   " ${CMAKE_C_COMPILER})
message(STATUS "cxx compiler " ${CMAKE_CXX_COMPILER})

set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

include_directories("./include")

set(MAIN_SRC sources/main.cpp)
set(CNC_LIB "cnc")
file(GLOB CNC_SRC "sources/cnc/*.cpp" "include/*.hpp")
set(IMAGES_SRC images.qrc)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${IMAGES_SRC})

add_library(${CNC_LIB} SHARED ${CNC_SRC})
target_link_libraries(${CNC_LIB} Qt5::Widgets)

target_link_libraries(${PROJECT_NAME} ${CNC_LIB} Qt5::Widgets)
