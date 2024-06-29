#include "scene/material.h"
#include "scene/light.h"
#include "scene/ray.h"

#include "fileio/imageio.h"
#include <algorithm>

using namespace std;
extern bool debugMode;

// Apply the Phong model to this point on the surface of the object, returning
// the color of that point.
Vec3d Material::shade(Scene *scene, const ray &r, const isect &i) const {
    auto lum = ke(i) + prod(ka(i), scene->ambient());
    const auto v = -r.getDirection();

    for (auto litr = scene->beginLights(); litr != scene->endLights(); litr++) {
        const auto *pLight = *litr;

        auto ld = pLight->getDirection(r.at(i.t));
        auto n = i.N;
        auto v = -r.getDirection();
        ld.normalize();
        n.normalize();
        v.normalize();

        auto rj = ld + 2 * (n * (ld * n) / (ld.length() * n.length()) - ld);
        rj.normalize();

        const auto lc = pLight->getColor(r.at(i.t));
        const auto atten = pLight->distanceAttenuation(r.at(i.t)) * Vec3d(1.0, 1.0, 1.0);

        // diffuse color
        const auto ldf = kd(i) * std::max(n * ld, 0.0);

        // specular color
        const auto lsp = ks(i) * std::pow(std::max(v * rj, 0.0), shininess(i));

        lum += prod(atten, prod(lc, ldf + lsp));
    }
    return lum;
}

TextureMap::TextureMap(string filename) {
    data = load(filename.c_str(), width, height);
    if (0 == data) {
        width = 0;
        height = 0;
        string error("Unable to load texture map '");
        error.append(filename);
        error.append("'.");
        throw TextureMapException(error);
    }
}

Vec3d TextureMap::getMappedValue(const Vec2d &coord) const {
    // YOUR CODE HERE

    // In order to add texture mapping support to the
    // raytracer, you need to implement this function.
    // What this function should do is convert from
    // parametric space which is the unit square
    // [0, 1] x [0, 1] in 2-space to Image coordinates,
    // and use these to perform bilinear interpolation
    // of the values.

    return Vec3d(1.0, 1.0, 1.0);
}

Vec3d TextureMap::getPixelAt(int x, int y) const {
    // This keeps it from crashing if it can't load
    // the texture, but the person tries to render anyway.
    if (0 == data)
        return Vec3d(1.0, 1.0, 1.0);

    if (x >= width)
        x = width - 1;
    if (y >= height)
        y = height - 1;

    // Find the position in the big data array...
    int pos = (y * width + x) * 3;
    return Vec3d(double(data[pos]) / 255.0, double(data[pos + 1]) / 255.0, double(data[pos + 2]) / 255.0);
}

Vec3d MaterialParameter::value(const isect &is) const {
    if (0 != _textureMap)
        return _textureMap->getMappedValue(is.uvCoordinates);
    else
        return _value;
}

double MaterialParameter::intensityValue(const isect &is) const {
    if (0 != _textureMap) {
        Vec3d value(_textureMap->getMappedValue(is.uvCoordinates));
        return (0.299 * value[0]) + (0.587 * value[1]) + (0.114 * value[2]);
    } else
        return (0.299 * _value[0]) + (0.587 * _value[1]) + (0.114 * _value[2]);
}
