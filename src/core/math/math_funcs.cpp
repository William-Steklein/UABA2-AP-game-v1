#include "math_funcs.h"

float lerp(float x0, float x1, float alpha) { return (1 - alpha) * x0 + alpha * x1; }

float to_radian(float angle) { return angle * static_cast<float>(M_PI) / 180.f; }

float to_degree(float angle) { return angle * 180.f / static_cast<float>(M_PI); }

void degree_mod(float &angle) {
    if (angle > 0) {
        while (angle > 360) {
            angle -= 360;
        }
    } else {
        while (angle < -360) {
            angle += 360;
        }
    }
}

void radian_mod(float &angle) {
    if (angle > 0) {
        while (angle > 2 * M_PI) {
            angle -= 2 * M_PI;
        }
    } else {
        while (angle < -2 * M_PI) {
            angle += 2 * M_PI;
        }
    }
}