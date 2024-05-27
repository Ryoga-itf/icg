// modelerview.h

// This is the base class for all your models.  It contains
// a camera control for your use.  The draw() function will 
// set up default lighting and apply the projection, so if you 
// inherit, you will probably want to call ModelerView::draw()
// to set up the camera.

#ifndef MODELERVIEW_H
#define MODELERVIEW_H

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

#include <FL/Fl_Gl_Window.H>

class Camera;
class ModelerView;
typedef ModelerView* (*ModelerViewCreator_f)(int x, int y, int w, int h, char *label);

typedef enum { CTRL_MODE, CURVE_MODE } cam_mode_t;

class ModelerView : public Fl_Gl_Window
{
public:
    ModelerView(int x, int y, int w, int h, char *label=0);

	virtual ~ModelerView();
    virtual int handle(int event);
    virtual void draw();

	void setImage(const char *fname, const char * e);
	void saveImage(const char* filename, const char * type, int quality);
	void endDraw();

	void camera(cam_mode_t mode);
    Camera *m_camera;
	Camera *m_ctrl_camera;
	Camera *m_curve_camera;

	float t;
	void update();
	bool save_image;
};


#endif
