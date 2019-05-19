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
include_directories(${PROJECT_SOURCE_DIR}/tests)

set(CLIENT_SOURCE_FILES
        client/main.cpp
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        common/StageView.cpp
        client/ChellView.cpp)

set(SERVER_SOURCE_FILES
        server/main.cpp
        server/Stage.cpp
        server/Coordinate.cpp
        server/BrickBlock.cpp
        server/BrickBlock.cpp
        server/MetalBlock.cpp
        server/DiagonalMetalBlock.cpp
        server/EnergyTransmitter.cpp
        server/Rock.cpp
        server/EnergyBar.cpp
        server/Button.cpp
        server/Acid.cpp
        server/Chell.cpp
        server/Dynamic.cpp
        server/MoveRight.cpp
        server/MoveLeft.cpp
        server/Stop.cpp
        server/EnergyBall.cpp)

set(TEST_SOURCE_FILES
        tests/tests.cpp
        server/Stage.cpp
        server/Coordinate.cpp
        server/BrickBlock.cpp
        server/BrickBlock.cpp
        server/MetalBlock.cpp
        server/DiagonalMetalBlock.cpp
        server/EnergyTransmitter.cpp
        server/Rock.cpp
        server/EnergyBar.cpp
        server/Button.cpp
        server/Acid.cpp
        server/Chell.cpp
        server/Dynamic.cpp
        server/MoveRight.cpp
        server/MoveLeft.cpp
        server/Stop.cpp
        server/EnergyBall.cpp)

add_executable(Client ${CLIENT_SOURCE_FILES})
add_executable(Server ${SERVER_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES})

target_link_libraries(Client yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

add_subdirectory(Box2D)
target_compile_features(Server PUBLIC cxx_std_17)
target_compile_features(Test PUBLIC cxx_std_17)
target_link_libraries(Server TG::Box2D)
target_link_libraries(Test TG::Box2D)
