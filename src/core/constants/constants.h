#ifndef GAMEENGINE_CORECONSTANTS_H
#define GAMEENGINE_CORECONSTANTS_H

#include <limits>
#include "../math/Vector2f.h"

namespace constants {
    // world bounderies
    extern const float world_x_min;
    extern const float world_x_max;

    // camera
    extern const float camera_view_x_min;
    extern const float camera_view_x_max;
    extern const float camera_view_y_min;
    extern const float camera_view_y_max;

    extern const Vector2f aspect_ratio;

    // player
    namespace player {
        extern const Vector2f spawn_position;
        extern const Vector2f view_size;

        extern const float jump_dt;
        extern const float jump_height;

        extern const float mass;
        extern const float horizontal_movement_force;
    }
}


#endif // GAMEENGINE_CORECONSTANTS_H
