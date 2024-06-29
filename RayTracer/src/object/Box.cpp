#include "object/Box.h"
#include <assert.h>
#include <cmath>
#include <limits>

bool Box::intersectLocal(const ray &r, isect &i) const {
    const auto p = r.getPosition();
    const auto d = r.getDirection();

    double x, y, t, bestT;
    int mod0, mod1, mod2, bestIndex;

    bestT = std::numeric_limits<double>().max();
    bestIndex = -1;

    for (int it = 0; it < 6; it++) {
        mod0 = it % 3;

        if (d[mod0] == 0) {
            continue;
        }

        t = (static_cast<double>(int(it / 3)) - 0.5 - p[mod0]) / d[mod0];

        if (t < RAY_EPSILON || t > bestT) {
            continue;
        }

        mod1 = (it + 1) % 3;
        mod2 = (it + 2) % 3;
        x = p[mod1] + t * d[mod1];
        y = p[mod2] + t * d[mod2];

        if (x <= 0.5 && x >= -0.5 && y <= 0.5 && y >= -0.5) {
            if (bestT > t) {
                bestT = t;
                bestIndex = it;
            }
        }
    }

    if (bestIndex < 0) {
        return false;
    }

    i.setT(bestT);
    i.setObject(this);

    const auto intersect_point = r.at((float)i.t);
    const auto i1 = (bestIndex + 1) % 3;
    const auto i2 = (bestIndex + 2) % 3;

    if (bestIndex < 3) {
        i.setN(Vec3d(-double(bestIndex == 0), -double(bestIndex == 1), -double(bestIndex == 2)));
        i.setUVCoordinates(Vec2d(0.5 - intersect_point[min(i1, i2)], 0.5 + intersect_point[max(i1, i2)]));
    } else {
        i.setN(Vec3d(double(bestIndex == 3), double(bestIndex == 4), double(bestIndex == 5)));
        i.setUVCoordinates(Vec2d(0.5 + intersect_point[min(i1, i2)], 0.5 + intersect_point[max(i1, i2)]));
    }
    return true;
}
