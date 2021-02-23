#pragma once

#ifndef _PICTURECAPTURE_ADAPTOR_HPP_
#define _PICTURECAPTURE_ADAPTOR_HPP_
#include "CaptureAdaptor.hpp"

class PictureCaptureAdaptor : public CaptureAdaptor
{
public:
	explicit PictureCaptureAdaptor(const cv::String& pictureFileName):_pic(cv::Mat(cv::imread(pictureFileName))){}
	~PictureCaptureAdaptor()
	{

	}

	bool init()
	{
		if (_pic.empty())
		{
			this->setErrorMsg(u8"ͼ��Ϊ�ջ��޷���");
			return false;
		}
		return true;
	}

	bool getFrame(cv::Mat& frame) override
	{
		if (!frame.empty())
		{
			cvtColor(frame, frame, cv::COLOR_RGB2BGR);
		}
		frame = _pic;
		return true;
	}
private:
	cv::Mat _pic;

};


#endif