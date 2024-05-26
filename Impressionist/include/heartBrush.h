//
// heartBrush.h
//
// The header file for Heart Brush.
//

#ifndef HEARTBRUSH_H
#define HEARTBRUSH_H

#include "impBrush.h"

class HeartBrush : public ImpBrush {
  public:
    HeartBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

    void BrushBegin(const Point source, const Point target);
    void BrushMove(const Point source, const Point target);
    void BrushEnd(const Point source, const Point target);
    const char *BrushName(void);
};

#endif
