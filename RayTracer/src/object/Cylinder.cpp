#include "object/Cylinder.h"
#include <cmath>
#include <utility>

bool Cylinder::intersectLocal(const ray &r, isect &i) const {
    i.obj = this;

    if (intersectCaps(r, i)) {
        if (isect ii; intersectBody(r, ii)) {
            if (ii.t < i.t) {
                i = ii;
                i.obj = this;
            }
        }
        return true;
    } else {
        return intersectBody(r, i);
    }
}

bool Cylinder::intersectBody(const ray &r, isect &i) const {
    const double x0 = r.getPosition()[0];
    const double y0 = r.getPosition()[1];
    const double x1 = r.getDirection()[0];
    const double y1 = r.getDirection()[1];

    const double a = x1 * x1 + y1 * y1;
    const double b = 2.0 * (x0 * x1 + y0 * y1);
    const double c = x0 * x0 + y0 * y0 - 1.0;

    if (0.0 == a) {
        // This implies that x1 = 0.0 and y1 = 0.0, which further
        // implies that the ray is aligned with the body of the cylinder,
        // so no intersection.
        return false;
    }

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return false;
    }

    discriminant = std::sqrt(discriminant);

    const double t2 = (-b + discriminant) / (2.0 * a);

    if (t2 <= RAY_EPSILON) {
        return false;
    }

    const double t1 = (-b - discriminant) / (2.0 * a);

    if (t1 > RAY_EPSILON) {
        // Two intersections.
        const Vec3d P = r.at(t1);
        const double z = P[2];
        if (z >= 0.0 && z <= 1.0) {
            // It's okay.
            i.t = t1;
            i.N = Vec3d(P[0], P[1], 0.0);
            i.N.normalize();
            return true;
        }
    }

    const Vec3d P = r.at(t2);
    const double z = P[2];
    if (z >= 0.0 && z <= 1.0) {
        i.t = t2;

        Vec3d normal(P[0], P[1], 0.0);
        // In case we are _inside_ the _uncapped_ cone, we need to flip the normal.
        // Essentially, the cone in this case is a double-sided surface
        // and has _2_ normals
        if (!capped && (normal * r.getDirection()) > 0) {
            normal = -normal;
        }

        i.N = normal.normalized();
        return true;
    }

    return false;
}

bool Cylinder::intersectCaps(const ray &r, isect &i) const {
    if (!capped) {
        return false;
    }

    const double pz = r.getPosition()[2];
    const double dz = r.getDirection()[2];

    if (0.0 == dz) {
        return false;
    }

    double t1 = (1.0 - pz) / dz;
    double t2 = (-pz) / dz;

    if (dz > 0.0) {
        std::swap(t1, t2);
    }

    if (t2 < RAY_EPSILON) {
        return false;
    }

    if (t1 >= RAY_EPSILON) {
        if (const Vec3d p(r.at(t1)); (p[0] * p[0] + p[1] * p[1]) <= 1.0) {
            i.t = t1;
            // Intersection with cap at z = 0?
            i.N = (dz > 0.0 ? Vec3d(0.0, 0.0, -1.0) : Vec3d(0.0, 0.0, 1.0));
            return true;
        }
    }

    if (const Vec3d p(r.at(t2)); (p[0] * p[0] + p[1] * p[1]) <= 1.0) {
        i.t = t2;
        // Intersection with interior of cap at z = 1?
        i.N = (dz > 0.0 ? Vec3d(0.0, 0.0, 1.0) : Vec3d(0.0, 0.0, -1.0));
        return true;
    }

    return false;
}
