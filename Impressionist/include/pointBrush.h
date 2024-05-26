//
// pointBrush.h
//
// The header file for Point Brush.
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "impBrush.h"

class PointBrush : public ImpBrush {
  public:
    PointBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

    void BrushBegin(const Point source, const Point target);
    void BrushMove(const Point source, const Point target);
    void BrushEnd(const Point source, const Point target);
    char *BrushName(void);
};

#endif
