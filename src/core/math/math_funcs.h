#ifndef GAMEENGINE_MATH_FUNCS_H
#define GAMEENGINE_MATH_FUNCS_H

#include <cmath>

float lerp(float x0, float x1, float alpha);

float to_radian(float angle);

float to_degree(float angle);

void degree_mod(float &angle);

void radian_mod(float &angle);

#endif // GAMEENGINE_MATH_FUNCS_H
