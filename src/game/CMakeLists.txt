file(GLOB_RECURSE GameLibFiles *.cpp)
add_library(GameLib STATIC ${GameLibFiles} EntityView.cpp EntityView.h EntityViewCreator.cpp EntityViewCreator.h)

# SFML
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()
find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)

target_link_libraries(GameLib CoreLib sfml-graphics sfml-audio)

target_include_directories(GameLib INTERFACE "${PROJECT_SOURCE_DIR}/src")
