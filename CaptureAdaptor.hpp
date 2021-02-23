#pragma once

#ifndef _CAPTURE_ADAPTOR_HPP_
#define _CAPTURE_ADAPTOR_HPP_
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
//数据源适配器基类
class CaptureAdaptor
{
public:
	CaptureAdaptor(){}
	virtual ~CaptureAdaptor(){}
	virtual bool getFrame(cv::Mat& frame) = 0;
	void setErrorMsg(const std::string& str) { _errMsg = str; }
	std::string errorMsg() { return _errMsg; }
private:
	std::string _errMsg;
};


#endif // !_CAPTURE_ADAPTOR_H_


