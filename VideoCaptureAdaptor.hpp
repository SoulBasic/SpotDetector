#pragma once

#ifndef _VIDEOCAPTURE_ADAPTOR_HPP_
#define _VIDEOCAPTURE_ADAPTOR_HPP_
#include "CaptureAdaptor.hpp"

class VideoCaptureAdaptor : public CaptureAdaptor
{
public:
	explicit VideoCaptureAdaptor(const cv::String& videoFileName):_cv_capture(cv::VideoCapture(videoFileName)){}
	~VideoCaptureAdaptor(){}
	bool init()
	{
		if (!_cv_capture.isOpened())
		{
			this->setErrorMsg(u8"无法打开视频");
			return false;
		}
		return true;
	}
	bool getFrame(cv::Mat& frame) override
	{
		return _cv_capture.read(frame);
	}
private:
	cv::VideoCapture _cv_capture;
};


#endif