#pragma warning(disable : 4786)

#include "particleSystem.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// #include <limits>

using namespace std;

static float prevT;

float getRandom(float fMin, float fMax) { return fMin + (fMax - fMin) * (float)rand() / (float)RAND_MAX; }

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() {
    simulate = false;
    Particle_num = 0;
    for (int i = 0; i < MAX_PARTICLE; i++) {
        particle[i] = Particle();
    }
}

/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() {
    // TODO
}

/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t) {

    // TODO

    // These values are used by the UI ...
    // negative bake_end_time indicates that simulation
    // is still progressing, and allows the
    // indicator window above the time slider
    // to correctly show the "baked" region
    // in grey.
    bake_end_time = -1;
    simulate = true;
    dirty = true;
}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t) {

    // TODO

    // These values are used by the UI
    simulate = false;
    dirty = true;
}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t) {

    // TODO

    // These values are used by the UI
    simulate = false;
    dirty = true;
}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t) {

    // TODO
    if (simulate == false) {
        return;
    }

    for (int i = 0; i < MAX_PARTICLE; i++) {
        particle[i].f = particle[i].m * G - drag * particle[i].v;
        particle[i].v += (t - prevT) * (particle[i].f / particle[i].m);
        particle[i].x += (t - prevT) * particle[i].v;
    }

    // Debugging info
    if (t - prevT > .04) {
        printf("(!!) Dropped Frame %lf (!!)\n", t - prevT);
    }
    prevT = t;
}

/** Render particles */
void ParticleSystem::drawParticles(float t) {
    if (simulate == false) {
        return;
    }

    for (int i = 0; i < MAX_PARTICLE; i++) {
        if (particle[i].m > 0.0) {
            glPointSize(3.0); // パーティクルの大きさ
            glBegin(GL_POINTS);
            glVertex3f(particle[i].x[0], particle[i].x[1], particle[i].x[2]);
            glEnd();
        }
    }
}

/** Adds the current configuration of particles to
 * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) {

    // TODO (baking is extra credit)
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked() {

    // TODO (baking is extra credit)
}

void ParticleSystem::AddParticleStartingAt(Vec3d WorldPoint) {
    if (simulate == false) {
        return;
    }
    if (Particle_num > MAX_PARTICLE) {
        Particle_num = 0;
    }
    const double x = getRandom(-0.5, 0.5);
    const double z = getRandom(-0.5, 0.5);
    particle[Particle_num] = Particle(1.0, WorldPoint, Vec3d(x, 0.0, z), Vec3d(0.0, 0.0, 0.0));
    Particle_num++;
    return;
}

Mat4f ParticleSystem::getModelViewMatrix() {
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    Mat4f matMV(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
    return matMV.transpose(); // convert to row major
}

void ParticleSystem::SpawnParticles(Mat4f CameraTransforms) {
    Mat4f matCam = getModelViewMatrix();
    Mat4f ModelTransforms = CameraTransforms.inverse() * matCam;
    Vec4f WorldPoint1 = ModelTransforms * Vec4f(0, 0, 0, 1);
    Vec3d WorldPoint(WorldPoint1[0], WorldPoint1[1], WorldPoint1[2]);
    for (int i = 0; i < Spawn_Num; i++) {
        AddParticleStartingAt(WorldPoint);
    }
    return;
}
