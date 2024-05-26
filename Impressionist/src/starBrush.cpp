//
// starBrush.cpp
//
// The implementation of Star Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "starBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

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

    const auto alpha = pDoc->getAlpha();

    SetColorAlpha(source, alpha);
    glBegin(GL_POINTS);
    glVertex2d(target.x, target.y);
    glEnd();
}

void StarBrush::BrushEnd(const Point source, const Point target) {
    // do nothing so far
    glDisable(GL_BLEND);
}
