#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#pragma warning(disable : 4786)

#include <cmath>
#include <functional>
#include <iostream>

namespace Animator {
class Point {
  public:
    Point(void);
    Point(const float &x, const float &y);

    void toStream(std::ostream &output_stream) const;
    void fromStream(std::istream &input_stream);

    float distance(const Point &p) const {
        float xd = x - p.x;
        float yd = y - p.y;
        return sqrtf(xd * xd + yd * yd);
    }

    float x;
    float y;
};

std::ostream &operator<<(std::ostream &output_stream, const Animator::Point &point);
std::istream &operator>>(std::istream &input_stream, Animator::Point &point);

class PointSmallerXCompare : public std::binary_function<const Point &, const Point &, bool> {
  public:
    bool operator()(const Point &first, const Point &second) const;
};

class PointLargerXCompare : public std::binary_function<const Point &, const Point &, bool> {
  public:
    bool operator()(const Point &first, const Point &second) const;
};

}; // namespace Animator

#endif // POINT_H_INCLUDED
