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
		//��ʼ��
		if (AVerInitialize() != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"�ɼ���������ʼ��ʧ��");
			return false;
		}
		//�г������豸
		DWORD dwNum = 0;
		wchar_t wszName[260] = { L'\0' };
		char szName[260] = { '\0' };
		char *pszName = szName;
		if (AVerGetDeviceNum(&dwNum) != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"�޷���ȡ�ɼ����ؼ���Ϣ");
			return false;
		}
		if (dwNum == 0)
		{
			this->setErrorMsg(u8"δ��⵽���õĲɼ���");
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
			this->setErrorMsg(u8"������׽����ʧ�ܣ���������");
			return false;
		}
		AVerSetVideoSource(_hCaptureDevice, VIDEOSOURCE_COMPOSITE);
		AVerSetVideoFormat(_hCaptureDevice, VIDEOFORMAT_PAL);
		FRAMERATE_RANGE_INFO fr;
		AVerGetVideoInputFrameRateRangeSupported(_hCaptureDevice, VIDEOSOURCE_COMPOSITE, VIDEOFORMAT_ALL, 640, 480, &fr);
		
		VIDEO_RESOLUTION res;
		//���÷ֱ���
		res.dwVersion = 1;
		res.dwVideoResolution = VIDEORESOLUTION_640X480;
		res.bCustom = FALSE;
		auto ret = AVerSetVideoResolutionEx(_hCaptureDevice, &res);

		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"��֧�ֵ�ǰ���õķֱ���");
			return false;
		}
		//����֡��
		ret = AVerSetVideoInputFrameRate(_hCaptureDevice, CAPTURE_FRAMERATE);
		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"��֧�ֵ�ǰ���õ�֡��");
			return false;
		}

		//Preview
		ret = AVerStartStreaming(_hCaptureDevice);
		if (ret != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"�޷�������Ƶ������������");
			return false;
		}
		AVerCaptureSingleImageToBuffer(_hCaptureDevice, NULL, &_frame_buffer_size, false, 1000 / _fps);
		if (_frame_buffer_size == 0)
		{
			this->setErrorMsg(u8"�޷���ȡ֡ͼ����������");
			return false;
		}
		_frame_buffer = new BYTE[_frame_buffer_size * 2];
		return true;
	}
	bool getFrame(cv::Mat& frame) override
	{
		if (AVerCaptureSingleImageToBuffer(_hCaptureDevice, _frame_buffer, &_frame_buffer_size, false, 1000 / _fps) != CAP_EC_SUCCESS)
		{
			this->setErrorMsg(u8"�޷���ȡ֡ͼ����������");
			return false;
		}

		//����֡ȡ�ص�BITMAP�浽һ��Mat������
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