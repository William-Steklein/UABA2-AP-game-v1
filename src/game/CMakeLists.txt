file(GLOB_RECURSE GameLibFiles *.cpp)
add_library(GameLib STATIC ${GameLibFiles})

# SFML
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()
find_package(SFML COMPONENTS graphics audio REQUIRED)

target_link_libraries(GameLib CoreLib sfml-graphics sfml-audio)

target_include_directories(GameLib INTERFACE "${PROJECT_SOURCE_DIR}/src")
