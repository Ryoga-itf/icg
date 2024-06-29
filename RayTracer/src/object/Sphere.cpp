#include <cmath>

#include "object/Sphere.h"

bool Sphere::intersectLocal(const ray &r, isect &i) const {
    const auto p = r.getPosition();
    const auto d = r.getDirection();

    const auto det = (p * d) * (p * d) - p * p + 1.0;

    if (det < 0.0) {
        return false;
    }

    const auto t1 = -(p * d) - std::sqrt(det);
    const auto t2 = -(p * d) + std::sqrt(det);

    double t;
    if (t1 > RAY_EPSILON) {
        t = t1;
    } else if (t2 > RAY_EPSILON) {
        t = t2;
    } else {
        return false;
    }

    const auto intersect = r.at(t);
    if (intersect * intersect - 1.0 < RAY_EPSILON) {
        i.obj = this;
        i.t = t;
        i.N = intersect;
        i.N.normalize();
        return true;
    }
    return false;
}
