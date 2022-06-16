#ifndef GAMEENGINE_UTILS_H
#define GAMEENGINE_UTILS_H

#include <cmath>

namespace CoreUtils {
    float lerp(float x0, float x1, float alpha);

    float toRadian(float angle);

    float toDegree(float angle);

    void fDegreeMod(float &angle);

    void fRadianMod(float &angle);
} // namespace CoreUtils

#endif // GAMEENGINE_UTILS_H
