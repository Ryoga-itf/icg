//=============================================================================
// ファイル: model.h
//=============================================================================
// モデルの設定・描画を制御
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

// ヘッダファイルのインクルード
#include "animator.h"
#include "controller.h"
#include "modelerdraw.h"
#include <GL/gl.h>
#include <cmath>

// フレーム番号の最大値
int max_frame_count = 450;

// Modelクラスの定義（ModelerViewクラスを継承）
class Model : public ModelerView {
  private:
    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
    // 第3週課題
    //---------------------------------------------------------------------

    // フレーム番号
    int frame_count;

    //-------------------------------------------------------------------------
    // 制御変数
    //-------------------------------------------------------------------------

    // 〜〜〜変数を追加〜〜〜

    // 時間刻み
    double dt;

    // 重力加速度
    double G;

    // 振り子の長さ
    double r;

    // 振り子の角度
    double angle_prev; // θ(t-dt)
    double angle_curr; // θ(t)
    double angle_next; // θ(t+dt)

    // ボールの位置座標
    Vec3d pos;

    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

  public:
    // コンストラクタ（スーパークラスのコンストラクタを呼び出す）
    Model(int x, int y, int w, int h, char *label) : ModelerView(x, y, w, h, label) {
        // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
        // 第3週課題
        //---------------------------------------------------------------------

        // フレーム番号の初期化
        frame_count = 0;

        //---------------------------------------------------------------------
        // 初期化
        //---------------------------------------------------------------------

        // 〜〜〜変数を初期化〜〜〜

        // 時間刻みを設定
        dt = 0.06;

        // 重力加速度を設定
        G = 9.8;

        // 振り子の長さを設定
        r = 6.0;

        // 振り子の角度を初期化
        angle_prev = angle_curr = angle_next = M_PI / 4.0;

        // ボールの位置座標を初期化
        pos = Vec3d(r * std::sin(angle_next), -r * std::cos(angle_next), 0);

        // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
    }

    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
    // 第3週課題
    //---------------------------------------------------------------------

    // 自動アニメーションの設定
    void SetAutomaticAnimation() {
        //-----------------------------------------------------------------
        // アニメーション
        //-----------------------------------------------------------------

        // 〜〜〜プログラムを記述〜〜〜
        const double k = std::sqrt(G / r);
        angle_next = -angle_prev + 2 * angle_curr - k * k * dt * dt * std::sin(angle_curr);
        angle_prev = angle_curr;
        angle_curr = angle_next;
        pos = Vec3d(r * std::sin(angle_next), -r * std::cos(angle_next), 0);

        //-----------------------------------------------------------------
    }

    // 手動アニメーションの設定
    void SetManualAnimation() {
        //-----------------------------------------------------------------
        // アニメーション
        //-----------------------------------------------------------------

        // 〜〜〜プログラムを記述〜〜〜
        angle_prev = angle_curr;
        angle_curr = angle_next;

        //-----------------------------------------------------------------
    }

    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

