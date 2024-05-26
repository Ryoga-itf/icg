//
// circleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush
// implementations will look like the file with the different GL primitive
// calls.
//

#include "circleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void CircleBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("CircleBrush::BrushMove  document is NULL\n");
        return;
    }

    constexpr auto div = 12;
    const auto size = pDoc->getSize();
    const auto radius = size / 2.0f;
    // SetColorAlpha( source, alpha );
    SetColor(source);
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < div; i++) {
        const auto Ax = target.x + radius * std::cos(2 * M_PI * i / div);
        const auto Ay = target.y + radius * std::sin(2 * M_PI * i / div);
        glVertex2f(Ax, Ay);
    }
    glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
