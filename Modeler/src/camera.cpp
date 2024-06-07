#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <cstdio>
#include <fstream>

#include "modelerapp.h" // needed to read values from graph widget
#include "modelerui.h"  // needed to read values from graph widget

#include "camera.h"
#include "curve.h"
#include "curveevaluator.h"
#include "linearcurveevaluator.h"

#pragma warning(push)
#pragma warning(disable : 4244)

// As of 02sp, the camera curves appear in the "model controls" pane.
// The camera curves are always at the end of the list.  This function
// returns the index of the first camera curve in the list.
int GetFirstCamCurveIndex() {
    ModelerApplication *app;
    int total_curves; // This is the total number of items that appear in the
                      // "model controls" pane, and equals the number of curves
                      // for the model + number of curves for the camera.

    app = ModelerApplication::Instance();
    // The camera curves are always last in the list of "model curves" in the left pane.
    total_curves = app->GetUI()->m_pwndGraphWidget->numCurves();
    return total_curves - NUM_CAM_CURVES;
}

int GetCamCurveIndex(CameraCurve c) { return GetFirstCamCurveIndex() + c; }

#define CAM_VAL(x) (ModelerApplication::Instance()->GetControlValue(GetCamCurveIndex(x)))

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502f
#endif

const float kMouseRotationSensitivity = 1.0f / 90.0f;
const float kMouseTranslationXSensitivity = 0.03f;
const float kMouseTranslationYSensitivity = 0.03f;
const float kMouseZoomSensitivity = 0.08f;

Camera::Camera() {
    mAzimuth = mTwist = 0.0f;
    mElevation = 0.7f;
    mDolly = -20.0f;
    mLookAt = Vec3f(0, 0, 0);
    mFOV = 30;
    mNearCP = 1;
    mFarCP = 100;

    mCurrentMouseAction = kActionNone;

    calculateViewingTransformParameters();
}

/**
 * Possibly useful fxn that is not currently called.
 * You could use this to generate the camera's up and right
 * vectors in world space...
 */
void MakeCamTrans(Mat4f &m, Vec3f &eye, Vec3f &at, Vec3f &up) {

    // compute normalized vectors
    Vec3f n_up = up;
    n_up.normalize();
    Vec3f k = (at - eye);
    k.normalize();

    // compute orthonormal basis (i, j, k)
    Vec3f i = k ^ n_up;
    Vec3f j = i ^ k;
    i.normalize();
    j.normalize();

    // construct rotation matrix
    m = Mat4f(i[0], i[1], i[2], 0, j[0], j[1], j[2], 0, -k[0], -k[1], -k[2], 0, 0, 0, 0, 1);
}

void Camera::calculateViewingTransformParameters() {
    // compute new transformation based on
    // user interaction
    Mat4f dollyXform;
    Mat4f azimXform;
    Mat4f elevXform;
    Mat4f twistXform;
    Mat4f originXform;

    Vec3f upVector;

    makeHTrans(dollyXform, Vec3f(0, 0, mDolly));
    makeHRotY(azimXform, mAzimuth);
    makeHRotX(elevXform, mElevation);
    makeDiagonal(twistXform, 1.0f);
    makeHTrans(originXform, mLookAt);

    mPosition = Vec3f(0, 0, 0);
    // grouped for (mat4 * vec3) ops instead of (mat4 * mat4) ops
    mPosition = originXform * (azimXform * (elevXform * (dollyXform * mPosition)));

    if (fmodf(mElevation, 2.0 * M_PI) < 3 * M_PI / 2 && fmodf(mElevation, 2.0 * M_PI) > M_PI / 2)
        mUpVector = Vec3f(0, -1, 0);
    else
        mUpVector = Vec3f(0, 1, 0);

    mDirtyTransform = false;
}

void Camera::clickMouse(MouseAction_t action, int x, int y) {
    mCurrentMouseAction = action;
    mLastMousePosition[0] = x;
    mLastMousePosition[1] = y;
}

