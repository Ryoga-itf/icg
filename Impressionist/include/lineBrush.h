//
// lineBrush.h
//
// The header file for Line Brush.
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "impBrush.h"

class LineBrush : public ImpBrush {
  public:
    LineBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

    void BrushBegin(const Point source, const Point target);
    void BrushMove(const Point source, const Point target);
    void BrushEnd(const Point source, const Point target);
    const char *BrushName(void);
};

#endif
