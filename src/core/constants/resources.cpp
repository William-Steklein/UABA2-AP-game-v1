#include "resources.h"

const std::map<std::string, std::string> textures_data = {
        {"background", "data/textures/prototype/Dark/texture_07.png"},
        {"sidescreen_background", "data/textures/black.png"},
        {"wall", "data/textures/cobble_stone.png"},
        {"portal_radio", "data/sprites/portal/portal_radio.png"},
};

const std::map<std::string, std::map<std::string, AnimationResource>> animation_groups_data =
        {
                {"doodle", {
                        {"standing", {{
                                          "data/sprites/doodle/doodle-left.png",
                                  }, 0.10f, true}},
                        {"jump", {{
                                          "data/sprites/doodle/doodle-right.png",
                                  }, 0.10f, false}},
                }},
                {"adventurer", {
                        {"crouch", {{
                                          "data/sprites/adventurer/adventurer-crouch-00.png",
                                          "data/sprites/adventurer/adventurer-crouch-01.png",
                                          "data/sprites/adventurer/adventurer-crouch-02.png",
                                          "data/sprites/adventurer/adventurer-crouch-03.png",
                                    }, 0.10f, true}},
                        {"fall", {{
                                          "data/sprites/adventurer/adventurer-fall-00.png",
                                          "data/sprites/adventurer/adventurer-fall-01.png",
                                  }, 0.10f, true}},
                        {"idle", {{
                                          "data/sprites/adventurer/adventurer-idle-00.png",
                                          "data/sprites/adventurer/adventurer-idle-01.png",
                                          "data/sprites/adventurer/adventurer-idle-02.png",
                                          "data/sprites/adventurer/adventurer-idle-03.png",
                                  }, 0.10f, true}},
                        {"jump", {{
                                          "data/sprites/adventurer/adventurer-jump-00.png",
                                          "data/sprites/adventurer/adventurer-jump-01.png",
                                          "data/sprites/adventurer/adventurer-jump-02.png",
                                          "data/sprites/adventurer/adventurer-jump-03.png",
                                  }, 0.15f, false}},
                        {"run", {{
                                         "data/sprites/adventurer/adventurer-run-00.png",
                                         "data/sprites/adventurer/adventurer-run-01.png",
                                         "data/sprites/adventurer/adventurer-run-02.png",
                                         "data/sprites/adventurer/adventurer-run-03.png",
                                         "data/sprites/adventurer/adventurer-run-04.png",
                                         "data/sprites/adventurer/adventurer-run-05.png",
                                 }, 0.10f, true}},
                }},
        };