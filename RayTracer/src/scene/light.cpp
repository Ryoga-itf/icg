#include <algorithm>
#include <cmath>

#include "scene/light.h"

using namespace std;

double DirectionalLight::distanceAttenuation(const Vec3d &P) const {
    // distance to light is infinite, so f(di) goes to 0.  Return 1.
    return 1.0;
}

Vec3d DirectionalLight::shadowAttenuation(const Vec3d &P) const {
    auto d = getDirection(P);
    d.normalize();
    const ray r(P, d, ray::SHADOW);
    if (isect i; getScene()->intersect(r, i)) {
        return Vec3d(0.0, 0.0, 0.0);
    } else {
        return Vec3d(1.0, 1.0, 1.0);
    }
}

Vec3d DirectionalLight::getColor(const Vec3d &P) const {
    // Color doesn't depend on P
    return color;
}

Vec3d DirectionalLight::getDirection(const Vec3d &P) const { return -orientation; }

double PointLight::distanceAttenuation(const Vec3d &P) const {
    const auto dv = this->position - P;
    const auto d = dv.length();
    return std::clamp(1.0 / (constantTerm + linearTerm * d + quadraticTerm * d * d), 0.0, 1.0);
}

Vec3d PointLight::getColor(const Vec3d &P) const {
    // Color doesn't depend on P
    return color;
}

Vec3d PointLight::getDirection(const Vec3d &P) const {
    Vec3d ret = position - P;
    ret.normalize();
    return ret;
}

Vec3d PointLight::shadowAttenuation(const Vec3d &P) const {
    auto d = getDirection(P);
    d.normalize();
    const ray r(P, d, ray::SHADOW);
    const auto dv = position - P;
    const auto dist = dv.length();
    if (isect i; getScene()->intersect(r, i)) {
        const auto dh = i.N - P;
        if (dh.length() < dist) {
            return Vec3d(0.0, 0.0, 0.0);
        }
    }
    return Vec3d(1.0, 1.0, 1.0);
}
