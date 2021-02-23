/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "detectviewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *source_camera;
    QAction *source_video;
    QAction *source_stream;
    QAction *image_original;
    QAction *image_fill;
    QAction *source_picture;
    QWidget *centralwidget;
    DetectViewer *widget;
    QSlider *thresh_val_slider;
    QSlider *detect_size_slider;
    QLabel *label;
    QLabel *label_2;
    QPushButton *start_button;
    QPushButton *pause_button;
    QPushButton *ellipse_button;
    QPushButton *target_button;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(660, 610);
        source_camera = new QAction(MainWindow);
        source_camera->setObjectName(QString::fromUtf8("source_camera"));
        source_camera->setCheckable(true);
        source_camera->setChecked(false);
        source_video = new QAction(MainWindow);
        source_video->setObjectName(QString::fromUtf8("source_video"));
        source_video->setCheckable(true);
        source_video->setEnabled(true);
        source_stream = new QAction(MainWindow);
        source_stream->setObjectName(QString::fromUtf8("source_stream"));
        source_stream->setCheckable(true);
        source_stream->setChecked(true);
        source_stream->setEnabled(true);
        image_original = new QAction(MainWindow);
        image_original->setObjectName(QString::fromUtf8("image_original"));
        image_original->setCheckable(true);
        image_original->setChecked(false);
        image_original->setEnabled(true);
        image_fill = new QAction(MainWindow);
        image_fill->setObjectName(QString::fromUtf8("image_fill"));
        image_fill->setCheckable(true);
        image_fill->setChecked(true);
        image_fill->setEnabled(true);
        source_picture = new QAction(MainWindow);
        source_picture->setObjectName(QString::fromUtf8("source_picture"));
        source_picture->setCheckable(true);
        source_picture->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new DetectViewer(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 80, 640, 480));
        thresh_val_slider = new QSlider(centralwidget);
        thresh_val_slider->setObjectName(QString::fromUtf8("thresh_val_slider"));
        thresh_val_slider->setGeometry(QRect(140, 10, 171, 22));
        thresh_val_slider->setMinimum(0);
        thresh_val_slider->setMaximum(50);
        thresh_val_slider->setValue(35);
        thresh_val_slider->setOrientation(Qt::Horizontal);
        thresh_val_slider->setTickPosition(QSlider::NoTicks);
        detect_size_slider = new QSlider(centralwidget);
        detect_size_slider->setObjectName(QString::fromUtf8("detect_size_slider"));
        detect_size_slider->setGeometry(QRect(140, 40, 171, 22));
        detect_size_slider->setContextMenuPolicy(Qt::DefaultContextMenu);
        detect_size_slider->setValue(50);
        detect_size_slider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 141, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 131, 16));
        start_button = new QPushButton(centralwidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(330, 20, 91, 31));
        pause_button = new QPushButton(centralwidget);
        pause_button->setObjectName(QString::fromUtf8("pause_button"));
        pause_button->setGeometry(QRect(440, 20, 91, 31));
        ellipse_button = new QPushButton(centralwidget);
        ellipse_button->setObjectName(QString::fromUtf8("ellipse_button"));
        ellipse_button->setGeometry(QRect(550, 0, 101, 31));
        target_button = new QPushButton(centralwidget);
        target_button->setObjectName(QString::fromUtf8("target_button"));
        target_button->setGeometry(QRect(550, 40, 101, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 660, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(source_camera);
        menu->addAction(source_video);
        menu->addAction(source_picture);
        menu->addAction(source_stream);
        menu_2->addAction(image_original);
        menu_2->addAction(image_fill);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SpotDetector", nullptr));
        source_camera->setText(QCoreApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264", nullptr));
        source_video->setText(QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221", nullptr));
        source_stream->setText(QCoreApplication::translate("MainWindow", "AverCapture", nullptr));
        image_original->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\346\257\224\344\276\213", nullptr));
        image_fill->setText(QCoreApplication::translate("MainWindow", "\351\223\272\346\273\241", nullptr));
        source_picture->setText(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217", nullptr));
#if QT_CONFIG(tooltip)
        detect_size_slider->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        detect_size_slider->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        label->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\226\221\344\272\256\345\272\246\347\233\221\346\265\213\351\230\210\345\200\274", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\226\221\345\244\247\345\260\217\347\233\221\346\265\213\351\230\210\345\200\274", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\347\233\221\346\265\213", nullptr));
        pause_button->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234\347\233\221\346\265\213", nullptr));
        ellipse_button->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\213\237\345\220\210\346\244\255\345\234\206", nullptr));
        target_button->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\240\207\351\235\266", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
