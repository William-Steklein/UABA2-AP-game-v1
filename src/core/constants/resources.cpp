#include "resources.h"

const std::map<std::string, std::string> texture_data = {
        {"background",      "data/textures/prototype/Dark/texture_07.png"},
        {"background_tile", "data/sprites/background_tile/background_tile.png"},
        {"menu",            "data/ui/menu.png"},
        {"button",          "data/ui/button.png"},
        {"hamburger",       "data/ui/hamburger.png"},
        {"green",           "data/textures/colors/green.png"},
        {"blue",            "data/textures/colors/blue.png"},
        {"blue_redsides",   "data/textures/colors/blue_redsides.png"},
        {"yellow",          "data/textures/colors/yellow.png"},
        {"yellow_redsides", "data/textures/colors/yellow_redsides.png"},
        {"white",           "data/textures/colors/white.png"},
        {"black",           "data/textures/colors/black.png"},
        {"wall",            "data/textures/cobble_stone.png"},
        {"wall2",           "data/textures/prototype/Red/texture_03.png"},
        {"portal_radio",    "data/sprites/portal/portal_radio.png"},
        {"spring",          "data/sprites/bonus/spring.png"},
        {"jetpack",         "data/sprites/bonus/raketa_on_panel.png"},
        {"spikes",          "data/sprites/spikes/spikes.png"},
        {"skeleton",        "data/sprites/skeleton/skeleton.png"},
        {"skeleton_red",    "data/sprites/skeleton/skeleton_red.png"},
        {"bullet",          "data/sprites/bullet/bullet.png"},
};

const std::map<std::string, std::map<std::string, AnimationResource>> animation_groups_data =
        {
                {"doodle",     {
                                       {"standing", {{
                                                             "data/sprites/doodle/doodle-left.png",
                                                     }, 0.10f, true}},
                                       {"jump",  {{
                                                          "data/sprites/doodle/doodle-right.png",
                                                  }, 0.10f, false}},
                               }},
                {"adventurer", {
                                       {"crouch",   {{
                                                             "data/sprites/adventurer/adventurer-crouch-00.png",
                                                             "data/sprites/adventurer/adventurer-crouch-01.png",
                                                             "data/sprites/adventurer/adventurer-crouch-02.png",
                                                             "data/sprites/adventurer/adventurer-crouch-03.png",
                                                     }, 0.10f, true}},
                                       {"fall",  {{
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
                {"heart",      {
                                       {"red",      {{       "data/sprites/heart/heart_red.png",}}},
                                       {"black", {{       "data/sprites/heart/heart_black.png",}}},
                               }},
        };

const std::map<std::string, std::string> audio_sound_data = {
        {"scream", "data/audio/wilhelm_scream.wav"},
};

const std::map<std::string, std::string> audio_music_data = {
        {"portal_radio", "data/audio/portal_radio_music.wav"},
};