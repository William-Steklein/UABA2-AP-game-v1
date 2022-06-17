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

add_subdirectory(src)

add_executable(${PROJECT_NAME} ./apps/app.cpp)
target_link_libraries(${PROJECT_NAME} GameLib)

# data
file(COPY "./data" DESTINATION "${CMAKE_BINARY_DIR}")
