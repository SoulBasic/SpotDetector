#pragma once

#ifndef _CAMERACAPTURE_ADAPTOR_HPP_
#define _CAMERACAPTURE_ADAPTOR_HPP_
#include "CaptureAdaptor.hpp"

class CameraCaptureAdaptor : public CaptureAdaptor
{
public:
	CameraCaptureAdaptor(int index = 0) :
		_cv_capture(cv::VideoCapture(index))
	{}
	~CameraCaptureAdaptor()
	{
		_cv_capture.release();
	}
	bool init()
	{
		if (!_cv_capture.isOpened())
		{
			this->setErrorMsg(u8"´ò¿ªÉãÏñÍ·Ê§°Ü");
			return false;
		}
		return true;
	}
	bool getFrame(cv::Mat& frame) override
	{
		if (!_cv_capture.read(frame))
		{
			return false;
		}
		return true;
	}
private:
	bool _valiable;
	cv::VideoCapture _cv_capture;
};


#endif