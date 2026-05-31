cmake_minimum_required(VERSION 3.17)
project(Pacman)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pacman
    src/main.cpp
    src/game.cpp
    src/pacman.cpp
    src/fruit.cpp
    src/map.cpp
    src/special_fruit.cpp
    src/ghost.cpp

    include/game.h
    include/pacman.h
    include/fruit.h
    include/constants.h
    include/map.h
    include/special_fruit.h
    include/ghost.h)

include_directories(include /usr/include c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Pacman ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

