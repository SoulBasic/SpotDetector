#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_button_clicked()
{
	this->ui->widget->setRunning(true);
}

void MainWindow::on_thresh_val_slider_sliderMoved(int position)
{
	double val = 205 + position;

	this->ui->widget->getDetector()->setThreshVal(val);
}

void MainWindow::on_detect_size_slider_sliderMoved(int position)
{
	this->ui->widget->getDetector()->setMinArea(position >> 1);
}

void MainWindow::on_target_ver_slider_sliderMoved(int position)
{
	float val = 0.45 + position * 0.001;
	this->ui->widget->getDetector()->setVerOffset(val);
}

void MainWindow::on_target_hor_slider_sliderMoved(int position)
{
	float val = 0.45 + position * 0.001;
	this->ui->widget->getDetector()->setHorOffset(val);
}

void MainWindow::on_target_angle_slider_sliderMoved(int position)
{
	this->ui->widget->getDetector()->setOffsetAngle(position/5 - 10);
}

void MainWindow::on_target_cell_slider_sliderMoved(int position)
{
	float val = 0.05 + position * 0.0004;
	this->ui->widget->getDetector()->setCellExpandPara(val);
}

void MainWindow::on_save_button_clicked()
{
	FILE* target = fopen("target_config.ini", "wt+");
	if (target != nullptr)
	{
		fprintf(target, "target_ver_offset=%f\ntarget_hor_offset=%f\ntarget_offset_angle=%d\ncell_expand_para=%f", 
			this->ui->widget->getDetector()->verOffset(), this->ui->widget->getDetector()->horOffset(), 
			this->ui->widget->getDetector()->offsetAngle(), this->ui->widget->getDetector()->cellExpandPara());
		fclose(target);
		QMessageBox::information(this, u8"信息", u8"保存成功", QMessageBox::Ok, QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(this, u8"信息", u8"保存失败", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void MainWindow::on_pause_button_clicked()
{
	this->ui->widget->setRunning(false);
}

void MainWindow::on_ellipse_button_clicked()
{
	auto dt = this->ui->widget->getDetector();
	dt->showEllipse(!dt->ellipseVisible());
}

void MainWindow::on_target_button_clicked()
{
	auto dt = this->ui->widget->getDetector();
	dt->showTarget(!dt->targetVisible());
}


void MainWindow::on_source_camera_triggered()
{
	if (!this->ui->source_camera->isChecked())
	{
		this->ui->source_camera->setChecked(true);
		return;
	}
	else
	{
		this->ui->source_camera->setChecked(false);
	}
	auto adaptor = std::make_shared<CameraCaptureAdaptor>(0);
	if (!adaptor->init())
	{
		QMessageBox::information(this, u8"切换数据源失败", QString(adaptor->errorMsg().c_str()), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	this->ui->widget->getDetector()->setAdaptor(adaptor);

	this->ui->source_camera->setChecked(true);
	this->ui->source_picture->setChecked(false);
	this->ui->source_video->setChecked(false);
	this->ui->source_stream->setChecked(false);
}

void MainWindow::on_source_video_triggered()
{
	if (!this->ui->source_video->isChecked())
	{
		this->ui->source_video->setChecked(true);
		return;
	}
	else
	{
		this->ui->source_video->setChecked(false);
	}
	QString fileName = QFileDialog::getOpenFileName(this, u8"打开视频源", ".",
		"AVI(*.avi);;MP4(*.mp4);;All Files(*.*)");
	if (fileName == "")
	{
		QMessageBox::information(NULL, u8"错误", u8"请选择正确的视频文件", QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	auto adaptor = std::make_shared<VideoCaptureAdaptor>(fileName.toStdString());
	if (!adaptor->init())
	{
		QMessageBox::information(this, u8"切换数据源失败", QString(adaptor->errorMsg().c_str()), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	this->ui->widget->getDetector()->setAdaptor(adaptor);

	this->ui->source_video->setChecked(true);
	this->ui->source_camera->setChecked(false);
	this->ui->source_picture->setChecked(false);
	this->ui->source_stream->setChecked(false);
}

void MainWindow::on_source_stream_triggered()
{
	if (!this->ui->source_stream->isChecked())
	{
		this->ui->source_stream->setChecked(true);
		return;
	}
	else
	{
		this->ui->source_stream->setChecked(false);
	}

	auto adaptor = std::make_shared<AverCaptureAdaptor>();
	if (!adaptor->init())
	{
		QMessageBox::information(this, u8"切换数据源失败", QString(adaptor->errorMsg().c_str()), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	this->ui->widget->getDetector()->setAdaptor(adaptor);

	this->ui->source_stream->setChecked(true);
	this->ui->source_camera->setChecked(false);
	this->ui->source_picture->setChecked(false);
	this->ui->source_video->setChecked(false);
}

void MainWindow::on_source_picture_triggered()
{
	if (!this->ui->source_picture->isChecked())
	{
		this->ui->source_picture->setChecked(true);
		return;
	}
	else
	{
		this->ui->source_picture->setChecked(false);
	}

	QString fileName = QFileDialog::getOpenFileName(this, u8"打开图像源", ".",
		"PNG(*.png);;JPG(*.jpg);;BMP(*.bmp);;All Files(*.*)");
	if (fileName == "")
	{
		QMessageBox::information(NULL, u8"错误", u8"请选择正确的图像文件", QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	auto adaptor = std::make_shared<PictureCaptureAdaptor>(fileName.toStdString());
	if (!adaptor->init())
	{
		QMessageBox::information(this, u8"切换数据源失败", QString(adaptor->errorMsg().c_str()), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	this->ui->widget->getDetector()->setAdaptor(adaptor);

	this->ui->source_picture->setChecked(true);
	this->ui->source_camera->setChecked(false);
	this->ui->source_video->setChecked(false);
	this->ui->source_stream->setChecked(false);
}
void MainWindow::on_image_original_triggered()
{
	if (!this->ui->image_original->isChecked())
	{
		this->ui->image_original->setChecked(true);
		return;
	}
	else
	{
		this->ui->image_original->setChecked(false);
	}

	this->ui->widget->setFill(false);

	this->ui->image_original->setChecked(true);
	this->ui->image_fill->setChecked(false);

}
void MainWindow::on_image_fill_triggered()
{
	if (!this->ui->image_fill->isChecked())
	{
		this->ui->image_fill->setChecked(true);
		return;
	}
	else
	{
		this->ui->image_fill->setChecked(false);
	}

	this->ui->widget->setFill(true);

	this->ui->image_fill->setChecked(true);
	this->ui->image_original->setChecked(false);
}


void MainWindow::resizeEvent(QResizeEvent * event)
{
	QSize sz = this->size();
	this->ui->widget->resize({ sz.width() - 20,sz.height() - 100 });
}


