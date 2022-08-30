#include "constants.h"

namespace constants {
    const float world_x_min = -1;
    const float world_x_max = 1;

    const float camera_view_x_min = -1;
    const float camera_view_x_max = 1;
    const float camera_view_y_min = 0.f;
    const float camera_view_y_max = 3.f;

    const Vector2f aspect_ratio = {2, 3};

    namespace player {
        const Vector2f spawn_position = {0.f, 0.f};
        const Vector2f view_size = {0.6f, 0.444f};

        const float jump_dt = 0.6;
        const float jump_height = 1;

        const float jump_velocity = (2 * jump_height / jump_dt);

        const float mass = 20;
        const float horizontal_movement_force = 200;
    }

    namespace bonus {
        const float spring_jump_velocity_multiplier = 1.5f;

        const float jetpack_force_amount = 250.f;
        const float jetpack_duration = 3.f;

        namespace enemy {
            const float can_damage_duration = 1.f;
        }
    }

    namespace bullet {
        const float velocity = 2.f;
        const float time_delay = 0.4f;
    }

    namespace hpbarhearts {
        const float horizontal_distance_multiplier = 0.2f;
        const Vector2f screen_ui_size = {0.2f, 0.2f};
        const Vector2f entity_ui_size = {0.05f, 0.05f};
    }
}
