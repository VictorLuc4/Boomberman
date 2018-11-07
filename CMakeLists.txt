cmake_minimum_required(VERSION 3.0)
set(NAME bomberman)
project(${NAME})
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

## Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
if (WIN32)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif (WIN32)

## Includes and lib directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
if (UNIX)
    include_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
    link_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux)
endif (UNIX)

if (WIN32)
    include_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
	link_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows)
endif (WIN32)

## Compilation
set(SRC
	src/Block.cpp
	src/Core.cpp
	src/Graphical.cpp
	src/IA.cpp
	src/Map.cpp
	src/Personnage.cpp
	src/Player.cpp
	src/GameScene.cpp
	src/MyEventReceiver.cpp
	src/Config.cpp
	src/GUI/MenuGui.cpp
	src/GUI/MenuScene.cpp
	src/GUI/MainMenuGui.cpp
	src/GUI/MenuManager.cpp
	src/GUI/OptionMenuGui.cpp
	src/GUI/NewGameMenuGui.cpp
	src/GUI/InfoMenu.cpp
	src/GUI/HudGui.cpp
	src/GUI/VictoryGui.cpp
	src/main.cpp
)

set(INCLUDES
	include/Block.hpp
	include/Core.hpp
	include/Graphical.hpp
	include/GameScene.hpp
	include/IA.hpp
	include/Map.hpp
	include/Personnage.hpp
	include/Player.hpp
	include/MenuScene.hpp
	include/MenuGui.hpp
	include/MenuManager.hpp
	include/MainMenuGui.hpp
	include/OptionMenuGui.hpp
	include/NewGameMenuGui.hpp
	include/InfoMenu.hpp
	include/MyEventReceiver.hpp
	include/HudGui.hpp
	include/VictoryGui.hpp
	include/Config.hpp
)

add_executable(bomberman ${SRC} ${INCLUDES})

## Lib linking
if (UNIX)
	execute_process(COMMAND bash -c "sudo cp -r -v ../lib/linux/libIrrKlang.so /usr/lib/")
	target_link_libraries(${NAME} Irrlicht GL Xxf86vm Xext X11 Xcursor)
	target_link_libraries(${NAME} Irrlicht IrrKlang GL Xxf86vm Xext X11 Xcursor)
endif(UNIX)
if (WIN32)
	target_link_libraries(${NAME} Irrlicht.dll)
	target_link_libraries(${NAME} irrKlang.dll)
endif(WIN32)
