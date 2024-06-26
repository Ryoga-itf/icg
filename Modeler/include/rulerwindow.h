#ifndef RULERWINDOWS_H_INCLUDED
#define RULERWINDOWS_H_INCLUDED

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

#include "FL/Fl_Double_Window.H"
#define RW_HORIZONTAL 0
#define RW_VERTICAL 1

class RulerWindow : public Fl_Double_Window {
  public:
    RulerWindow(int x, int y, int w, int h, const char *label = 0);
    ~RulerWindow();

    // RW_HORIZONTAL or RW_VERTICAL
    void type(unsigned char t);
    void range(double min, double max);
    void textsize(int s);
    void rulercolor(Fl_Color color) { m_flcColor = color; }

  protected:
    void draw();

    Fl_Color m_flcColor;
    unsigned char m_byType;
    double m_dRangeMin, m_dRangeMax;
    int m_iTextSize;
};

#endif // RULERWINDOWS_H_INCLUDED
