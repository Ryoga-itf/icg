#include "object/trimesh.h"
#include <cmath>
#include <float.h>

using namespace std;

Trimesh::~Trimesh() {
    for (Materials::iterator i = materials.begin(); i != materials.end(); ++i)
        delete *i;
}

// must add vertices, normals, and materials IN ORDER
void Trimesh::addVertex(const Vec3d &v) { vertices.push_back(v); }

void Trimesh::addMaterial(Material *m) { materials.push_back(m); }

void Trimesh::addNormal(const Vec3d &n) { normals.push_back(n); }

// Returns false if the vertices a,b,c don't all exist
bool Trimesh::addFace(int a, int b, int c) {
    int vcnt = vertices.size();

    if (a >= vcnt || b >= vcnt || c >= vcnt)
        return false;

    TrimeshFace *newFace = new TrimeshFace(scene, new Material(*this->material), this, a, b, c);
    newFace->setTransform(this->transform);
    faces.push_back(newFace);
    scene->add(newFace);
    return true;
}

const char *Trimesh::doubleCheck()
// Check to make sure that if we have per-vertex materials or normals
// they are the right number.
{
    if (!materials.empty() && materials.size() != vertices.size())
        return "Bad Trimesh: Wrong number of materials.";
    if (!normals.empty() && normals.size() != vertices.size())
        return "Bad Trimesh: Wrong number of normals.";

    return 0;
}

// Calculates and returns the normal of the triangle too.
bool TrimeshFace::intersectLocal(const ray &r, isect &i) const {
    const auto p = r.getPosition();
    const auto d = r.getDirection();
    const auto &alpha = parent->vertices[ids[0]];
    const auto &beta = parent->vertices[ids[1]];
    const auto &gamma = parent->vertices[ids[2]];
    auto normal = ((beta - alpha) ^ (gamma - alpha));

    normal.normalize();

    const auto t = (normal * alpha - normal * p) / (normal * d);
    if (t < RAY_EPSILON) {
        return false;
    }

    const auto Q = r.at(t);
    const auto a1 = (beta - alpha) ^ (Q - alpha);
    const auto a2 = (gamma - beta) ^ (Q - beta);
    const auto a3 = (alpha - gamma) ^ (Q - gamma);
    if ((std::abs(a1 * a2 - a1.length() * a2.length()) < RAY_EPSILON) and
        (std::abs(a2 * a3 - a2.length() * a3.length()) < RAY_EPSILON)) {
        i.obj = this;
        i.t = t;
        i.N = normal;
        return true;
    }
    return false;
}

void Trimesh::generateNormals()
// Once you've loaded all the verts and faces, we can generate per
// vertex normals by averaging the normals of the neighboring faces.
{
    int cnt = vertices.size();
    normals.resize(cnt);
    int *numFaces = new int[cnt]; // the number of faces assoc. with each vertex
    memset(numFaces, 0, sizeof(int) * cnt);

    for (Faces::iterator fi = faces.begin(); fi != faces.end(); ++fi) {
        Vec3d a = vertices[(**fi)[0]];
        Vec3d b = vertices[(**fi)[1]];
        Vec3d c = vertices[(**fi)[2]];

        Vec3d faceNormal = ((b - a) ^ (c - a));
        faceNormal.normalize();

        for (int i = 0; i < 3; ++i) {
            normals[(**fi)[i]] += faceNormal;
            ++numFaces[(**fi)[i]];
        }
    }

    for (int i = 0; i < cnt; ++i) {
        if (numFaces[i])
            normals[i] /= numFaces[i];
    }

    delete[] numFaces;
}
