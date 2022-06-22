file(GLOB_RECURSE CoreLibFiles *.cpp)

add_library(CoreLib STATIC ${CoreLibFiles} ${HEADER_FILES} entities/Entity.cpp entities/Entity.h physics/Hitbox.cpp physics/Hitbox.h physics/collisions.h physics/collisions.cpp physics/Ray.cpp physics/Ray.h entities/game/Doodle.cpp entities/game/Doodle.h animation/AnimationStateMachine.cpp animation/AnimationStateMachine.h entities/IEntityViewCreator.h entities/ui/UIWidget.cpp entities/ui/UIWidget.h)

target_include_directories(CoreLib INTERFACE "${PROJECT_SOURCE_DIR}/src")
