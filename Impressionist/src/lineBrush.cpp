//
// lineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "lineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void LineBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("LineBrush::BrushMove  document is NULL\n");
        return;
    }

    const auto size = pDoc->getSize();
    const auto angle = pDoc->getAngle();
    const float Ax = target.x + size * std::cos(M_PI * angle / 180);
    const float Ay = target.y + size * std::sin(M_PI * angle / 180);
    const float Bx = target.x - size * std::cos(M_PI * angle / 180);
    const float By = target.y - size * std::sin(M_PI * angle / 180);

    const auto alpha = pDoc->getAlpha();
    SetColorAlpha(source, alpha);
    glBegin(GL_LINES);
    glVertex2f(Ax, Ay);
    glVertex2f(Bx, By);
    glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
