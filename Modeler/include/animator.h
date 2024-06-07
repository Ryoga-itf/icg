// Define macro for circle ratio "M_PI"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

// Include header files
#include "modelerapp.h"
#include "modelerdraw.h"
#include "modelerview.h"
#include "particleSystem.h"
#include "vec.h"
#include <FL/gl.h>
#include <math.h>

// Discern automatic and manual animation ( true: automatic / false: manual )
bool IsAutomaticAnimation() { return ModelerApplication::Instance()->Animating(); }

// Get slider control value
double GetSliderValue(int enumeration) { return ModelerApplication::Instance()->GetControlValue(enumeration); }

// Set slider control value
void SetSliderValue(int enumeration, double value) {
    ModelerApplication::Instance()->SetControlValue(enumeration, value);
}
