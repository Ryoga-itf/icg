#include "object/Square.h"
#include <cmath>

// Test
bool Square::intersectLocal(const ray &r, isect &i) const {
    const auto p = r.getPosition();
    const auto d = r.getDirection();

    if (d[2] == 0.0) {
        return false;
    }

    double t = -p[2] / d[2];

    if (t <= RAY_EPSILON) {
        return false;
    }

    const auto P = r.at(t);

    if (P[0] < -0.5 or P[0] > 0.5) {
        return false;
    }

    if (P[1] < -0.5 or P[1] > 0.5) {
        return false;
    }

    i.obj = this;
    i.t = t;
    i.N = (d[2] > 0.0 ? Vec3d(0.0, 0.0, -1.0) : Vec3d(0.0, 0.0, 1.0));

    i.setUVCoordinates(Vec2d(P[0] + 0.5, P[1] + 0.5));
    return true;
}
