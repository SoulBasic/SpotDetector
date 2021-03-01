#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <Winsock2.h>
#include "CaptureAdaptor.hpp"
#include "CameraCaptureAdaptor.hpp"
#include "AVerCaptureAdaptor.hpp"
#include "PictureCaptureAdaptor.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_button_clicked();

    void on_thresh_val_slider_sliderMoved(int position);

    void on_detect_size_slider_sliderMoved(int position);

	void on_target_ver_slider_sliderMoved(int position);

	void on_target_hor_slider_sliderMoved(int position);

	void on_target_angle_slider_sliderMoved(int position);

	void on_target_cell_slider_sliderMoved(int position);

	void on_save_button_clicked();

    void on_pause_button_clicked();

	void on_ellipse_button_clicked();

	void on_target_button_clicked();

    void on_source_camera_triggered();

	void on_source_video_triggered();

	void on_source_stream_triggered();

	void on_source_picture_triggered();

	void on_image_original_triggered();

	void on_image_fill_triggered();

private:
    Ui::MainWindow *ui;
	void resizeEvent(QResizeEvent * event);

};
#endif // MAINWINDOW_H
