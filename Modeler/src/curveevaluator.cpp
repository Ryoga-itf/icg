#include "curveevaluator.h"

using namespace Animator;

float CurveEvaluator::s_fFlatnessEpsilon = 0.00001f;
int CurveEvaluator::s_iSegCount = 16;

CurveEvaluator::~CurveEvaluator(void)
{
}

// this function handles cases where there are 0 or 1 control points defined for any curve type
void CurveEvaluator::handleEdgeCases(const std::vector<Point>& ptvCtrlPts, 
									 std::vector<Point>& ptvEvaluatedCurvePts, 
									 const float& fAniLength, 
									 const float default_val)
{
	// get rid of previously evaluated points
	ptvEvaluatedCurvePts.clear();
	if(ptvCtrlPts.size() == 0)
	{
		ptvEvaluatedCurvePts.push_back(Point(0, default_val));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, default_val));
		return;
	}
	else if(ptvCtrlPts.size() == 1)
	{
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(ptvCtrlPts[0].x, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts[0].y));
		return;		
	}
}

