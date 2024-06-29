#include <algorithm>
#include <cmath>

#include "scene/light.h"

using namespace std;

double DirectionalLight::distanceAttenuation(const Vec3d &P) const {
    // distance to light is infinite, so f(di) goes to 0.  Return 1.
    return 1.0;
}

Vec3d DirectionalLight::shadowAttenuation(const Vec3d &P) const {
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.

    return Vec3d(1, 1, 1);
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
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.

    return Vec3d(1, 1, 1);
}
