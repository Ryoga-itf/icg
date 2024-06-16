//=============================================================================
// ファイル: controller.h
//=============================================================================
// スライダコントローラの設定
//=============================================================================

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// ヘッダファイルのインクルード
#include "modelerapp.h"

// フレーム番号の最大値
extern int max_frame_count;

// コントローラ識別用の列挙子
enum CONTROLLERS {
    FRAME_CONTROLS, // フレームコントローラ（変更しないこと)
    L_ARM_Z_ANGLE,
    L_ARM_X_ANGLE,
    R_ARM_Z_ANGLE,
    R_ARM_X_ANGLE,
    L_HEAR_ANGLE,
    R_HEAR_ANGLE,
    NECK_X_ANGLE,
    NECK_Y_ANGLE,
    NUM_CONTROLS, // コントローラ数（必ず末尾に追加）
};

// コントローラの設定
// （NUM_CONTROLSを除くCONTROLLERS列挙子と１：１に対応付ける）
inline void SetController(ModelerControl *controls) {
    // フレーム番号の制御用スライダ
    controls[FRAME_CONTROLS] = ModelerControl("Frame Number", 0, (float)max_frame_count, 1, 0);

    controls[L_ARM_Z_ANGLE] = ModelerControl("Left Arm-Z Angle", -180.0f, 180.0f, 1.0f, 140.0f);
    controls[L_ARM_X_ANGLE] = ModelerControl("Left Arm-X Angle", -180.0f, 180.0f, 1.0f, 0.0f);
    controls[R_ARM_Z_ANGLE] = ModelerControl("Right Arm-Z Angle", -180.0f, 180.0f, 1.0f, -120.0f);
    controls[R_ARM_X_ANGLE] = ModelerControl("Right Arm-X Angle", -180.0f, 180.0f, 1.0f, 0.0f);
    controls[L_HEAR_ANGLE] = ModelerControl("Left Hear Angle", -180.0f, 180.0f, 1.0f, 0.0f);
    controls[R_HEAR_ANGLE] = ModelerControl("Right Hear Angle", -180.0f, 180.0f, 1.0f, 0.0f);
    controls[NECK_X_ANGLE] = ModelerControl("Neck-X Angle", -90.0f, 90.0f, 1.0f, 0.0f);
    controls[NECK_Y_ANGLE] = ModelerControl("Neck-Y Angle", -90.0f, 90.0f, 1.0f, 0.0f);
}

// __CONTROLLER_H__
#endif
