//
// triangletBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush
// implementations will look like the file with the different GL primitive
// calls.
//

#include "triangleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc *pDoc, const char *name) : ImpBrush(pDoc, name) {}

void TriangleBrush::BrushBegin(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize((float)size);

    BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target) {
    ImpressionistDoc *pDoc = GetDocument();
    ImpressionistUI *dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("TriangleBrush::BrushMove  document is NULL\n");
        return;
    }

    const auto size = pDoc->getSize();
    const int Ax = target.x - (.5 * size);
    const int Bx = target.x + (.5 * size);
    const int Cx = target.x;
    const int Ay = target.y - (.5 * size);
    const int By = target.y - (.5 * size);
    const int Cy = target.y + (.5 * size);

    // SetColorAlpha( source, alpha );
    SetColor(source);
    glBegin(GL_POLYGON);
    glVertex2i(Ax, Ay);
    glVertex2i(Bx, By);
    glVertex2i(Cx, Cy);
    glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
