#include "animation_data.h"

const std::map<std::string, std::map<std::string, AnimationData>> animation_data_groups =
        {
                {"background", {
                        {"", {{
                                          "data/textures/prototype/Dark/texture_07.png",
                                    }, 0.f, true}},
                }},
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
                                  }, 0.10f, false}},
                        {"run", {{
                                         "data/sprites/adventurer/adventurer-run-00.png",
                                         "data/sprites/adventurer/adventurer-run-01.png",
                                         "data/sprites/adventurer/adventurer-run-02.png",
                                         "data/sprites/adventurer/adventurer-run-03.png",
                                         "data/sprites/adventurer/adventurer-run-04.png",
                                         "data/sprites/adventurer/adventurer-run-05.png",
                                 }, 0.10f, true}},
                }}
        };