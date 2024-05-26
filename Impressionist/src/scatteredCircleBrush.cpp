//
// scatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "scatteredCircleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>
#include <cstdlib>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
        return;
    }

    const auto alpha = pDoc->getAlpha();
    const auto size = pDoc->getSize();
    const auto scatteredNum = pDoc->getScatteredNum();
    constexpr auto div = 12;
    const auto radius = size / 2.0f;

    SetColorAlpha(source, alpha);
    glBegin(GL_POLYGON);

    for (size_t n = 0; n < scatteredNum; n++) {
        const int cAx = target.x + std::rand() % (2 * size);
        const int cAy = target.y + std::rand() % (2 * size);
        for (size_t i = 0; i < div; i++) {
            const auto Ax = cAx + radius * std::cos(2 * M_PI * i / div);
            const auto Ay = cAy + radius * std::sin(2 * M_PI * i / div);
            glVertex2f(Ax, Ay);
        }
    }
    glEnd();
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
