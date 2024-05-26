//
// scatteredBrush.cpp
//
// The implementation of Scattered Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "scatteredBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

ScatteredBrush::ScatteredBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void ScatteredBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void ScatteredBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("ScatteredBrush::BrushMove  document is NULL\n");
        return;
    }

    // SetColorAlpha( source, alpha );
    SetColor(source);
    glBegin(GL_POINTS);
    glVertex2d(target.x, target.y);
    glEnd();
}

void ScatteredBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
