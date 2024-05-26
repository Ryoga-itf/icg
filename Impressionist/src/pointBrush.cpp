//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "pointBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

PointBrush::PointBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void PointBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void PointBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    // スライダーつけたあと

    if (pDoc == NULL) {
        printf("PointBrush::BrushMove  document is NULL\n");
        return;
    }

    // SetColorAlpha( source, alpha );
    SetColor(source);
    glBegin(GL_POINTS);
    glVertex2d(target.x, target.y);
    glEnd();
}

void PointBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
