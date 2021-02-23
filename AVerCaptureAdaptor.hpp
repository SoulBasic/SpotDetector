#pragma once

#ifndef _AVERCAPTURE_ADAPTOR_HPP_
#define _AVERCAPTURE_ADAPTOR_HPP_
#include "Config.hpp"
#include "CaptureAdaptor.hpp"
#include <qt_windows.h>
#include <qdebug.h>

#include "AVerCapAPI_Pro.h"

#pragma comment(lib, "AVerCapAPI.lib")


class AverCaptureAdaptor : public CaptureAdaptor
{
public:
	explicit AverCaptureAdaptor() :
		_hCaptureDevice(nullptr),
		_frame_buffer_size(0),
		_frame_buffer(nullptr),
		_fps(30)
	{

	}
	~AverCaptureAdaptor() 
	{
		if (_frame_buffer != nullptr)
		{
			delete _frame_buffer;
		}
		AVerCaptureVideoSequenceStop(_hCaptureDevice);
		AVerStopStreaming(_hCaptureDevice);
	}
	bool init()
	{
		//初始化
		if (AVerInitialize() != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"采集卡驱动初始化失败");
			return false;
		}
		//列出所有设备
		DWORD dwNum = 0;
		wchar_t wszName[260] = { L'\0' };
		char szName[260] = { '\0' };
		char *pszName = szName;
		if (AVerGetDeviceNum(&dwNum) != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"无法获取采集卡关键信息");
			return false;
		}
		if (dwNum == 0)
		{
			this->setErrorMsg(u8"未检测到可用的采集卡");
			return false;
		}
			
		for (int i = 0; i < dwNum; i++)
		{
			AVerGetDeviceName(i, wszName);
			WideCharToMultiByte(CP_ACP, 0, wszName, -1, pszName, 260, NULL, NULL);
			qDebug("%s\n", pszName);
		}

		if (AVerCreateCaptureObjectEx(0, DEVICETYPE_ALL, NULL, &_hCaptureDevice) != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"创建捕捉对象失败，请检查驱动");
			return false;
		}
		AVerSetVideoSource(_hCaptureDevice, VIDEOSOURCE_COMPOSITE);
		AVerSetVideoFormat(_hCaptureDevice, VIDEOFORMAT_PAL);
		FRAMERATE_RANGE_INFO fr;
		AVerGetVideoInputFrameRateRangeSupported(_hCaptureDevice, VIDEOSOURCE_COMPOSITE, VIDEOFORMAT_ALL, 640, 480, &fr);
		
		VIDEO_RESOLUTION res;
		//设置分辨率
		res.dwVersion = 1;
		res.dwVideoResolution = VIDEORESOLUTION_640X480;
		res.bCustom = FALSE;
		auto ret = AVerSetVideoResolutionEx(_hCaptureDevice, &res);

		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"不支持当前设置的分辨率");
			return false;
		}
		//设置帧率
		ret = AVerSetVideoInputFrameRate(_hCaptureDevice, CAPTURE_FRAMERATE);
		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"不支持当前设置的帧率");
			return false;
		}

		//Preview
		ret = AVerStartStreaming(_hCaptureDevice);
		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"无法开启视频流，请检查驱动");
			return false;
		}
		AVerCaptureSingleImageToBuffer(_hCaptureDevice, NULL, &_frame_buffer_size, false, 1000 / _fps);
		if (_frame_buffer_size == 0)
		{
			this->setErrorMsg(u8"无法获取帧图像，请检查驱动");
			return false;
		}
		_frame_buffer = new BYTE[_frame_buffer_size * 2];
		return true;
	}
	bool getFrame(cv::Mat& frame) override
	{
		if (AVerCaptureSingleImageToBuffer(_hCaptureDevice, _frame_buffer, &_frame_buffer_size, false, 1000 / _fps) != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"无法获取帧图像，请检查驱动");
			return false;
		}

		//将单帧取回的BITMAP存到一个Mat对象中
		BITMAPFILEHEADER* file_header = reinterpret_cast<BITMAPFILEHEADER*>(_frame_buffer);
		BITMAPINFOHEADER* info_header = reinterpret_cast<BITMAPINFOHEADER*>(_frame_buffer + 14);
		LONG w = info_header->biWidth;
		LONG h = info_header->biHeight;
		frame.create(h,w, CV_MAKETYPE(CV_8U, (info_header->biBitCount) / 8));
		frame.data = _frame_buffer + 54;
		return true;
	}
private:
	HANDLE _hCaptureDevice;
	LONG _frame_buffer_size;
	BYTE* _frame_buffer;
	int _fps;
};


#endif