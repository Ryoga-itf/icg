//
// starBrush.cpp
//
// The implementation of Star Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "starBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>

extern float frand();

StarBrush::StarBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void StarBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void StarBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("StarBrush::BrushMove  document is NULL\n");
        return;
    }

    constexpr int div = 10;
    const auto size = pDoc->getSize() / 2.0f;
    const auto alpha = pDoc->getAlpha();

    SetColorAlpha(source, alpha);
    glBegin(GL_POLYGON);
    glVertex2d(target.x, target.y);
    for (size_t i = 0; i <= div; i++) {
        const auto radius = size / (i % 2 == 0 ? 0.5f : 1.0f);
        const auto Ax = target.x + radius * std::cos(2 * M_PI * i / div);
        const auto Ay = target.y + radius * std::sin(2 * M_PI * i / div);
        glVertex2f(Ax, Ay);
    }
    glEnd();
}

void StarBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
