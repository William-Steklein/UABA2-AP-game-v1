#ifndef GAMEENGINE_INPUTMAP_H
#define GAMEENGINE_INPUTMAP_H

#include "math/Vector2f.h"
#include <string>

struct InputMap {
    bool a{false};
    bool b{false};
    bool c{false};
    bool d{false};
    bool e{false};
    bool f{false};
    bool g{false};
    bool h{false};
    bool i{false};
    bool j{false};
    bool k{false};
    bool l{false};
    bool m{false};
    bool n{false};
    bool o{false};
    bool p{false};
    bool q{false};
    bool r{false};
    bool s{false};
    bool t{false};
    bool u{false};
    bool v{false};
    bool w{false};
    bool x{false};
    bool y{false};
    bool z{false};

    bool slash{false};
    bool esc{false};

    bool get_input_stream{false};
    std::string input_stream;

    Vector2f mouse_pos_world;
    Vector2f mouse_pos_representation_window;

    bool mouse_button_left{false};
    bool mouse_button_right{false};
    bool mouse_button_middle{false};

    float mouse_wheel_delta{0};
};

#endif // GAMEENGINE_INPUTMAP_H
