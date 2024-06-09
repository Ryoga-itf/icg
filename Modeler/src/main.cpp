// Include header file
#include "controller.h"
#include "model.h"

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView *createModel(int x, int y, int w, int h, char *label) { return new Model(x, y, w, h, label); }

// main function
int main() {
    // Initialize the controls
    // Constructor is ModelerControl(name, minimumvalue, maximumvalue,
    //                                 stepsize, defaultvalue)
    // You will want to modify this to accommodate your model.
    ModelerControl controls[NUM_CONTROLS + 1];

    // Set model controllers
    SetController(controls);

    // Initialize the modeler application with your model and the
    // appropriate array of controls.
    ModelerApplication::Instance()->Init(&createModel, controls, NUM_CONTROLS);

    ParticleSystem *ps = new ParticleSystem();
    ModelerApplication::Instance()->SetParticleSystem(ps);

    // make sure we give back the memory to older OSs that don't
    // clear your memory pool after shutdown.
    int Result = ModelerApplication::Instance()->Run();
    delete ModelerApplication::Instance();
    return Result;
}
