cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(APP_EXE GameEngine)

if (WIN32)
    add_link_options(-static -static-libgcc -static-libstdc++)
    # -mwindows removes the console window
#    set(CMAKE_CXX_FLAGS "-pthread -mwindows")
    set(CMAKE_CXX_FLAGS "-pthread")
#    if (cmake-build-release)
#    else ()
#    endif ()
else ()
    set(CMAKE_CXX_FLAGS "-pthread")
endif ()

project(${APP_EXE})

# Game representation
file(GLOB_RECURSE source_game_representation
        src/main.cpp
        src/game_representation/*.cpp
        src/game_representation/*.h
        )

add_executable(${APP_EXE} ${source_game_representation})

# Game logic static library
file(GLOB_RECURSE source_game_logic
        src/game_logic/*.cpp
        src/game_logic/*.h
        )

add_library(SOURCE_GAME_LOGIC_LIB STATIC ${source_game_logic})

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${APP_EXE} SOURCE_GAME_LOGIC_LIB sfml-graphics sfml-audio)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})