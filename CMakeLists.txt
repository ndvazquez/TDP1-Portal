cmake_minimum_required(VERSION 3.14)
project(Portal)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
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
        client/views/StageView.cpp
        client/views/ChellView.cpp
        client/views/EnergyBallView.cpp
        client/views/AcidView.cpp
        client/views/BulletView.cpp
        client/views/View.cpp
        client/views/RockView.cpp
        client/views/ButtonView.cpp
        client/views/BluePortalView.cpp
        client/views/Camera.cpp
        client/audio/AudioSystem.cpp
        client/audio/SoundCodeQueue.cpp
        client/views/ViewFactory.cpp
        client/views/ViewManager.cpp
        client/views/CakeView.cpp
        common/UserEvent.cpp
        client/communication-support/UserEventHandler.cpp
        common/UserEventQueue.cpp
        client/views/OrangePortalView.cpp
        client/views/GateView.cpp
        common/Thread.cpp
        common/Socket.cpp
        client/communication-support/EventSender.cpp
        client/communication-support/StageStatusReceiver.cpp
        common/StageStatusQueue.cpp
        )

#EDITOR CONFIG

set(EDITOR_SOURCE_FILES
        common/Window.cpp
        common/Sprite.cpp
        common/AnimatedSprite.cpp
        common/SDLSession.cpp
        common/Text.cpp


        editor/Menu.cpp
        editor/Editor.cpp
        editor/MenuButton.cpp
        editor/Event.cpp
        editor/MouseButton.cpp


        editor/stage/Controller.cpp
        editor/stage/View.cpp
        editor/stage/Stage.cpp
        editor/stage/LogicGates.cpp
        editor/stage/YamlManager.cpp


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
        editor/stage/object/Receptor.cpp
        editor/stage/object/EnergyBar.cpp
        editor/stage/object/VerticalEnergyBar.cpp
        editor/stage/object/HorizontalEnergyBar.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockUp.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockRightUp.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockLeftUp.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockDown.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockLeftDown.cpp
        editor/stage/object/diagonalBlocks/DiagonalBlockRightDown.cpp

        editor/stage/object/WithOutGravitySentinel.cpp
        editor/stage/object/GravitySentinel.cpp



        #ffmpeg/CodecContext.cpp
        #ffmpeg/FormatOutput.cpp
        #ffmpeg/FormatContext.cpp
        #ffmpeg/Frame.cpp
        #ffmpeg/Output.cpp
        #ffmpeg/Packet.cpp
        #ffmpeg/SwsContext.cpp
        #ffmpeg/BlockingQueue.cpp
        #ffmpeg/Consumer.cpp
        #ffmpeg/Thread.cpp
        )

set(SERVER_SOURCE_FILES
        server/stage-support/Stage.cpp
        server/stage-support/Coordinate.cpp
        server/entities/RockBlock.cpp
        server/entities/RockBlock.cpp
        server/entities/MetalBlock.cpp
        server/entities/DiagonalMetalBlock.cpp
        server/entities/EnergyTransmitter.cpp
        server/entities/Rock.cpp
        server/entities/EnergyBar.cpp
        server/entities/Button.cpp
        server/entities/Acid.cpp
        server/entities/Chell.cpp
        server/movements/Dynamic.cpp
        server/movements/MoveRight.cpp
        server/movements/MoveLeft.cpp
        server/movements/Stop.cpp
        server/entities/EnergyBall.cpp
        server/entities/Entity.cpp
        server/configuration.cpp
        server/entities/Floor.cpp
        server/entities/BlueShot.cpp
        server/entities/OrangeShot.cpp
        server/entities/Shot.cpp
        server/entities/Portal.cpp
        server/entities/EnergyTransmitterUp.cpp
        server/entities/EnergyTransmitterDown.cpp
        server/entities/EnergyTransmitterLeft.cpp
        server/entities/EnergyTransmitterRight.cpp
        server/entities/Gate.cpp
        server/entities/Cake.cpp
        server/stage-support/StageManager.cpp
        common/Thread.cpp
        common/Socket.cpp
        common/StageStatusQueue.cpp
        common/UserEventQueue.cpp
        common/UserEvent.cpp
        server/communication-support/ClientHandler.cpp
        server/communication-support/ClientSender.cpp
        server/communication-support/ClientReceiver.cpp
        server/entities/EnergyReceptor.cpp
        server/entities/EnergyReceptorUp.cpp
        server/entities/EnergyReceptorDown.cpp
        server/entities/EnergyReceptorLeft.cpp
        server/entities/EnergyReceptorRight.cpp
        server/stage-support/PhysicsWorld.cpp
        server/entities/ItemActivable.cpp
        server/portal-support/PortalManager.cpp
        server/stage-support/YamlParser.cpp
        server/portal-support/PortalHolder.cpp
        server/communication-support/RoomManager.cpp
        server/communication-support/RoomAcceptor.cpp
        server/communication-support/RoomWorker.cpp)

set(TEST_SOURCE_FILES
        tests/tests.cpp)

add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES})
add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})
add_executable(Editor editor/main.cpp ${EDITOR_SOURCE_FILES})
add_subdirectory(Box2D)
target_link_libraries(Client yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} pthread)
target_link_libraries(Editor yaml-cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES} -lSDL2_ttf)# avformat avcodec avutil swscale)
target_link_libraries(Server yaml-cpp)
target_compile_features(Server PUBLIC cxx_std_17)
target_compile_features(Test PUBLIC cxx_std_17)
target_link_libraries(Server TG::Box2D pthread)
target_link_libraries(Test TG::Box2D)
