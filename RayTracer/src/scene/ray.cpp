#include "scene/ray.h"
#include "scene/material.h"
#include "scene/scene.h"

const Material &isect::getMaterial() const { return material ? *material : obj->getMaterial(); }