void Camera::dragMouse(int x, int y) {
    Vec3f mouseDelta = Vec3f(x, y, 0.0f) - mLastMousePosition;
    mLastMousePosition = Vec3f(x, y, 0.0f);

    switch (mCurrentMouseAction) {
    case kActionTranslate: {
        calculateViewingTransformParameters();

        double xTrack = -mouseDelta[0] * kMouseTranslationXSensitivity;
        double yTrack = mouseDelta[1] * kMouseTranslationYSensitivity;

        Vec3f transXAxis = mUpVector ^ (mPosition - mLookAt);
        transXAxis /= sqrt((transXAxis * transXAxis));
        Vec3f transYAxis = (mPosition - mLookAt) ^ transXAxis;
        transYAxis /= sqrt((transYAxis * transYAxis));

        setLookAt(getLookAt() + transXAxis * xTrack + transYAxis * yTrack);

        break;
    }
    case kActionRotate: {
        float dAzimuth = -mouseDelta[0] * kMouseRotationSensitivity;
        float dElevation = mouseDelta[1] * kMouseRotationSensitivity;

        setAzimuth(getAzimuth() + dAzimuth);
        setElevation(getElevation() + dElevation);

        if (getAzimuth() > M_PI)
            mAzimuth -= 2.0 * M_PI;
        if (getElevation() > M_PI)
            mElevation -= 2.0 * M_PI;

        //	fprintf(stderr, "az %f, elev %f\n", mAzimuth, mElevation);

        break;
    }
    case kActionZoom: {
        float dDolly = -mouseDelta[1] * kMouseZoomSensitivity;
        setDolly(getDolly() + dDolly);
        break;
    }
    case kActionTwist:
        // Not implemented
    default:
        break;
    }
}

void Camera::releaseMouse(int x, int y) { mCurrentMouseAction = kActionNone; }

void Camera::applyViewingTransform() {
    if (mDirtyTransform)
        calculateViewingTransformParameters();

    // Set Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(mFOV, 1.0, mNearCP, mFarCP);

    // Set View matrix
    glMatrixMode(GL_MODELVIEW);
    // Place the camera at mPosition, aim the camera at
    // mLookAt, and twist the camera such that mUpVector is up
    gluLookAt(mPosition[0], mPosition[1], mPosition[2], mLookAt[0], mLookAt[1], mLookAt[2], mUpVector[0], mUpVector[1],
              mUpVector[2]);

    Vec3f F = mLookAt - mPosition;
    glRotatef(mTwist, F[0], F[1], F[2]);
}

/** Update camera params based on keyframes **/
void Camera::update(float t) {
    // otherwise, update based on curves
    mAzimuth = CAM_VAL(AZIMUTH);
    mElevation = CAM_VAL(ELEVATION);
    mDolly = CAM_VAL(DOLLY);
    mTwist = CAM_VAL(TWIST);
    mLookAt[0] = CAM_VAL(LOOKAT_X);
    mLookAt[1] = CAM_VAL(LOOKAT_Y);
    mLookAt[2] = CAM_VAL(LOOKAT_Z);
    mFOV = CAM_VAL(FOV);
    mNearCP = CAM_VAL(NEARCP);
    mFarCP = CAM_VAL(FARCP);

    mDirtyTransform = true;
}

bool Camera::setKeyframe(float time, float maxTime) {
    for (int i = 0; i < NUM_CAM_CURVES; i++) {
        int iIndexThisCamCurve = GetCamCurveIndex((CameraCurve)i);

        Curve *pCurve = ModelerApplication::Instance()->GetUI()->getCurve(iIndexThisCamCurve);

        float fValue;
        switch (i) {
        case AZIMUTH:
            fValue = getAzimuth();
            break;
        case ELEVATION:
            fValue = getElevation();
            break;
        case DOLLY:
            fValue = getDolly();
            break;
        case TWIST:
            fValue = getTwist();
            break;
        case LOOKAT_X:
            fValue = getLookAt()[0];
            break;
        case LOOKAT_Y:
            fValue = getLookAt()[1];
            break;
        case LOOKAT_Z:
            fValue = getLookAt()[2];
            break;
        case FOV:
            fValue = getFOV();
            break;
        case NEARCP:
            fValue = getNearCP();
            break;
        case FARCP:
            fValue = getFarCP();
            break;
            //	default:	assert(0);	// invalid curve index
        }

        pCurve->addControlPoint(Animator::Point(time, fValue));
    }
    return true;
}

// When the user click the the range of x around t that camera control points will be removed.
const float REMOVE_KEYFRAME_RANGE = 0.2f;

void Camera::removeKeyframe(float time) {
    for (int i = 0; i < NUM_CAM_CURVES; i++) {
        int iIndexThisCamCurve = GetCamCurveIndex((CameraCurve)i);

        Curve *pCurve = ModelerApplication::Instance()->GetUI()->getCurve(iIndexThisCamCurve);

        pCurve->removeControlPointsInRange(time - REMOVE_KEYFRAME_RANGE / 2, time + REMOVE_KEYFRAME_RANGE / 2);
    }
}

#pragma warning(pop)
