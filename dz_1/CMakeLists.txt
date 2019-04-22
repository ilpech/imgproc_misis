cmake_minimum_required(VERSION 3.13)
set (CMAKE_CXX_STANDARD 11)
project(hist)

find_package(OpenCV REQUIRED)

message("OpenCV version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} dz_1.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
