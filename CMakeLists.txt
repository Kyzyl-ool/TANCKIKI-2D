cmake_minimum_required(VERSION 3.13)
project(TANCHIKI)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp sources/GameObject.cpp sources/GameObject.hpp sources/ObjectManager.cpp sources/ObjectManager.hpp sources/PhysicsManager.cpp sources/PhysicsManager.hpp sources/GraphicsManager.cpp sources/GraphicsManager.hpp sources/GameManager.cpp sources/GameManager.hpp sources/InterfaceManager.cpp sources/InterfaceManager.hpp sources/windowConfig.hpp sources/Match.cpp sources/Match.hpp sources/blocks.hpp sources/constants/gameStates.hpp sources/EventManager.cpp sources/EventManager.hpp sources/Tank.cpp sources/Tank.hpp sources/constants/messages.hpp sources/Collision.cpp sources/Collision.hpp sources/Bullet.cpp sources/windowConfig.hpp main.cpp sources/InterfaceManager.cpp sources/WidgetsMenu.cpp sources/WidgetsMenu.hpp sources/NetworkManager.cpp sources/Ammunition.cpp sources/Ammunition.hpp sources/Repair.cpp sources/Repair.hpp)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
find_package(TGUI REQUIRED)

add_executable(TANCHIKI ${SOURCE_FILES})

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    if (APPLE)
        target_link_libraries(TANCHIKI ${SFML_LIBRARIES} tgui)
    else()
        target_link_libraries(TANCHIKI sfml-window sfml-graphics sfml-network sfml-system sfml-audio tgui)
    endif ()
endif()