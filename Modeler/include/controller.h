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
    X_POSITION,     // オブジェクトのX座標
    Y_POSITION,     // オブジェクトのY座標
    Z_POSITION,     // オブジェクトのZ座標
    ARM1_ANGLE,     // アーム1の角度
    ARM2_ANGLE,     // アーム2の角度
    ARM3_ANGLE,     // アーム3の角度
    ARM4_ANGLE,     // アーム4の角度
    NUM_CONTROLS,   // コントローラ数（必ず末尾に追加）
};

// コントローラの設定
// （NUM_CONTROLSを除くCONTROLLERS列挙子と１：１に対応付ける）
inline void SetController(ModelerControl *controls) {
    // フレーム番号の制御用スライダ
    controls[FRAME_CONTROLS] = ModelerControl("Frame Number", 0, (float)max_frame_count, 1, 0);

    // オブジェクトのX座標用スライダ
    controls[X_POSITION] = ModelerControl("X-Position", -3.0f, 3.0f, 0.1f, 0.0f);
    // オブジェクトのY座標用スライダ
    controls[Y_POSITION] = ModelerControl("Y-Position", -3.0f, 3.0f, 0.1f, 0.0f);
    // オブジェクトのZ座標用スライダ
    controls[Z_POSITION] = ModelerControl("Z-Position", -3.0f, 3.0f, 0.1f, 0.0f);

    // アームの角度用スライダ
    controls[ARM1_ANGLE] = ModelerControl("Arm1-Angle", -180.0f, 180.0f, 1.0f, 30.0f);
    controls[ARM2_ANGLE] = ModelerControl("Arm2-Angle", -180.0f, 180.0f, 1.0f, 90.0f);
    controls[ARM3_ANGLE] = ModelerControl("Arm3-Angle", -180.0f, 180.0f, 1.0f, -30.0f);
    controls[ARM4_ANGLE] = ModelerControl("Arm4-Angle", -180.0f, 180.0f, 1.0f, 30.0f);
}

// __CONTROLLER_H__
#endif
