cmake_minimum_required(VERSION 3.14)
project(Portal)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/tests)

set(CLIENT_SOURCE_FILES
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        client/StageView.cpp
        client/ChellView.cpp
        client/EnergyBallView.cpp
        client/AcidView.cpp
        client/BulletView.cpp
        client/View.cpp
        client/RockView.cpp
        client/ButtonView.cpp
        client/PortalView.cpp
        client/Camera.cpp
        client/AudioSystem.cpp
        client/SoundCodeQueue.cpp
        client/ViewFactory.cpp
        client/ViewManager.cpp
        client/CakeView.cpp
        common/UserEvent.cpp
        client/UserEventHandler.cpp
        client/UserEventQueue.cpp)

#EDITOR CONFIG

set(EDITOR_SOURCE_FILES
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        editor/stage/Stage.cpp
        editor/Menu.cpp
        editor/Editor.cpp
        editor/MenuButton.cpp
        editor/Event.cpp
        editor/stage/Controller.cpp
        editor/stage/View.cpp
        editor/stage/object/StaticObject.cpp
        editor/stage/object/Block.cpp
        editor/stage/object/Button.cpp
        editor/stage/object/Rock.cpp
        editor/stage/object/Chell.cpp
        editor/stage/object/AnimatedObject.cpp
        editor/stage/object/Object.cpp
        editor/stage/object/Gate.cpp
        editor/stage/object/Cake.cpp
        editor/stage/object/Acid.cpp
        editor/stage/object/DiagonalBlockUp.cpp
        editor/MouseButton.cpp


        ffmpeg/CodecContext.cpp
        ffmpeg/FormatOutput.cpp
        ffmpeg/FormatContext.cpp
        ffmpeg/Frame.cpp
        ffmpeg/Output.cpp
        ffmpeg/Packet.cpp
        ffmpeg/SwsContext.cpp
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
        server/configuration.cpp
        server/Floor.cpp
        server/BlueShot.cpp
        server/OrangeShot.cpp
        server/Shot.cpp
        server/Portal.cpp
        server/EnergyTransmitterUp.cpp
        server/EnergyTransmitterDown.cpp
        server/EnergyTransmitterLeft.cpp
        server/EnergyTransmitterRight.cpp
        server/Gate.cpp
        server/Cake.cpp
        server/BluePortal.cpp
        server/OrangePortal.cpp)

set(TEST_SOURCE_FILES
        tests/tests.cpp)

add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES} ${SERVER_SOURCE_FILES})
add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})
add_executable(Editor editor/main.cpp ${EDITOR_SOURCE_FILES})
add_subdirectory(Box2D)
target_link_libraries(Client yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} TG::Box2D)
target_link_libraries(Editor yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}  avformat avcodec avutil swscale)
target_compile_features(Server PUBLIC cxx_std_17)
target_compile_features(Test PUBLIC cxx_std_17)
target_link_libraries(Server TG::Box2D)
target_link_libraries(Test TG::Box2D)
