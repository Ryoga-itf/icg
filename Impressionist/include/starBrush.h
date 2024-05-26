//
// starBrush.h
//
// The header file for Star Brush.
//

#ifndef STARBRUSH_H
#define STARBRUSH_H

#include "impBrush.h"

class StarBrush : public ImpBrush {
  public:
    StarBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

    void BrushBegin(const Point source, const Point target);
    void BrushMove(const Point source, const Point target);
    void BrushEnd(const Point source, const Point target);
    const char *BrushName(void);
};

#endif
