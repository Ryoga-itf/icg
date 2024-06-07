#ifndef INCLUDED_CURVE_EVALUATOR_H
#define INCLUDED_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)

#include "curve.h"

class CurveEvaluator {
  public:
    virtual ~CurveEvaluator(void);
    virtual void evaluateCurve(const std::vector<Animator::Point> &control_points,
                               std::vector<Animator::Point> &evaluated_curve_points, const float &animation_length,
                               const bool &wrap_control_points, const float default_val) const = 0;
    static float s_fFlatnessEpsilon;
    static int s_iSegCount;

    void handleEdgeCases(const std::vector<Animator::Point> &ptvCtrlPts,
                         std::vector<Animator::Point> &ptvEvaluatedCurvePts, const float &fAniLength,
                         const float default_val);
};

#endif
