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
#include <cstdlib>
#include <utility>

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

    void DrawBox(double x1, double y1, double z1, double x2, double y2, double z2) {
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        if (z1 > z2) {
            std::swap(z1, z2);
        }
        const auto w = x2 - x1;
        const auto h = y2 - y1;
        const auto d = z2 - z1;

        glPushMatrix();
        glTranslated(x1, y1, z1);
        drawBox(w, h, d);
        glPopMatrix();
    }

    // 脚
    void DrawLeg(const double size = 0.45, const double height = 2.25) {
        glPushMatrix();
        glTranslated(-size / 2, 0, -size / 2);

        setDiffuseColor(0.44f, 0.45f, 0.47f, 1.0f);
        drawBox(size, height * 0.6666666667, size);

        glTranslated(0, height * 0.6666666667, 0);
        setDiffuseColor(0.584f, 0.784f, 0.785f, 1.0f);
        drawBox(size, height * 0.0444444444, size);

        glTranslated(0, height * 0.0444444444, 0);
        setDiffuseColor(0.914f, 0.910f, 0.851f, 1.0f);
        drawBox(size, height * 0.3333333333, size);

        glPopMatrix();
    }

    void DrawArm(const double size = 0.4, const double length = 2.5) {
        glPushMatrix();
        glTranslated(-size / 2, 0, -size / 2);

        setDiffuseColor(0.914f, 0.910f, 0.851f, 1.0f);
        drawBox(size, length * 0.2857142857, size);
        glTranslated(0, length * 0.2857142857, 0);

        {
            glTranslated(size / 2, 0, size / 2);
            glTranslated(-size * 1.2 / 2, 0, -size * 1.2 / 2);
            setDiffuseColor(0.584f, 0.784f, 0.785f, 1.0f);
            drawBox(size * 1.2, length * 0.0408163265, size * 1.2);
            glTranslated(0, length * 0.0408163265, 0);

            setDiffuseColor(0.44f, 0.45f, 0.47f, 1.0f);
            drawBox(size * 1.2, length * 0.5306122449, size * 1.2);
            glTranslated(0, length * 0.5306122449, 0);

            setDiffuseColor(0.584f, 0.784f, 0.785f, 1.0f);
            drawBox(size * 1.2, length * 0.0408163265, size * 1.2);
            glTranslated(0, length * 0.0408163265, 0);

            glTranslated(size * 1.2 / 2, 0, size * 1.2 / 2);
            glTranslated(-size / 2, 0, -size / 2);
        }

        setDiffuseColor(0.914f, 0.910f, 0.851f, 1.0f);
        drawBox(size, length * 0.1020408163, size);

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

        glTranslated(0, -4, 0);
        {
            glPushMatrix(); // 初期座標系
            setAmbientColor(0.75f, 0.75f, 0.75f);
            setSpecularColor(1.0f, 1.0f, 1.0f);
            setShininess(20.0f);

            // 台を描画
            setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
            glTranslated(-3, 0, -3);
            drawBox(6, 0.3, 6);

            glPopMatrix(); // 初期座標系
        }

        // 脚
        {
            glPushMatrix();
            glTranslated(-0.3, 0, 0);
            DrawLeg();
            glPopMatrix();
        }
        {
            glPushMatrix();
            glTranslated(0.3, 0, 0);
            DrawLeg();
            glPopMatrix();
        }

        {
            glPushMatrix();
            glTranslated(0, 2.2, 0);
            {
                glPushMatrix();
                glRotated(-90, 1, 0, 0);
                setDiffuseColor(0.584f, 0.784f, 0.785f, 1.0f);
                drawCylinder(0.2, 1, 0.8);
                glPopMatrix();
            }
            {
                glPushMatrix();
                glTranslated(0, 0.2, 0);
                glRotated(-90, 1, 0, 0);
                setDiffuseColor(0.44f, 0.45f, 0.47f, 1.0f);
                drawCylinder(1.35, 0.8, 0.3);
                glPopMatrix();
            }

            glTranslated(0, 1.4, 0);

            {
                glPushMatrix();
                glTranslated(-1.2 / 2, -0.2, -0.7 / 2);
                setDiffuseColor(0.820f, 0.851f, 0.863f, 1.0f);
                drawBox(1.2, 2.5, 0.7);
                glPopMatrix();
            }

            glTranslated(0, 1.75, 0);

            // 腕
            {
                glPushMatrix();
                glTranslated(-0.4, 0, 0);
                glRotated(120, 0, 0, 1);
                DrawArm();
                glPopMatrix();
            }
            // 腕
            {
                glPushMatrix();
                glTranslated(0.4, 0, 0);
                glRotated(-120, 0, 0, 1);
                DrawArm();
                glPopMatrix();
            }

            glTranslated(0, 0.5, 0);

            // 首
            {
                glPushMatrix();
                glTranslated(-0.4 / 2, 0, -0.4 / 2);
                drawBox(0.4, 0.3, 0.4);
                glPopMatrix();
            }

            glTranslated(0, 0.3, 0);

            // 顔
            {
                glPushMatrix();
                glTranslated(-2.0 / 2, 0, -1.4 / 2);
                drawBox(2, 1.75, 1.4);
                glPopMatrix();
            }
            glPopMatrix();
        }

        // 描画終了
        EndPaint();
    }
};

// __MODEL_H__
#endif
