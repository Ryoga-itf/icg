//
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include <algorithm>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "circleBrush.h"
#include "lineBrush.h"
#include "pointBrush.h"
#include "scatteredCircleBrush.h"
#include "scatteredPointBrush.h"
#include "starBrush.h"
#include "triangleBrush.h"

#define DESTROY(p)                                                                                                     \
    {                                                                                                                  \
        if ((p) != NULL) {                                                                                             \
            delete[] p;                                                                                                \
            p = NULL;                                                                                                  \
        }                                                                                                              \
    }

ImpressionistDoc::ImpressionistDoc() {
    // Set NULL image name as init.
    m_imageName[0] = '\0';

    m_nWidth = -1;
    m_ucBitmap = NULL;
    m_ucPainting = NULL;
    m_ucPreviewBackup = NULL;

    // create one instance of each brush
    ImpBrush::c_nBrushCount = NUM_BRUSH_TYPE;
    ImpBrush::c_pBrushes = new ImpBrush *[ImpBrush::c_nBrushCount];

    ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush(this, "Points");
    ImpBrush::c_pBrushes[BRUSH_TRIANGLES] = new TriangleBrush(this, "Triangles");
    ImpBrush::c_pBrushes[BRUSH_CIRCLES] = new CircleBrush(this, "Circles");
    ImpBrush::c_pBrushes[BRUSH_LINES] = new LineBrush(this, "Lines");
    ImpBrush::c_pBrushes[BRUSH_STARS] = new StarBrush(this, "Stars");
    ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS] = new ScatteredPointBrush(this, "Scattered Points");
    ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES] = new ScatteredCircleBrush(this, "Scattered Circles");

    // make one of the brushes current
    m_pCurrentBrush = ImpBrush::c_pBrushes[0];
}

