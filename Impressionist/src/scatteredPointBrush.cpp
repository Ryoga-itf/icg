//
// scatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "scatteredPointBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <GL/gl.h>
#include <cstdlib>

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("ScatteredPointBrush::BrushMove  document is NULL\n");
        return;
    }

    const auto alpha = pDoc->getAlpha();
    const auto size = pDoc->getSize();
    const auto scatteredNum = pDoc->getScatteredNum();

    SetColorAlpha(source, alpha);
    glPointSize(1.0);
    glBegin(GL_POINTS);

    for (size_t i = 0; i < scatteredNum; i++) {
        const int Ax = target.x - size / 2 + std::rand() % size;
        const int Ay = target.y - size / 2 + std::rand() % size;
        glVertex2i(Ax, Ay);
    }
    glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
