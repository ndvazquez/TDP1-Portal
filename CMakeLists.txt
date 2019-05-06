cmake_minimum_required(VERSION 3.14)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/client)

set(CLIENT_SOURCE_FILES
        client/main.cpp
        client/Window.cpp
        client/Sprite.cpp)

add_executable(Portal ${CLIENT_SOURCE_FILES})
target_link_libraries(Portal ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
