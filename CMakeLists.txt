cmake_minimum_required(VERSION 3.12)
project(falsetone)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(falsetone
        src/main.cpp)

INCLUDE_DIRECTORIES(/usr/local/Cellar/opencv/3.4.3/include/)
LINK_DIRECTORIES(/usr/local/Cellar/opencv/3.4.3/libs/)

file(GLOB LIBRARIES "/usr/local/Cellar/opencv/3.4.3/*.dylib")
TARGET_LINK_LIBRARIES(falsetone ${LIBRARIES})