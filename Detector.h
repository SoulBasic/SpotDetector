#pragma once

#ifndef _DETECTOR_H_
#define _DETECTOR_H_

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <WinSock2.h>
#include <qt_windows.h>
#include <io.h>
#include <atomic>
#include <thread>
#include <memory>
#include <string>
#include <algorithm>
#include <tchar.h>
#include <chrono>
#include <vector>
#include "Config.hpp"
#include "CameraCaptureAdaptor.hpp"
#include "VideoCaptureAdaptor.hpp"
#include "AVerCaptureAdaptor.hpp"
#include "PictureCaptureAdaptor.hpp"

using namespace cv;


#pragma comment(lib, "ws2_32.lib")

struct Line2d
{
	Point2d first;
	Point2d second;
	Line2d(){}
	Line2d(double firstx, double firsty, double secondx, double secondy) :first(Point2d(firstx, firsty)), second(Point2d(secondx, secondy)) {}
};

class Detector
{
public:
	Detector(int threshVal, int minArea);
	~Detector();
	
	void setAdaptor(std::shared_ptr<CaptureAdaptor> adaptor);//设置数据源适配器
	void process(Mat& srcImg);//光斑识别算法
	void draw_target(Mat& srcImg);//标靶绘制
	Mat& frame();//通用取帧接口
	bool initPLC();//网口通信初始化
	bool calcXOR(std::string& cmd);//校验位计算
	void stoa_hex(short src, char* dest);//2字节整数转16位字符串
	void setMousePos(Point2d p) { _center = p; }
	inline void setThreshVal(int val) { _threshVal = val; }//threshVal是光斑亮度检测阈值
	inline void setMinArea(int val) { _minArea = val; }//MinArea是光斑大小检测阈值

	void setVerOffset(float val) { _target_ver_offset = val; calc_target(); }
	void setHorOffset(float val) { _target_hor_offset = val; calc_target(); }
	void setCellExpandPara(float val) { _cell_expand_para = val; calc_target(); }
	void setOffsetAngle(int val) { _target_offset_angle = val; calc_target(); }

	inline float verOffset() { return _target_ver_offset; }
	inline float horOffset() { return _target_hor_offset; }
	inline float cellExpandPara() { return _cell_expand_para; }
	inline int offsetAngle() { return _target_offset_angle; }

	inline bool ellipseVisible() { return _show_ellipse; }
	inline bool targetVisible() { return _show_target; }
	inline void showTarget(bool val) { _show_target = val; }//显示标靶
	inline void showEllipse(bool val) { _show_ellipse = val; }//显示椭圆
	inline void setRunning(bool val) { _running = val; }//检测开关
	inline Point2i getOffset() const { return _offset; }//取偏移坐标
private:
	void timeThread();//帧率计算、通信处理线程
	void send_modbus_packet();//发送当前的坐标信息到触摸屏
	std::string get_time_string(time_t stamp, bool is_file_name);
	void clearThread();
	int getFiles(const char *path, std::vector<std::string>& arr, time_t now);
	void calc_target();
	void pointRotate(Point2d& point, Point2d& pivot, int angle);//点旋转算法
	void lineRotate(Line2d& line,Point2d& pivot, int angle);//线旋转算法
	double getDistance(Point2f P, Point2f A, Point2f B);//点线距算法
	std::shared_ptr<CaptureAdaptor> _captureAdaptor;
	CvVideoWriter* _frame_writer;
	FILE* _log_file;
	SOCKET _csock;
	Mat _frame_cache;
	Mat _frame_write_cache;
	Point2i _offset;
	Point2d _center;
	Point2d _abs_center;
	Line2d _hor;
	Line2d _ver;
	time_t _log_checktime;
	time_t _now_time;
	float _target_ver_offset;
	float _target_hor_offset;
	float _cell_expand_para;
	int _target_offset_angle;
	int _cell_length;
	int _threshVal;
	int _minArea;
	int _frame_count;
	int _fps;
	short _seq_modbus;
	bool _running;
	bool _show_ellipse;
	bool _show_target;
	bool _history_read;
	int _ret;
	char _recvBuf[256] = {};
};
#endif // !_DETECTOR_H_
