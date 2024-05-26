//
// heartBrush.cpp
//
// The implementation of Heart Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "heartBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>

extern float frand();

HeartBrush::HeartBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void HeartBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void HeartBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("HeartBrush::BrushMove  document is NULL\n");
        return;
    }

    constexpr auto div = 50;
    const auto size = pDoc->getSize();
    const auto alpha = pDoc->getAlpha();

    SetColorAlpha(source, alpha);
    glBegin(GL_POLYGON);

    for (int i = 0; i < div; i++) {
        const auto t = 2 * M_PIf * i / div;
        const auto radius = size / 2.0;
        const auto Ax = target.x + radius * std::pow(std::sin(t), 3);
        const auto Ay = target.y + radius * 0.8125f * std::cos(t) - radius * 0.3125f * std::cos(2 * t) -
                        radius * 0.125f * std::cos(3 * t) - radius * 0.0625f * std::cos(4 * t);
        glVertex2f(Ax, Ay);
    }
    glEnd();
}

void HeartBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
