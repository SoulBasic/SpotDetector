#ifndef DETECTVIEWER_H
#define DETECTVIEWER_H
#include <iostream>
#include "Detector.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <qpainter.h>
#include "VideoCaptureAdaptor.hpp"
#include "PictureCaptureAdaptor.hpp"
#include "CameraCaptureAdaptor.hpp"
#include "CaptureAdaptor.hpp"
#include <QMouseEvent>
#include <qmessagebox.h>

using namespace cv;
class DetectViewer : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit DetectViewer(QWidget *parent = nullptr);
	~DetectViewer();
	inline void setRunning(bool val) { dtcr.setRunning(val); }
	inline Detector* getDetector() { return &dtcr; }

	inline void setFill(bool val) { _isFill = val; }
protected:
    void initializeGL() override;
    void paintGL() override;
	void mouseMoveEvent(QMouseEvent *event);
signals:

private:
	Detector dtcr;
	bool _isFill;
};

#endif // DETECTVIEWER_H
