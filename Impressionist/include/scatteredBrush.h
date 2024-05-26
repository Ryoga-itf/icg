//
// scatteredBrush.h
//
// The header file for Scattered Brush.
//

#ifndef SCATTEREDBRUSH_H
#define SCATTEREDBRUSH_H

#include "impBrush.h"

class ScatteredBrush : public ImpBrush {
  public:
    ScatteredBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

    void BrushBegin(const Point source, const Point target);
    void BrushMove(const Point source, const Point target);
    void BrushEnd(const Point source, const Point target);
    const char *BrushName(void);
};

#endif
