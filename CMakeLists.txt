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
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        common/StageView.cpp
        client/ChellView.cpp)

#EDITOR CONFIG

set(EDITOR_SOURCE_FILES
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        editor/Stage.cpp
        editor/Menu.cpp
        editor/Editor.cpp
        editor/MenuButton.cpp
        editor/RockButton.cpp
        editor/Event.cpp
        editor/StageController.cpp
        editor/StageView.cpp
        editor/StaticObject.cpp
        editor/Block.cpp
        editor/Button.cpp
        editor/Rock.cpp
        editor/Chell.cpp
        editor/AnimatedObject.cpp
        editor/Object.cpp
        editor/Gate.cpp
        editor/MouseButton.cpp
        )



set(SERVER_SOURCE_FILES
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
        server/EnergyBall.cpp
        server/Entity.cpp
        server/MoveUp.cpp
        server/MoveDown.cpp)

set(TEST_SOURCE_FILES
        tests/tests.cpp)

add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES} ${SERVER_SOURCE_FILES})
add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})
add_executable(Editor editor/main.cpp ${EDITOR_SOURCE_FILES})
add_subdirectory(Box2D)
target_link_libraries(Client yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} TG::Box2D)
target_link_libraries(Editor yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
target_compile_features(Server PUBLIC cxx_std_17)
target_compile_features(Test PUBLIC cxx_std_17)
target_link_libraries(Server TG::Box2D)
target_link_libraries(Test TG::Box2D)
