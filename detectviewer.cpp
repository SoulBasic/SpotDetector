#include "detectviewer.h"

DetectViewer::DetectViewer(QWidget *parent) :
	QOpenGLWidget{ parent },
	dtcr(Detector(235, 15)),
	_isFill(true)
{

}

DetectViewer::~DetectViewer()
{
}



void DetectViewer::initializeGL()
{
	if (!dtcr.initPLC())
	{
#ifdef _DEBUG
		qDebug("%s", "�޷���ʼ��ͨ��ģ��");
#endif // _DEBUG

		QMessageBox::information(nullptr, "error", u8"�޷���ʼ��ͨ��ģ�飬�����봥��������������", QMessageBox::Ok, QMessageBox::Ok);
	}

	auto adaptor = std::make_shared<AverCaptureAdaptor>();//��ʼ��һ��Aver�ɼ�����Ƶ������
	if (!adaptor->init())//�ɼ�����ʼ��
	{
#ifdef _DEBUG
		qDebug("%s", adaptor->errorMsg().c_str());
#endif // _DEBUG
	}
	dtcr.setAdaptor(adaptor);//���ɼ������������õ�̽���������
	dtcr.setRunning(true);

}

void DetectViewer::paintGL()
{
	update();
	Mat& frame = dtcr.frame();
	if (frame.empty())return;
	cvtColor(frame, frame, COLOR_BGR2RGB);
	QImage qframe = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	if (_isFill)
	{
		qframe = qframe.scaled(this->size());
	}
	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), qframe);
	painter.end();

}


void DetectViewer::mouseMoveEvent(QMouseEvent * event)
{
	QPoint p = event->pos();
	float x = p.x();
	float y = p.y();
	Point2f temp{ x,y };
	dtcr.setMousePos(temp);
}


