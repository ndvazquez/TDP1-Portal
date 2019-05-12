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
include_directories(${PROJECT_SOURCE_DIR}/server)

set(CLIENT_SOURCE_FILES
        client/main.cpp
        client/Window.cpp
        client/Sprite.cpp
        client/AnimatedSprite.cpp
        client/SDLSession.cpp)

set(SERVER_SOURCE_FILES
        server/main.cpp server/main.cpp server/Stage.cpp server/Stage.h)

add_executable(Client ${CLIENT_SOURCE_FILES})
add_executable(Server ${SERVER_SOURCE_FILES} server/main.cpp)

target_link_libraries(Client ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

add_subdirectory(Box2D)
target_compile_features(Server PUBLIC cxx_std_17)
target_link_libraries(Server TG::Box2D)
