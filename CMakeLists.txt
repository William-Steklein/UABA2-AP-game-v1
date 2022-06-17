cmake_minimum_required(VERSION 3.10.2)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
endif()

if (WIN32)
    # Windows
    add_link_options(-static -static-libgcc -static-libstdc++)

    set(CMAKE_CXX_FLAGS "-pthread")

    if (CMAKE_BUILD_TYPE MATCHES "Release")
        # -mwindows removes the console window
        set(CMAKE_CXX_FLAGS "-pthread -mwindows")
    endif ()
else ()
    # Linux & macOS
    set(CMAKE_CXX_FLAGS "-pthread")
endif ()

# Game representation
file(GLOB_RECURSE source_game_representation src/game_representation/*.cpp)

# Game logic static library
file(GLOB_RECURSE source_game_logic src/game_logic/*.cpp)
add_library(SOURCE_GAME_LOGIC_LIB STATIC ${source_game_logic})

add_executable(${PROJECT_NAME} ${source_game_representation} src/main.cpp)

# SFML
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()
find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} SOURCE_GAME_LOGIC_LIB sfml-graphics sfml-audio)

# assets
file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}")
