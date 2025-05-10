#ifndef MAC_FIXES_H
#define MAC_FIXES_H

#ifdef __APPLE__
  #ifndef GL_SILENCE_DEPRECATION
    #define GL_SILENCE_DEPRECATION
  #endif
  
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  
  #ifdef GLUT_BUILDING_LIB
    #undef GLUT_BUILDING_LIB
  #endif
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#ifdef __cplusplus
  #include <cmath>
#else
  #include <math.h>
#endif

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

#ifndef M_PIf
  #define M_PIf 3.14159265358979323846f
#endif

#endif