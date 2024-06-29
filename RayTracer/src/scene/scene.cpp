#include "scene/scene.h"
#include "scene/BSPTree.h"
#include "scene/light.h"
#include "ui/TraceUI.h"
#include <cmath>
#include <limits>
#include <utility>

extern TraceUI *traceUI;

using namespace std;

void BoundingBox::operator=(const BoundingBox &target) {
    min = target.min;
    max = target.max;
}

// Does this bounding box intersect the target?
bool BoundingBox::intersects(const BoundingBox &target) const {
    return ((target.min[0] - RAY_EPSILON <= max[0]) && (target.max[0] + RAY_EPSILON >= min[0]) &&
            (target.min[1] - RAY_EPSILON <= max[1]) && (target.max[1] + RAY_EPSILON >= min[1]) &&
            (target.min[2] - RAY_EPSILON <= max[2]) && (target.max[2] + RAY_EPSILON >= min[2]));
}

// does the box contain this point?
bool BoundingBox::intersects(const Vec3d &point) const {
    return ((point[0] + RAY_EPSILON >= min[0]) && (point[1] + RAY_EPSILON >= min[1]) &&
            (point[2] + RAY_EPSILON >= min[2]) && (point[0] - RAY_EPSILON <= max[0]) &&
            (point[1] - RAY_EPSILON <= max[1]) && (point[2] - RAY_EPSILON <= max[2]));
}

// if the ray hits the box, put the "t" value of the intersection
// closest to the origin in tMin and the "t" value of the far intersection
// in tMax and return true, else return false.
// Using Kay/Kajiya algorithm.
bool BoundingBox::intersect(const ray &r, double &tMin, double &tMax) const {
    const auto R0 = r.getPosition();
    const auto Rd = r.getDirection();

    tMin = std::numeric_limits<double>().lowest();
    tMax = std::numeric_limits<double>().max();

    for (int currentaxis = 0; currentaxis < 3; currentaxis++) {
        const double vd = Rd[currentaxis];

        // if the ray is parallel to the face's plane (=0.0)
        if (vd == 0.0) {
            if (R0[currentaxis] < min[currentaxis] || R0[currentaxis] > max[currentaxis]) {
                return false;
            }
            continue;
        }

        const double v1 = min[currentaxis] - R0[currentaxis];
        const double v2 = max[currentaxis] - R0[currentaxis];

        // two slab intersections
        double t1 = v1 / vd;
        double t2 = v2 / vd;

        if (t1 > t2) {
            std::swap(t1, t2);
        }

        if (t1 > tMin) {
            tMin = t1;
        }
        if (t2 < tMax) {
            tMax = t2;
        }

        if (tMin > tMax) {
            // box is missed
            return false;
        }
        if (tMax < RAY_EPSILON) {
            // box is behind ray
            return false;
        }
    }
    return true; // it made it past all 3 axes.
}

bool Geometry::intersect(const ray &r, isect &i) const {
    // Transform the ray into the object's local coordinate space
    const auto pos = transform->globalToLocalCoords(r.getPosition());
    auto dir = transform->globalToLocalCoords(r.getPosition() + r.getDirection()) - pos;
    const auto length = dir.length();
    dir /= length;

    const ray localRay(pos, dir, r.type());

    if (intersectLocal(localRay, i)) {
        // Transform the intersection point & normal returned back into global space.
        i.N = transform->localToGlobalCoordsNormal(i.N);
        i.t /= length;

        return true;
    } else {
        return false;
    }
}

bool Geometry::hasBoundingBoxCapability() const {
    // by default, primitives do not have to specify a bounding box.
    // If this method returns true for a primitive, then either the ComputeBoundingBox() or
    // the ComputeLocalBoundingBox() method must be implemented.

    // If no bounding box capability is supported for an object, that object will
    // be checked against every single ray drawn.  This should be avoided whenever possible,
    // but this possibility exists so that new primitives will not have to have bounding
    // boxes implemented for them.

    return false;
}

Scene::~Scene() {
    for (auto g = objects.begin(); g != objects.end(); ++g) {
        delete (*g);
    }
    for (auto l = lights.begin(); l != lights.end(); ++l) {
        delete (*l);
    }
    for (auto t = textureCache.begin(); t != textureCache.end(); t++) {
        delete (*t).second;
    }

    if (pBSPTree) {
        delete pBSPTree;
    }
}

// Get any intersection with an object.  Return information about the
// intersection through the reference parameter.
bool Scene::intersect(const ray &r, isect &i) const {
    bool have_one = false;

    // try the non-bounded objects
    for (const auto &j : nonboundedobjects) {
        if (isect cur; j->intersect(r, cur)) {
            if (!have_one || (cur.t < i.t)) {
                i = cur;
                have_one = true;
            }
        }
    }

    // try the BSP tree
    if (traceUI->getBSPEnabled()) {
        if (isect cur; ((BSPTree *)pBSPTree)->intersect(r, cur)) {
            if (!have_one || (cur.t < i.t)) {
                i = cur;
                have_one = true;
            }
        }
    } else {
        // go over the BSP tree's objects without using the BSP tree to do so (SLOW)
        for (const auto &j : boundedobjects) {
            if (isect cur; j->intersect(r, cur)) {
                if (!have_one || (cur.t < i.t)) {
                    i = cur;
                    have_one = true;
                }
            }
        }
    }

    if (!have_one) {
        i.setT(1000.0);
    }

    // if debugging,
    intersectCache.emplace_back(r, i);

    return have_one;
}

void Scene::initBSPTree() {
    constexpr unsigned short maxTreeDepth = 13;
    constexpr unsigned long maxChildrenPerNode = 5;
    bool first_boundedobject = true;
    BoundingBox b;
    pBSPTree = new BSPTree();

    // split the objects into two categories: bounded and non-bounded
    for (const auto &j : objects) {
        if (j->hasBoundingBoxCapability()) {
            boundedobjects.push_back(j);

            // widen the scene's bounding box, if necessary
            if (first_boundedobject) {
                sceneBounds = j->getBoundingBox();
                first_boundedobject = false;
            } else {
                b = j->getBoundingBox();
                sceneBounds.max = maximum(sceneBounds.max, b.max);
                sceneBounds.min = minimum(sceneBounds.min, b.min);
            }
        } else {
            nonboundedobjects.push_back(j);
        }
    }

    ((BSPTree *)pBSPTree)->initialize(&boundedobjects, maxTreeDepth, maxChildrenPerNode, sceneBounds);
}

TextureMap *Scene::getTexture(string name) {
    const auto itr = textureCache.find(name);
    if (itr == textureCache.end()) {
        textureCache[name] = new TextureMap(name);
        return textureCache[name];
    } else {
        return (*itr).second;
    }
}
