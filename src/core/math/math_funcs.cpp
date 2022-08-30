#include "math_funcs.h"

float lerp(float x0, float x1, float alpha) { return (1 - alpha) * x0 + alpha * x1; }

Vector2f lerp(const Vector2f &p0, const Vector2f &p1, float alpha) {
    return {lerp(p0.x, p1.x, alpha), lerp(p0.y, p1.y, alpha)};
}

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

bool linesegmentIntersection(const Vector2f &l1p1, const Vector2f &l1p2, const Vector2f &l2p1,
                             const Vector2f &l2p2, Vector2f &intersection1,
                             Vector2f &intersection2, bool &is_collinear) {
    const Vector2f &p = l1p1;
    const Vector2f &q = l2p1;

    Vector2f r = l1p2 - l1p1;
    Vector2f s = l2p2 - l2p1;

    Vector2f q_p = q - p;

    float rxs = r.crossProduct(s);

    float q_pxs = q_p.crossProduct(s);
    float q_pxr = q_p.crossProduct(r);

    // line segments are collinear
    if (rxs == 0 && q_pxr == 0) {
        float rdotr = r.dotProduct(r);
        float sdotr = s.dotProduct(r);

        float t0{0};
        float t1{0};

        // interval [t0, t1]
        if (sdotr >= 0) {
            t0 = q_p.dotProduct(r) / rdotr;
            t1 = t0 + (s.dotProduct(r) / rdotr);
        }
            // interval [t1, t0]
        else {
            t1 = (q_p.dotProduct(r) / rdotr);
            t0 = t1 + (s.dotProduct(r) / rdotr);
        }

        // if the interval intersects [0, 1]
        if ((t0 >= 0 && t0 <= 1) || (t1 >= 0 && t1 <= 1)) {
            if (t0 >= 0)
                intersection1 = p + t0 * r;
            else
                intersection1 = p;

            if (t1 <= 1)
                intersection2 = p + t1 * r;
            else
                intersection2 = p + r;

            is_collinear = true;
            return true;
        }
    }
        // line segments are parallel
    else if (rxs == 0) {
        return false;
    }
        // line segments intersect
    else {
        float t = q_pxs / rxs;
        float u = q_pxr / rxs;

        if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
            intersection1 = p + t * r;
            is_collinear = false;
            return true;
        }
    }

    // line segments are not parallel but do not intersect
    return false;
}

float sigmoid(float x, float a, float b) {
    float euler = 2.71828;
    return 1 / (1 + std::pow(euler, -(a * x) + b));
}