cmake_minimum_required(VERSION 3.13)
set (CMAKE_CXX_STANDARD 11)
project(waprer)

find_package(OpenCV REQUIRED)

SET(WAPRER_SRC "warper_go.cpp" "imgwarp_mls.cpp" "imgwarp_mls_similarity.cpp")

message("OpenCV version: " ${OpenCV_VERSION})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${WAPRER_SRC})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