    // 描画の前処理
    void BeginPaint() {
        // 半透明処理を有効化
        glEnable(GL_BLEND);
        // 混合方法の指定
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // 描画の後処理
    void EndPaint() {
        // 半透明処理を無効化
        glDisable(GL_BLEND);
    }

    // 片目の描画
    void DrawEye() {
        // 白目の描画
        setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
        drawSphere(0.25);
        // 黒目の描画
        glPushMatrix();
        setDiffuseColor(0.2f, 0.1f, 0.0f, 1.0f);
        glTranslated(0.0, 0.2, 0.0);
        drawSphere(0.1);
        glPopMatrix();
    }

    // オブジェクトの描画
    void draw() {
        // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
        // 第3週課題
        //---------------------------------------------------------------------
        //  自動アニメーションの処理
        if (IsAutomaticAnimation() && frame_count < max_frame_count) {
            // フレーム番号の更新
            SetSliderValue(FRAME_CONTROLS, ++frame_count);
            // 自動アニメーション
            SetAutomaticAnimation();
        }
        // 手動アニメーションの処理
        else {
            // フレーム番号を取得
            frame_count = (int)GetSliderValue(FRAME_CONTROLS);
            // 手動アニメーション
            SetManualAnimation();
        }
        // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

        // スーパークラスの描画メソッドをコール（必須）
        ModelerView::draw();
        ParticleSystem *ps = ModelerApplication::Instance()->GetParticleSystem();
        Mat4f CameraTransforms = ps->getModelViewMatrix();

        // 描画開始
        BeginPaint();

        //---------------------------------------------------------------------
        // オブジェクトを描画
        //---------------------------------------------------------------------

        glPushMatrix(); // 初期座標系を保存

        // 拡散反射光を設定
        setDiffuseColor(0.4f, 0.3f, 0.0f, 1.0f);
        // 環境光を設定
        setAmbientColor(0.5f, 0.5f, 0.5f);
        // 鏡面反射光を設定
        setSpecularColor(1.0f, 1.0f, 1.0f);
        // ハイライトの強さを設定
        setShininess(20.0f);

        drawBox(4, 0.3, 4);    // 台を描画
        glTranslated(2, 0, 2); // 原点を台の中心に移動

        // ステップ１----------------------------------------------

        glRotated(GetSliderValue(ARM1_ANGLE), 1, 0, 0); // 座標系を傾ける
        // 拡散反射光を設定
        setDiffuseColor(0.0f, 0.8f, 0.0f, 1.0f);
        drawBox(0.2, 4, 0.2);  // アーム１の描画
        glTranslated(0, 4, 0); // 原点をアーム１の先端に移動

        // ステップ２----------------------------------------------

        glRotated(GetSliderValue(ARM2_ANGLE), 1, 0, 0); // 座標系を傾ける
        // 拡散反射光を設定
        setDiffuseColor(0.8f, 0.8f, 0.0f, 1.0f);
        drawBox(0.2, 2, 0.2);     // アーム２の描画
        glTranslated(-0.5, 2, 0); // 原点をアーム２の先端に移動

        // ステップ３----------------------------------------------

        glPushMatrix();                                 // 座標系を保存
        glRotated(GetSliderValue(ARM3_ANGLE), 1, 0, 0); // 座標系を傾ける
        // 拡散反射光を設定
        setDiffuseColor(0.8f, 0.0f, 0.0f, 1.0f);
        drawBox(1, 1, 0.2); // アーム３の描画

        // 目の描画
        glTranslated(0.0, 0.0, -0.2f);
        glPushMatrix();
        glTranslated(0.2f, 0.0, 0.0);
        DrawEye();
        glPopMatrix();

        glTranslated(0.8f, 0.0, 0.0);
        DrawEye();

        // ステップ４----------------------------------------------

        glPopMatrix();                                  // 座標系を復元
        glRotated(GetSliderValue(ARM4_ANGLE), 1, 0, 0); // 座標系を傾ける
        // 拡散反射光を設定
        setDiffuseColor(0.0f, 0.0f, 0.8f, 1.0f);
        drawBox(1, 1, 0.2); // アーム４の描画

        glTranslated(0.5, 1, -0.5);
        ps->SpawnParticles(CameraTransforms);

        glPopMatrix(); // 初期座標系を復元

        //---------------------------------------------------------------------

        // glTranslated(posX, posY, 0);
        // drawSphere(0.5);
        // 振り子の軸を描画

        glBegin(GL_LINES);

        glVertex3d(0, 0, 0);

        glVertex3d(pos[0], pos[1], pos[2]);

        glEnd();

        // ボールを描画

        glTranslated(pos[0], pos[1], pos[2]);

        drawSphere(0.5);

        // 描画終了
        EndPaint();
    }
};

// __MODEL_H__
#endif
