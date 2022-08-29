#ifndef GAMEENGINE_MATH_FUNCS_H
#define GAMEENGINE_MATH_FUNCS_H

#include <cmath>
#include "Vector2f.h"

float lerp(float x0, float x1, float alpha);

Vector2f lerp(const Vector2f &p0, const Vector2f &p1, float alpha);

float to_radian(float angle);

float to_degree(float angle);

void degree_mod(float &angle);

void radian_mod(float &angle);

// algorithm from https://stackoverflow.com/a/565282/12557703
bool linesegmentIntersection(const Vector2f &l1p1, const Vector2f &l1p2, const Vector2f &l2p1,
                             const Vector2f &l2p2, Vector2f &intersection1,
                             Vector2f &intersection2, bool &is_collinear);

float sigmoid(float x);

#endif // GAMEENGINE_MATH_FUNCS_H
