#include "point.h"

using namespace Animator;

Point::Point(void) : x(0.0), y(0.0) {}

Point::Point(const float &new_x, const float &new_y) : x(new_x), y(new_y) {}

void Point::toStream(std::ostream &output_stream) const {
    output_stream << x << std::endl;
    output_stream << y << std::endl;
}

void Point::fromStream(std::istream &input_stream) {
    input_stream >> x;
    input_stream >> y;
}

namespace Animator {

std::ostream &operator<<(std::ostream &output_stream, const Animator::Point &point) {
    point.toStream(output_stream);

    return output_stream;
}

std::istream &operator>>(std::istream &input_stream, Animator::Point &point) {
    point.fromStream(input_stream);

    return input_stream;
}

} // namespace Animator

bool PointSmallerXCompare::operator()(const Point &first, const Point &second) const {
    bool hasSmallerX = (first.x < second.x);

    return hasSmallerX;
}

bool PointLargerXCompare::operator()(const Point &first, const Point &second) const {
    bool hasLargerX = (first.x > second.x);

    return hasLargerX;
}
