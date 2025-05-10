#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
int main()
{ 
	int w=300, h=180;
	Fl_Window window(w,h); 
	Fl_Box* box = new Fl_Box(FL_UP_BOX, 0, 0, w, h, "Hello, World!");
	box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
	window.show(); 
	return(Fl::run());
}