/***********************
 * ParticleSystem class
 ***********************/

/**
 * The particle system class simply "manages" a collection of particles.
 * Its primary responsibility is to run the simulation, evolving particles
 * over time according to the applied forces using Euler's method.
 * This header file contains the functions that you are required to implement.
 * (i.e. the rest of the code relies on this interface)
 * In addition, there are a few suggested state variables included.
 * You should add to this class (and probably create new classes to model
 * particles and forces) to build your system.
 */

#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

#include "mat.h"
#include "vec.h"

#define MAX_PARTICLE 500                // パーティクルの最大数
#define Spawn_Num 5                     // 一度に放出する個数
static Vec3d G = Vec3d(0.0, -9.8, 0.0); // 重力加速度
static float drag = 0.001;              // 空気抵抗

class Particle {
  public:
    Particle() : m{0.0}, x{0.0, 0.0, 0.0}, v(0.0, 0.0, 0.0), f(0.0, 0.0, 0.0) {}
    Particle(float mass, Vec3d position, Vec3d velocity, Vec3d force) : m{mass}, x{position}, v{velocity}, f{force} {}

    float m; /* mass */
    Vec3d x; /* position vector */
    Vec3d v; /* velocity vector */
    Vec3d f; /* force accumulator */
};

class ParticleSystem {
  private:
    Particle particle[MAX_PARTICLE]; // パーティクルを格納する配列
    int Particle_num;

  public:
    /** Constructor **/
    ParticleSystem();

    /** Destructor **/
    virtual ~ParticleSystem();

    /** Simulation fxns **/
    // This fxn should render all particles in the system,
    // at current time t.
    virtual void drawParticles(float t);

    // This fxn should save the configuration of all particles
    // at current time t.
    virtual void bakeParticles(float t);

    // This function should compute forces acting on all particles
    // and update their state (pos and vel) appropriately.
    virtual void computeForcesAndUpdateParticles(float t);

    // This function should reset the system to its initial state.
    // When you need to reset your simulation, PLEASE USE THIS FXN.
    // It sets some state variables that the UI requires to properly
    // update the display.  Ditto for the following two functions.
    virtual void resetSimulation(float t);

    // This function should start the simulation
    virtual void startSimulation(float t);

    // This function should stop the simulation
    virtual void stopSimulation(float t);

    // This function should clear out your data structure
    // of baked particles (without leaking memory).
    virtual void clearBaked();

    virtual void AddParticleStartingAt(Vec3d WorldPoint);

    Mat4f getModelViewMatrix();
    void SpawnParticles(Mat4f cameraTransform);

    // These accessor fxns are implemented for you
    float getBakeStartTime() { return bake_start_time; }
    float getBakeEndTime() { return bake_end_time; }
    float getBakeFps() { return bake_fps; }
    bool isSimulate() { return simulate; }
    bool isDirty() { return dirty; }
    void setDirty(bool d) { dirty = d; }

  protected:
    /** Some baking-related state **/
    float bake_fps;        // frame rate at which simulation was baked
    float bake_start_time; // time at which baking started
                           // These 2 variables are used by the UI for
                           // updating the grey indicator
    float bake_end_time;   // time at which baking ended

    /** General state variables **/
    bool simulate; // flag for simulation mode
    bool dirty;    // flag for updating ui (don't worry about this)
};

#endif // __PARTICLE_SYSTEM_H__
