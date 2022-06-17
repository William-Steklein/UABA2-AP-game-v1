file(GLOB_RECURSE CoreLibFiles *.cpp)

add_library(CoreLib STATIC ${CoreLibFiles} ${HEADER_FILES})

target_include_directories(CoreLib INTERFACE "${PROJECT_SOURCE_DIR}/src")
