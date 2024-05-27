// Define macro for circle ratio "M_PI"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

// Include header files
#include <math.h>
#include <FL/gl.h>
#include "vec.h"
#include "modelerapp.h"
#include "modelerview.h"
#include "modelerdraw.h"
#include "particleSystem.h"

// Discern automatic and manual animation ( true: automatic / false: manual )
bool IsAutomaticAnimation()
{
    return ModelerApplication::Instance()->Animating();
}

// Get slider control value
double GetSliderValue( int enumeration )
{
    return ModelerApplication::Instance()->GetControlValue( enumeration );
}

// Set slider control value
void SetSliderValue( int enumeration, double value )
{
    ModelerApplication::Instance()->SetControlValue( enumeration, value );
}
