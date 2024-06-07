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
inline bool IsAutomaticAnimation() { return ModelerApplication::Instance()->Animating(); }

// Get slider control value
inline double GetSliderValue(int enumeration) { return ModelerApplication::Instance()->GetControlValue(enumeration); }

// Set slider control value
inline void SetSliderValue(int enumeration, double value) {
    ModelerApplication::Instance()->SetControlValue(enumeration, value);
}