//---------------------------------------------------------
// Set the current UI
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI *ui) { m_pUI = ui; }

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char *ImpressionistDoc::getImageName() { return m_imageName; }

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type) { m_pCurrentBrush = ImpBrush::c_pBrushes[type]; }

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize() { return m_pUI->getSize(); }

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle() { return m_pUI->getAngle(); }

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
float ImpressionistDoc::getAlpha() { return m_pUI->getAlpha(); }

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getScatteredNum() { return m_pUI->getScatteredNum(); }
//
//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) {
    // try to open the image to read
    unsigned char *data;
    int width, height;

    if ((data = readBMP(iname, width, height)) == NULL) {
        fl_alert("Can't load bitmap file");
        return 0;
    }

    // reflect the fact of loading the new image
    m_nWidth = width;
    m_nPaintWidth = width;
    m_nHeight = height;
    m_nPaintHeight = height;

    // release old storage
    delete[] m_ucBitmap;
    delete[] m_ucPainting;
    delete[] m_ucPreviewBackup;

    m_ucBitmap = data;

    // allocate space for draw view
    m_ucPainting = new unsigned char[width * height * 3];
    m_ucPreviewBackup = new unsigned char[width * height * 3];
    memset(m_ucPainting, 0, width * height * 3);

    m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), m_pUI->m_mainWindow->y(), width * 2, height + 25);

    // display it on origView
    m_pUI->m_origView->resizeWindow(width, height);
    m_pUI->m_origView->refresh();

    // refresh paint view as well
    m_pUI->m_paintView->resizeWindow(width, height);
    m_pUI->m_paintView->refresh();

    return 1;
}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) {

    writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

    return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() {

    // Release old storage
    if (m_ucPainting) {
        delete[] m_ucPainting;

        // allocate space for draw view
        m_ucPainting = new unsigned char[m_nPaintWidth * m_nPaintHeight * 3];
        memset(m_ucPainting, 0, m_nPaintWidth * m_nPaintHeight * 3);

        // refresh paint view as well
        m_pUI->m_paintView->refresh();
    }

    return 0;
}

// Apply the filter specified by filter_kernel to the
// each pixel in the source buffer and place the resulting
// pixel in the destination buffer.

// This is called from the UI when the
// "preview" or "apply" button is pressed in the filter dialog.

/*
 *	INPUT:
 *		sourceBuffer:		the original image buffer,
 *		srcBufferWidth:		the width of the image buffer
 *		srcBufferHeight:	the height of the image buffer
 *							the buffer is arranged such that
 *							origImg[3*(row*srcBufferWidth+column)+0],
 *							origImg[3*(row*srcBufferWidth+column)+1],
 *							origImg[3*(row*srcBufferWidth+column)+2]
 *							are R, G, B values for pixel at (column, row).
 *		destBuffer:			the image buffer to put the resulting
 *							image in.  It is always the same size
 *							as the source buffer.
 *
 *      filterKernel:		the 2D filter kernel,
 *		knlWidth:			the width of the kernel
 *		knlHeight:			the height of the kernel
 *
 *		divisor, offset:	each pixel after filtering should be
 *							divided by divisor and then added by offset
 */
void ImpressionistDoc::applyFilter(const unsigned char *sourceBuffer, int srcBufferWidth, int srcBufferHeight,
                                   unsigned char *destBuffer, const double *filterKernel, int knlWidth, int knlHeight,
                                   double divisor, double offset) {
    double bufR, bufB, bufG;
    int i, j, k, l;
    for (i = 0; i < srcBufferWidth; i++) {
        for (j = 0; j < srcBufferHeight; j++) {
            destBuffer[3 * (i + srcBufferWidth * j)] = 0;
            destBuffer[3 * (i + srcBufferWidth * j) + 1] = 0;
            destBuffer[3 * (i + srcBufferWidth * j) + 2] = 0;
        }
    }

    for (i = 2; i < srcBufferWidth - 2; i++) {
        for (j = 2; j < srcBufferHeight - 2; j++) {
            bufR = bufG = bufB = offset;
            for (k = 0; k < knlWidth; k++) {
                for (l = 0; l < knlHeight; l++) {
                    bufR += filterKernel[k + knlWidth * l] *
                            sourceBuffer[3 * (i + k - 2 + srcBufferWidth * (j + l - 2))] / divisor;
                    bufG += filterKernel[k + knlWidth * l] *
                            sourceBuffer[3 * (i + k - 2 + srcBufferWidth * (j + l - 2)) + 1] / divisor;
                    bufB += filterKernel[k + knlWidth * l] *
                            sourceBuffer[3 * (i + k - 2 + srcBufferWidth * (j + l - 2)) + 2] / divisor;
                }
            }

            bufR = std::clamp(bufR, 0.0, 255.0);
            bufG = std::clamp(bufG, 0.0, 255.0);
            bufB = std::clamp(bufB, 0.0, 255.0);

            destBuffer[3 * (i + srcBufferWidth * j)] = (unsigned char)bufR;
            destBuffer[3 * (i + srcBufferWidth * j) + 1] = (unsigned char)bufG;
            destBuffer[3 * (i + srcBufferWidth * j) + 2] = (unsigned char)bufB;
        }
    }
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte *ImpressionistDoc::GetOriginalPixel(int x, int y) {
    if (x < 0)
        x = 0;
    else if (x >= m_nWidth)
        x = m_nWidth - 1;

    if (y < 0)
        y = 0;
    else if (y >= m_nHeight)
        y = m_nHeight - 1;

    return (GLubyte *)(m_ucBitmap + 3 * (y * m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte *ImpressionistDoc::GetOriginalPixel(const Point p) { return GetOriginalPixel(p.x, p.y); }

// ３回目実習　FilterKernel
int ImpressionistDoc::copyImageToCanvas() {
    if (m_ucPainting) {
        // キャンバスのバッファを再確保
        delete[] m_ucPainting;
        m_nPaintWidth = m_nWidth;
        m_nPaintHeight = m_nHeight;
        m_ucPainting = new unsigned char[m_nPaintWidth * m_nPaintHeight * 3];

        // 値をコピー
        memcpy(m_ucPainting, m_ucBitmap, m_nPaintWidth * m_nPaintHeight * 3);
        m_pUI->m_paintView->refresh(); // 再描画
    }
    return 0;
}
