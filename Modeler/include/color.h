#ifndef INCLUDED_COLOR_H
#define INCLUDED_COLOR_H

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

class Color {
  public:
    Color(void);
    Color(const float new_red, const float new_green, const float new_blue);

    float red;
    float green;
    float blue;
};

#endif
