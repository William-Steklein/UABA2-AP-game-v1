#ifndef GAMEENGINE_CORECONSTANTS_H
#define GAMEENGINE_CORECONSTANTS_H

#include <limits>
#include "math/Vector2f.h"

namespace constants {
    // camera
    extern const float world_x_min;
    extern const float world_x_max;
    extern const float world_y_min;
    extern const float world_y_max;

    extern const float camera_view_x_min;
    extern const float camera_view_x_max;
    extern const float camera_view_y_min;
    extern const float camera_view_y_max;

    extern const Vector2f aspect_ratio;
}


#endif // GAMEENGINE_CORECONSTANTS_H
