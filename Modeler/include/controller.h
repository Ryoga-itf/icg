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
}

// __CONTROLLER_H__
#endif
