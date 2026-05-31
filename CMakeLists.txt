cmake_minimum_required(VERSION 3.14)
project(Pacman)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

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
    include/ghost.h
)

target_include_directories(Pacman PRIVATE include)
target_link_libraries(Pacman PRIVATE sfml-system sfml-window sfml-graphics)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    add_custom_command(TARGET Pacman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE_DIR:Pacman>
        COMMENT "Copying SFML DLLs"
    )
endif()