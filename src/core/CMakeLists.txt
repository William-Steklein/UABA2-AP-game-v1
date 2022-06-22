file(GLOB_RECURSE CoreLibFiles *.cpp)

add_library(CoreLib STATIC ${CoreLibFiles})

target_include_directories(CoreLib INTERFACE "${PROJECT_SOURCE_DIR}/src")
