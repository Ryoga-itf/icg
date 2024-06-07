#include "linearcurveevaluator.h"
#include <cassert>
using namespace Animator;

void LinearCurveEvaluator::evaluateCurve(const std::vector<Point> &ptvCtrlPts, std::vector<Point> &ptvEvaluatedCurvePts,
                                         const float &fAniLength, const bool &bWrap, const float default_val) const {
    int iCtrlPtCount = ptvCtrlPts.size();
    ptvEvaluatedCurvePts.clear();

    ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());

    float x = 0.0;
    float y1;

    if (bWrap) {
        // if wrapping is on, interpolate the y value at xmin and
        // xmax so that the slopes of the lines adjacent to the
        // wraparound are equal.

        if ((ptvCtrlPts[0].x + fAniLength) - ptvCtrlPts[iCtrlPtCount - 1].x > 0.0f) {
            y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x) +
                  ptvCtrlPts[iCtrlPtCount - 1].y * ptvCtrlPts[0].x) /
                 (ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x);
        } else
            y1 = ptvCtrlPts[0].y;
    } else {
        // if wrapping is off, make the first and last segments of
        // the curve horizontal.

        y1 = ptvCtrlPts[0].y;
    }

    ptvEvaluatedCurvePts.push_back(Point(x, y1));

    /// set the endpoint based on the wrap flag.
    float y2;
    x = fAniLength;
    if (bWrap)
        y2 = y1;
    else
        y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

    ptvEvaluatedCurvePts.push_back(Point(x, y2));
}
