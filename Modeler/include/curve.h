#ifndef CURVE_H_INCLUDED
#define CURVE_H_INCLUDED

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#pragma warning(disable : 4786)

#include <iostream>
#include <string>
#include <vector>

#include "point.h"

class CurveEvaluator;

class Curve {
  public:
    Curve();
    Curve(const float fMaxX, const float fStartYValue);
    Curve(const float fMaxX, const Animator::Point &point);
    Curve(std::istream &isInputStream);

    void maxX(const float fNewMaxX);
    void setEvaluator(CurveEvaluator *pceEvaluator) { m_pceEvaluator = pceEvaluator; }
    float evaluateCurveAt(const float x) const;
    void scaleX(const float fScale);
    void addControlPoint(const Animator::Point &point);
    void removeControlPoint(const int iCtrlPt);
    void removeControlPoint2(const int iCtrlPt);
    void removeControlPointsInRange(const float fMinX, const float fMaxX);
    void getControlPoint(const int iCtrlPt, Animator::Point &ptCtrlPt) const { ptCtrlPt = m_ptvCtrlPts[iCtrlPt]; }
    int getClosestControlPoint(const Animator::Point &point, Animator::Point &ptCtrlPt) const;
    void getClosestPoint(const Animator::Point &pt, Animator::Point &ptClosestPt) const;
    float getDistanceToCurve(const Animator::Point &normalized_point) const;
    void moveControlPoint(const int iCtrlPt, const Animator::Point &ptNewPt);
    void moveControlPoints(const std::vector<int> &ivCtrlPts, const Animator::Point &ptOffset, const float fMinY,
                           const float fMaxY);

    int controlPointCount(void) const;
    int segmentCount(void) const;

    void wrap(bool bWrap);
    bool wrap() const;
    void drawEvaluatedCurveSegments(void) const;
    void drawControlPoints(void) const;
    void drawControlPoint(int iCtrlPt) const;
    void drawCurve(void) const;
    void invalidate(void) const;

    void toStream(std::ostream &output_stream) const;
    void fromStream(std::istream &input_stream);

    void set_default_value(float new_def);

    void clear();

  protected:
    // the default value the curve goes to if no control points are defined
    float default_value;

    void init(const float fStartYValue = 0.0f);
    void reevaluate(void) const;
    // this must be called when a control point is added
    void sortControlPoints(void) const;

    CurveEvaluator *m_pceEvaluator;

    mutable std::vector<Animator::Point> m_ptvCtrlPts;
    mutable std::vector<Animator::Point> m_ptvEvaluatedCurvePts;
    mutable bool m_bDirty;

    float m_fMaxX;
    bool m_bWrap;
    static float s_fCtrlPtXEpsilon;
};

std::ostream &operator<<(std::ostream &output_stream, const Curve &curve_data);
std::istream &operator>>(std::istream &input_stream, Curve &curve_data);

#endif // CURVE_H_INCLUDED
