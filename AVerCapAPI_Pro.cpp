#include "qt_windows.h"
#include <tchar.h>
#include "AVerCapAPI_Pro.h"


#ifdef AVER_GOOGLEANALYTIC
extern CGATool	g_GATool;
#endif

class DLLControl
{
public:
	HINSTANCE m_hdll;
	DLLControl();
	~DLLControl();
};
DLLControl::DLLControl():
m_hdll(NULL)
{
	m_hdll=LoadLibrary(_T("AVerCapAPI.dll"));
	if(m_hdll == NULL)  
	{  
		FreeLibrary(m_hdll);    
	} 
}
DLLControl::~DLLControl()
{
	HRESULT hr=FreeLibrary(m_hdll); 
}
DLLControl g_Dllcontrol;

typedef LONG (WINAPI *DLL_AVerInitialize)();
LONG WINAPI AVerInitialize()
{
	DLL_AVerInitialize dll_Fun;
	dll_Fun=(DLL_AVerInitialize)GetProcAddress(g_Dllcontrol.m_hdll,"AVerInitialize");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun();
	return hr;
}typedef LONG (WINAPI *DLL_AVerUninitialize)();

LONG WINAPI AVerUninitialize()
{
	DLL_AVerUninitialize dll_Fun;
	dll_Fun=(DLL_AVerUninitialize)GetProcAddress(g_Dllcontrol.m_hdll,"AVerUninitialize");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun();
	return hr;
}

//Device Control
typedef LONG (WINAPI *DLL_AVerGetDeviceNum)(DWORD*);
LONG WINAPI AVerGetDeviceNum(DWORD *pdwDeviceNum)
{
	DLL_AVerGetDeviceNum dll_Fun;
	dll_Fun=(DLL_AVerGetDeviceNum)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetDeviceNum");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(pdwDeviceNum);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetDeviceType)(DWORD,DWORD*);
LONG WINAPI AVerGetDeviceType(DWORD dwDeviceIndex, DWORD *pdwDeviceType)
{
	DLL_AVerGetDeviceType dll_Fun;
	dll_Fun=(DLL_AVerGetDeviceType)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetDeviceType");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(dwDeviceIndex,pdwDeviceType);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetDeviceName)(DWORD,LPWSTR);
LONG WINAPI AVerGetDeviceName(DWORD dwDeviceIndex, LPWSTR szDeviceName)
{
	DLL_AVerGetDeviceName dll_Fun;
	dll_Fun=(DLL_AVerGetDeviceName)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetDeviceName");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(dwDeviceIndex,szDeviceName);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetDeviceSerialNum)(DWORD,BYTE *);
LONG WINAPI AVerGetDeviceSerialNum(DWORD dwDeviceIndex, BYTE *pbySerialNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetDeviceSerialNum");
#endif
	DLL_AVerGetDeviceSerialNum dll_Fun;
	dll_Fun=(DLL_AVerGetDeviceSerialNum)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetDeviceSerialNum");
	if(dll_Fun==NULL)
	{

		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(dwDeviceIndex,pbySerialNum);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerCreateCaptureObject)(DWORD,HWND,HANDLE *);
LONG WINAPI AVerCreateCaptureObject(DWORD dwDeviceIndex, HWND hWnd, HANDLE *phCaptureObject)
{
	DLL_AVerCreateCaptureObject dll_Fun;
	dll_Fun=(DLL_AVerCreateCaptureObject)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCreateCaptureObject");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(dwDeviceIndex,hWnd,phCaptureObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerCreateCaptureObjectEx)(DWORD,DWORD,HWND,HANDLE*);
LONG WINAPI AVerCreateCaptureObjectEx(DWORD dwDeviceIndex, DWORD dwType, HWND hWnd, HANDLE *phCaptureObject)
{
	DLL_AVerCreateCaptureObjectEx dll_Fun;
	dll_Fun=(DLL_AVerCreateCaptureObjectEx)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCreateCaptureObjectEx");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(dwDeviceIndex,dwType,hWnd,phCaptureObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerDeleteCaptureObject)(HANDLE);
LONG WINAPI AVerDeleteCaptureObject(HANDLE hCaptureObject)
{
	DLL_AVerDeleteCaptureObject dll_Fun;
	dll_Fun=(DLL_AVerDeleteCaptureObject)GetProcAddress(g_Dllcontrol.m_hdll,"AVerDeleteCaptureObject");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetVideoSourceSupported)(HANDLE,DWORD*,DWORD*);
LONG WINAPI AVerGetVideoSourceSupported(HANDLE hCaptureObject,DWORD *pdwSupported, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoSourceSupported");
#endif
	DLL_AVerGetVideoSourceSupported dll_Fun;
	dll_Fun=(DLL_AVerGetVideoSourceSupported)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoSourceSupported");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwSupported,pdwNum);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetVideoSource)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoSource(HANDLE hCaptureObject, DWORD dwVideoSource)
{
#ifdef AVER_GOOGLEANALYTIC
	char *pszVideoSource = NULL;
	switch(dwVideoSource)
	{
	case VIDEOSOURCE_COMPOSITE: pszVideoSource = "Composite"; break;
	case VIDEOSOURCE_SVIDEO: pszVideoSource = "S-Video"; break;
	case VIDEOSOURCE_COMPONENT: pszVideoSource = "Component"; break;
	case VIDEOSOURCE_HDMI: pszVideoSource = "HDMI"; break;
	case VIDEOSOURCE_VGA: pszVideoSource = "VGA"; break;
	case VIDEOSOURCE_SDI: pszVideoSource = "SDI"; break;
	case VIDEOSOURCE_ASI: pszVideoSource = "ASI"; break;
	case VIDEOSOURCE_DVI: pszVideoSource = "DVI"; break;
	}
	g_GATool.PostData("Capture SDK", "AVerSetVideoSource",pszVideoSource);
#endif
	DLL_AVerSetVideoSource dll_Fun;
	dll_Fun=(DLL_AVerSetVideoSource)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoSource");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwVideoSource);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetVideoSource)(HANDLE,DWORD *);
LONG WINAPI AVerGetVideoSource(HANDLE hCaptureObject, DWORD *pdwVideoSource)
{
	DLL_AVerGetVideoSource dll_Fun;
	dll_Fun=(DLL_AVerGetVideoSource)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoSource");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwVideoSource);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetAudioSourceSupportedEx)(HANDLE,DWORD,DWORD *);
LONG WINAPI AVerGetAudioSourceSupportedEx(HANDLE hCaptureObject, DWORD dwVideoSource, DWORD *pdwSupported)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetAudioSourceSupportedEx");
#endif
	DLL_AVerGetAudioSourceSupportedEx dll_Fun;
	dll_Fun=(DLL_AVerGetAudioSourceSupportedEx)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAudioSourceSupportedEx");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwVideoSource,pdwSupported);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetAudioSource)(HANDLE,DWORD);
LONG WINAPI AVerSetAudioSource(HANDLE hCaptureObject, DWORD dwAudioSource)
{
#ifdef AVER_GOOGLEANALYTIC
	char *pszAudioSource = NULL;
	switch(dwAudioSource)
	{
	case AUDIOSOURCE_NONE: pszAudioSource = "None"; break;
	case AUDIOSOURCE_COMPOSITE: pszAudioSource = "Composite"; break;
	case AUDIOSOURCE_SVIDEO: pszAudioSource = "S-Video"; break;
	case AUDIOSOURCE_COMPONENT: pszAudioSource = "Component"; break;
	case AUDIOSOURCE_HDMI: pszAudioSource = "HDMI"; break;
	case AUDIOSOURCE_VGA: pszAudioSource = "VGA"; break;
	case AUDIOSOURCE_SDI: pszAudioSource = "SDI"; break;
	case AUDIOSOURCE_ASI: pszAudioSource = "ASI"; break;
	case AUDIOSOURCE_DVI: pszAudioSource = "DVI"; break;
	case AUDIOSOURCE_DEFAULT: pszAudioSource = "Default"; break;
	}
	g_GATool.PostData("Capture SDK", "AVerSetAudioSource", pszAudioSource);
#endif
	DLL_AVerSetAudioSource dll_Fun;
	dll_Fun=(DLL_AVerSetAudioSource)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetAudioSource");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwAudioSource);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetAudioSource)(HANDLE,DWORD *);
LONG WINAPI AVerGetAudioSource(HANDLE hCaptureObject, DWORD *pdwAudioSource)
{
	DLL_AVerGetAudioSource dll_Fun;
	dll_Fun=(DLL_AVerGetAudioSource)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAudioSource");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwAudioSource);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetVideoFormat)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoFormat(HANDLE hCaptureObject, DWORD dwVideoFormat)
{
#ifdef AVER_GOOGLEANALYTIC
	char *pszVideoFormat = NULL;
	switch(dwVideoFormat)
	{
	case VIDEOFORMAT_NTSC: pszVideoFormat = "NTSC";break;
	case VIDEOFORMAT_PAL: pszVideoFormat = "PAL"; break;
	case VIDEOFORMAT_ALL: pszVideoFormat = "ALL"; break;
	}
	g_GATool.PostData("Capture SDK", "AVerSetVideoFormat", pszVideoFormat);
#endif
	DLL_AVerSetVideoFormat dll_Fun;
	dll_Fun=(DLL_AVerSetVideoFormat)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoFormat");
	if(dll_Fun==NULL)
	{ 
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwVideoFormat);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetVideoFormat)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoFormat(HANDLE hCaptureObject, DWORD *pdwVideoFormat)
{
	DLL_AVerGetVideoFormat dll_Fun;
	dll_Fun = (DLL_AVerGetVideoFormat)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoFormat");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwVideoFormat);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoResolutionRangeSupported)(HANDLE,DWORD,DWORD,RESOLUTION_RANGE_INFO*);
LONG WINAPI AVerGetVideoResolutionRangeSupported(HANDLE hCaptureObject, DWORD dwVideoSource,DWORD dwFormat,RESOLUTION_RANGE_INFO *ResolutionRangeInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoResolutionRangeSupported");
#endif
	DLL_AVerGetVideoResolutionRangeSupported dll_Fun;
	dll_Fun = (DLL_AVerGetVideoResolutionRangeSupported)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoResolutionRangeSupported");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoSource,dwFormat,ResolutionRangeInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoResolutionSupported)(HANDLE,DWORD,DWORD,DWORD *,DWORD *);
LONG WINAPI AVerGetVideoResolutionSupported(HANDLE hCaptureObject,DWORD dwVideoSource,DWORD dwVideoFormat, DWORD *pdwSupported, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoResolutionSupported");
#endif
	DLL_AVerGetVideoResolutionSupported dll_Fun;
	dll_Fun = (DLL_AVerGetVideoResolutionSupported)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoResolutionSupported");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoSource,dwVideoFormat,pdwSupported,pdwNum);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoResolutionEx)(HANDLE , VIDEO_RESOLUTION *);
LONG WINAPI AVerSetVideoResolutionEx(HANDLE hCaptureObject, VIDEO_RESOLUTION *pVideoResolution)
{
#ifdef AVER_GOOGLEANALYTIC
	char szResolution[20] = {0};
	CResolution res = CResolution::Transform(*pVideoResolution);
	sprintf_s(szResolution, 20, "%d*%d", res.m_uiWidth, res.m_uiHeight);
	g_GATool.PostData("Capture SDK", "AVerSetVideoResolutionEx", szResolution);
#endif
	DLL_AVerSetVideoResolutionEx dll_Fun;
	dll_Fun = (DLL_AVerSetVideoResolutionEx)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoResolutionEx");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pVideoResolution);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoResolutionEx)(HANDLE,VIDEO_RESOLUTION*);
LONG WINAPI AVerGetVideoResolutionEx(HANDLE hCaptureObject, VIDEO_RESOLUTION *pVideoResolution)
{
	DLL_AVerGetVideoResolutionEx dll_Fun;
	dll_Fun = (DLL_AVerGetVideoResolutionEx)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoResolutionEx");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pVideoResolution);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoInputFrameRateRangeSupported)(HANDLE , DWORD , DWORD , DWORD , DWORD , FRAMERATE_RANGE_INFO *);
LONG WINAPI AVerGetVideoInputFrameRateRangeSupported(HANDLE hCaptureObject, DWORD dwVideoSource, DWORD dwFormat, DWORD dwWidth, DWORD dwHeight, FRAMERATE_RANGE_INFO *FrameRateRangeInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoInputFrameRateRangeSupported");
#endif
	DLL_AVerGetVideoInputFrameRateRangeSupported dll_Fun;
	dll_Fun = (DLL_AVerGetVideoInputFrameRateRangeSupported)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoInputFrameRateRangeSupported");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoSource,dwFormat,dwWidth,dwHeight,FrameRateRangeInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoInputFrameRateSupportedEx)(HANDLE , DWORD ,DWORD , DWORD , DWORD *, DWORD *);
LONG WINAPI AVerGetVideoInputFrameRateSupportedEx(HANDLE hCaptureObject, DWORD dwVideoSource,DWORD dwVideoFormat, DWORD dwVideoResolution, DWORD *pdwSupported, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoInputFrameRateSupportedEx");
#endif
	DLL_AVerGetVideoInputFrameRateSupportedEx dll_Fun;
	dll_Fun = (DLL_AVerGetVideoInputFrameRateSupportedEx)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoInputFrameRateSupportedEx");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoSource,dwVideoFormat,dwVideoResolution,pdwSupported,pdwNum);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoInputFrameRate)(HANDLE , DWORD );
LONG WINAPI AVerSetVideoInputFrameRate(HANDLE hCaptureObject, DWORD dwFrameRate)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoInputFrameRate", "", dwFrameRate);
#endif
	DLL_AVerSetVideoInputFrameRate dll_Fun;
	dll_Fun = (DLL_AVerSetVideoInputFrameRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoInputFrameRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwFrameRate);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoInputFrameRate)(HANDLE , DWORD *);
LONG WINAPI AVerGetVideoInputFrameRate(HANDLE hCaptureObject, DWORD *pdwFrameRate)
{
	DLL_AVerGetVideoInputFrameRate dll_Fun;
	dll_Fun = (DLL_AVerGetVideoInputFrameRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoInputFrameRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwFrameRate);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetAudioSamplingRateSupported)(HANDLE , DWORD ,DWORD *, DWORD *);
LONG WINAPI AVerGetAudioSamplingRateSupported(HANDLE hCaptureObject, DWORD dwAudioSource,DWORD *pdwSupported, DWORD *pdwNum)
{
	DLL_AVerGetAudioSamplingRateSupported dll_Fun;
	dll_Fun = (DLL_AVerGetAudioSamplingRateSupported)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetAudioSamplingRateSupported");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwAudioSource,pdwSupported,pdwNum);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetAudioSamplingRate)(HANDLE,DWORD);
LONG WINAPI AVerSetAudioSamplingRate(HANDLE hCaptureObject, DWORD dwSamplingRate)
{
	DLL_AVerSetAudioSamplingRate dll_Fun;
	dll_Fun = (DLL_AVerSetAudioSamplingRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetAudioSamplingRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwSamplingRate);
	return hr;
};

typedef LONG (WINAPI *DLL_AVerGetAudioSamplingRate)(HANDLE,DWORD*);
LONG WINAPI AVerGetAudioSamplingRate(HANDLE hCaptureObject, DWORD *pdwSamplingRate)
{
	DLL_AVerGetAudioSamplingRate dll_Fun;
	dll_Fun = (DLL_AVerGetAudioSamplingRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetAudioSamplingRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwSamplingRate);
	return hr;
};

typedef LONG (WINAPI *DLL_AVerStartStreaming)(HANDLE);
LONG WINAPI AVerStartStreaming(HANDLE hCaptureObject)
{
	DLL_AVerStartStreaming dll_Fun;
	dll_Fun = (DLL_AVerStartStreaming)GetProcAddress(g_Dllcontrol.m_hdll, "AVerStartStreaming");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerStopStreaming)(HANDLE);
LONG WINAPI AVerStopStreaming(HANDLE hCaptureObject)
{
	DLL_AVerStopStreaming dll_Fun;
	dll_Fun = (DLL_AVerStopStreaming)GetProcAddress(g_Dllcontrol.m_hdll, "AVerStopStreaming");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetAudioInfo)(HANDLE,INPUT_AUDIO_INFO*);
LONG WINAPI AVerGetAudioInfo(HANDLE hCaptureObject, INPUT_AUDIO_INFO *pAudioInfo)
{
	DLL_AVerGetAudioInfo dll_Fun;
	dll_Fun = (DLL_AVerGetAudioInfo)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetAudioInfo");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pAudioInfo);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoInfo)(HANDLE,INPUT_VIDEO_INFO*);
LONG WINAPI AVerGetVideoInfo(HANDLE hCaptureObject, INPUT_VIDEO_INFO *pVideoInfo)
{
	DLL_AVerGetVideoInfo dll_Fun;
	dll_Fun = (DLL_AVerGetVideoInfo)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoInfo");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pVideoInfo);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetMacroVisionMode)(HANDLE,DWORD*);
LONG WINAPI AVerGetMacroVisionMode(HANDLE hCaptureObject, DWORD *pdwMode)
{
	DLL_AVerGetMacroVisionMode dll_Fun;
	dll_Fun = (DLL_AVerGetMacroVisionMode)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetMacroVisionMode");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwMode);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetSignalPresence)(HANDLE,BOOL*);
LONG WINAPI AVerGetSignalPresence(HANDLE hCaptureObject, BOOL *pbSignalPresence)
{
	DLL_AVerGetSignalPresence dll_Fun;
	dll_Fun = (DLL_AVerGetSignalPresence)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetSignalPresence");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pbSignalPresence);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerEnumThirdPartyAudioCapSource)(HANDLE,AUDIOCAPTURESOURCE_INFO*,DWORD*);
LONG WINAPI AVerEnumThirdPartyAudioCapSource(HANDLE hCaptureObject, AUDIOCAPTURESOURCE_INFO *pAudioCapSourceInfo, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerEnumThirdPartyAudioCapSource");
#endif
	DLL_AVerEnumThirdPartyAudioCapSource dll_Fun;
	dll_Fun = (DLL_AVerEnumThirdPartyAudioCapSource)GetProcAddress(g_Dllcontrol.m_hdll, "AVerEnumThirdPartyAudioCapSource");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pAudioCapSourceInfo,pdwNum);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerEnumThirdPartyAudioCapSourceInputType)(HANDLE,DWORD,AUDIOCAPTURESOURCE_INPUTTYPE_INFO*,DWORD*);
LONG WINAPI AVerEnumThirdPartyAudioCapSourceInputType(HANDLE hCaptureObject, DWORD dwCapIndex, AUDIOCAPTURESOURCE_INPUTTYPE_INFO *pInputTypeInfo, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerEnumThirdPartyAudioCapSourceInputType");
#endif
	DLL_AVerEnumThirdPartyAudioCapSourceInputType dll_Fun;
	dll_Fun = (DLL_AVerEnumThirdPartyAudioCapSourceInputType)GetProcAddress(g_Dllcontrol.m_hdll, "AVerEnumThirdPartyAudioCapSourceInputType");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwCapIndex,pInputTypeInfo,pdwNum);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerEnumThirdPartyAudioCapSourceSampleFormat)(HANDLE,DWORD,AUDIOCAPTURESOURCE_FORMAT_INFO*,DWORD*);
LONG WINAPI AVerEnumThirdPartyAudioCapSourceSampleFormat(HANDLE hCaptureObject, DWORD dwCapIndex, AUDIOCAPTURESOURCE_FORMAT_INFO *pFormatInfo, DWORD *pdwNum)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerEnumThirdPartyAudioCapSourceSampleFormat");
#endif
	DLL_AVerEnumThirdPartyAudioCapSourceSampleFormat dll_Fun;
	dll_Fun = (DLL_AVerEnumThirdPartyAudioCapSourceSampleFormat)GetProcAddress(g_Dllcontrol.m_hdll, "AVerEnumThirdPartyAudioCapSourceSampleFormat");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwCapIndex,pFormatInfo,pdwNum);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetThirdPartyAudioCapSource)(HANDLE,AUDIOCAPTURESOURCE_SETTING*);
LONG WINAPI AVerSetThirdPartyAudioCapSource(HANDLE hCaptureObject, AUDIOCAPTURESOURCE_SETTING *pAudioCapSourceSetting)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetThirdPartyAudioCapSource");
#endif
	DLL_AVerSetThirdPartyAudioCapSource dll_Fun;
	dll_Fun = (DLL_AVerSetThirdPartyAudioCapSource)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetThirdPartyAudioCapSource");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pAudioCapSourceSetting);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetThirdPartyAudioCapSource)(HANDLE,AUDIOCAPTURESOURCE_SETTING*);
LONG WINAPI AVerGetThirdPartyAudioCapSource(HANDLE hCaptureObject, AUDIOCAPTURESOURCE_SETTING *pAudioCapSourceSetting)
{
	DLL_AVerGetThirdPartyAudioCapSource dll_Fun;
	dll_Fun = (DLL_AVerGetThirdPartyAudioCapSource)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetThirdPartyAudioCapSource");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pAudioCapSourceSetting);
	return hr;
};

//Preview Control
typedef LONG (WINAPI *DLL_AVerSetVideoWindowPosition)(HANDLE,RECT);
LONG WINAPI AVerSetVideoWindowPosition(HANDLE hCaptureObject, RECT rectVideoWnd)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoWindowPosition");
#endif
	DLL_AVerSetVideoWindowPosition dll_Fun;
	dll_Fun = (DLL_AVerSetVideoWindowPosition)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoWindowPosition");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,rectVideoWnd);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerRepaintVideo)(HANDLE);
LONG WINAPI AVerRepaintVideo(HANDLE hCaptureObject)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerRepaintVideo");
#endif
	DLL_AVerRepaintVideo dll_Fun;
	dll_Fun = (DLL_AVerRepaintVideo)GetProcAddress(g_Dllcontrol.m_hdll, "AVerRepaintVideo");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetVideoRenderer)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoRenderer(HANDLE hCaptureObject, DWORD dwVideoRenderer)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoRenderer");
#endif
	DLL_AVerSetVideoRenderer dll_Fun;
	dll_Fun = (DLL_AVerSetVideoRenderer)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoRenderer");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoRenderer);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoRenderer)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoRenderer(HANDLE hCaptureObject, DWORD *pdwVideoRenderer)
{
	DLL_AVerGetVideoRenderer dll_Fun;
	dll_Fun = (DLL_AVerGetVideoRenderer)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoRenderer");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwVideoRenderer);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetMaintainAspectRatioEnabled)(HANDLE,BOOL);
LONG WINAPI AVerSetMaintainAspectRatioEnabled(HANDLE hCaptureObject, BOOL bEnabled)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetMaintainAspectRatioEnabled", "TRUE");
#endif
	DLL_AVerSetMaintainAspectRatioEnabled dll_Fun;
	dll_Fun = (DLL_AVerSetMaintainAspectRatioEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetMaintainAspectRatioEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,bEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetMaintainAspectRatioEnabled)(HANDLE,BOOL*);
LONG WINAPI AVerGetMaintainAspectRatioEnabled(HANDLE hCaptureObject, BOOL *pbEnabled)
{
	DLL_AVerGetMaintainAspectRatioEnabled dll_Fun;
	dll_Fun = (DLL_AVerGetMaintainAspectRatioEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetMaintainAspectRatioEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pbEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetAspectRatio)(HANDLE,DWORD*,DWORD*);
LONG WINAPI AVerGetAspectRatio(HANDLE hCaptureObject, DWORD *pdwAspectRatioX, DWORD *pdwAspectRatioY)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetAspectRatio");
#endif
	DLL_AVerGetAspectRatio dll_Fun;
	dll_Fun = (DLL_AVerGetAspectRatio)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetAspectRatio");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwAspectRatioX,pdwAspectRatioY);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetVideoPreviewEnabled)(HANDLE,BOOL);
LONG WINAPI AVerSetVideoPreviewEnabled(HANDLE hCaptureObject, BOOL bEnabled)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoPreviewEnabled", "TRUE");
#endif
	DLL_AVerSetVideoPreviewEnabled dll_Fun;
	dll_Fun = (DLL_AVerSetVideoPreviewEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoPreviewEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,bEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoPreviewEnabled)(HANDLE,BOOL*);
LONG WINAPI AVerGetVideoPreviewEnabled(HANDLE hCaptureObject, BOOL *pbEnabled)
{
	DLL_AVerGetVideoPreviewEnabled dll_Fun;
	dll_Fun = (DLL_AVerGetVideoPreviewEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoPreviewEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pbEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetAudioPreviewEnabled)(HANDLE,BOOL);
LONG WINAPI AVerSetAudioPreviewEnabled(HANDLE hCaptureObject, BOOL bEnabled)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetAudioPreviewEnabled", "TRUE");
#endif
	DLL_AVerSetAudioPreviewEnabled dll_Fun;
	dll_Fun = (DLL_AVerSetAudioPreviewEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetAudioPreviewEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,bEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetAudioPreviewEnabled)(HANDLE,BOOL*);
LONG WINAPI AVerGetAudioPreviewEnabled(HANDLE hCaptureObject, BOOL *pbEnabled)
{
	DLL_AVerGetAudioPreviewEnabled dll_Fun;
	dll_Fun = (DLL_AVerGetAudioPreviewEnabled)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetAudioPreviewEnabled");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pbEnabled);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetVolume)(HANDLE,DWORD,DWORD);
LONG WINAPI AVerSetVolume(HANDLE hCaptureObject, DWORD dwVolumeMode, DWORD dwVolume)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVolume");
#endif
	DLL_AVerSetVolume dll_Fun;
	dll_Fun = (DLL_AVerSetVolume)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVolume");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVolumeMode,dwVolume);
	return hr;
};

typedef LONG (WINAPI *DLL_AVerGetVolume)(HANDLE,DWORD,DWORD*);
LONG WINAPI AVerGetVolume(HANDLE hCaptureObject, DWORD dwVolumeMode, DWORD *pdwVolume)
{
	DLL_AVerGetVolume dll_Fun;
	dll_Fun = (DLL_AVerGetVolume)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVolume");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVolumeMode,pdwVolume);
	return hr;
};


// SW Processor
typedef LONG (WINAPI *DLL_AVerSetVideoProcAmp)(HANDLE,DWORD,DWORD);
LONG WINAPI AVerSetVideoProcAmp(HANDLE hCaptureObject, DWORD dwVideoProcAmpProperty, DWORD dwPropertyValue)
{
	DLL_AVerSetVideoProcAmp dll_Fun;
	dll_Fun = (DLL_AVerSetVideoProcAmp)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoProcAmp");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoProcAmpProperty,dwPropertyValue);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoProcAmp)(HANDLE,DWORD,DWORD*);
LONG WINAPI AVerGetVideoProcAmp(HANDLE hCaptureObject, DWORD dwVideoProcAmpProperty, DWORD *pdwPropertyValue)
{
	DLL_AVerGetVideoProcAmp dll_Fun;
	dll_Fun = (DLL_AVerGetVideoProcAmp)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoProcAmp");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwVideoProcAmpProperty,pdwPropertyValue);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetVideoOutputFrameRate)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoOutputFrameRate(HANDLE hCaptureObject, DWORD dwFrameRate)
{
	DLL_AVerSetVideoOutputFrameRate dll_Fun;
	dll_Fun = (DLL_AVerSetVideoOutputFrameRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerSetVideoOutputFrameRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,dwFrameRate);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerGetVideoOutputFrameRate)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoOutputFrameRate(HANDLE hCaptureObject, DWORD *pdwFrameRate)
{
	DLL_AVerGetVideoOutputFrameRate dll_Fun;
	dll_Fun = (DLL_AVerGetVideoOutputFrameRate)GetProcAddress(g_Dllcontrol.m_hdll, "AVerGetVideoOutputFrameRate");
	if (dll_Fun == NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr = dll_Fun(hCaptureObject,pdwFrameRate);
	return hr;
};
typedef LONG (WINAPI *DLL_AVerSetDeinterlaceMode)(HANDLE,DWORD);
LONG WINAPI AVerSetDeinterlaceMode(HANDLE hCaptureObject, DWORD dwMode)
{	
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetDeinterlaceMode");
#endif
	DLL_AVerSetDeinterlaceMode dll_Fun;
	dll_Fun=(DLL_AVerSetDeinterlaceMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetDeinterlaceMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetDeinterlaceMode)(HANDLE,DWORD*);
LONG WINAPI AVerGetDeinterlaceMode(HANDLE hCaptureObject, DWORD* pdwMode)
{
	DLL_AVerGetDeinterlaceMode dll_Fun;
	dll_Fun=(DLL_AVerGetDeinterlaceMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetDeinterlaceMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwMode); 
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoDownscaleMode)(HANDLE,DWORD,DWORD,DWORD);
LONG WINAPI AVerSetVideoDownscaleMode(HANDLE hCaptureObject, DWORD dwMode, DWORD dwWidth, DWORD dwHeight)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoDownscaleMode");
#endif
	DLL_AVerSetVideoDownscaleMode dll_Fun;
	dll_Fun=(DLL_AVerSetVideoDownscaleMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoDownscaleMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwMode,dwWidth,dwHeight);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoDownscaleMode)(HANDLE,DWORD*,DWORD*,DWORD*);
LONG WINAPI AVerGetVideoDownscaleMode(HANDLE hCaptureObject, DWORD *pdwMode, DWORD *pdwWidth, DWORD *pdwHeight)
{
	DLL_AVerGetVideoDownscaleMode dll_Fun;
	dll_Fun=(DLL_AVerGetVideoDownscaleMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoDownscaleMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwMode,pdwWidth,pdwHeight); 
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetOverlayProperty)(HANDLE,DWORD,OVERLAY_INFO);
LONG WINAPI AVerSetOverlayProperty(HANDLE hCaptureObject, DWORD dwContentType, OVERLAY_INFO OverlayInfo)
{
	DLL_AVerSetOverlayProperty dll_Fun;
	dll_Fun=(DLL_AVerSetOverlayProperty)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetOverlayProperty");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwContentType,OverlayInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetOverlayProperty)(HANDLE,DWORD,OVERLAY_INFO*);
LONG WINAPI AVerGetOverlayProperty(HANDLE hCaptureObject, DWORD dwContentType, OVERLAY_INFO *pOverlayInfo)
{
	DLL_AVerGetOverlayProperty dll_Fun;
	dll_Fun=(DLL_AVerGetOverlayProperty)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetOverlayProperty");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwContentType,pOverlayInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayText)(HANDLE,LPWSTR,DWORD);
LONG WINAPI AVerOverlayText(HANDLE hCaptureObject, LPWSTR lpText, DWORD dwDuration)
{
	DLL_AVerOverlayText dll_Fun;
	dll_Fun=(DLL_AVerOverlayText)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayText");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,lpText,dwDuration);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayTextEx)(HANDLE,CAP_OVERLAY_TEXT_INFO*);
LONG WINAPI AVerOverlayTextEx(HANDLE hCaptureObject, CAP_OVERLAY_TEXT_INFO* pCapOverlayTextInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerOverlayTextEx");
#endif
	DLL_AVerOverlayTextEx dll_Fun;
	dll_Fun=(DLL_AVerOverlayTextEx)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayTextEx");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCapOverlayTextInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayTime)(HANDLE,DWORD,DWORD);
LONG WINAPI AVerOverlayTime(HANDLE hCaptureObject, DWORD dwFormat, DWORD dwDuration)
{
	DLL_AVerOverlayTime dll_Fun;
	dll_Fun=(DLL_AVerOverlayTime)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayTime");
	if(dll_Fun==NULL)
	{ 
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwFormat,dwDuration);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayImage)(HANDLE,OVERLAY_IMAGE_INFO,DWORD);
LONG WINAPI AVerOverlayImage(HANDLE hCaptureObject, OVERLAY_IMAGE_INFO ImageInfo, DWORD dwDuration)
{
	DLL_AVerOverlayImage dll_Fun;
	dll_Fun=(DLL_AVerOverlayImage)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayImage");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,ImageInfo,dwDuration);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayMediaContent)(HANDLE,OVERLAY_CONTENT_INFO*);
LONG WINAPI AVerOverlayMediaContent(HANDLE hCaptureObject, OVERLAY_CONTENT_INFO* pContentInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerOverlayMediaContent");
#endif
	DLL_AVerOverlayMediaContent dll_Fun;
	dll_Fun=(DLL_AVerOverlayMediaContent)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayMediaContent");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pContentInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayDC)(HANDLE,OVERLAY_DC_INFO*);
LONG WINAPI AVerOverlayDC(HANDLE hCaptureObject, OVERLAY_DC_INFO* pOverlayDCInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerOverlayDC");
#endif
	DLL_AVerOverlayDC dll_Fun;
	dll_Fun=(DLL_AVerOverlayDC)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayDC");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pOverlayDCInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetNoiseReductionEnabled)(HANDLE,BOOL);
LONG WINAPI AVerSetNoiseReductionEnabled(HANDLE hCaptureObject, BOOL bEnabled)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetNoiseReductionEnabled");
#endif
	DLL_AVerSetNoiseReductionEnabled dll_Fun;
	dll_Fun=(DLL_AVerSetNoiseReductionEnabled)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetNoiseReductionEnabled");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,bEnabled);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetNoiseReductionEnabled)(HANDLE,BOOL*);
LONG WINAPI AVerGetNoiseReductionEnabled(HANDLE hCaptureObject, BOOL *pbEnabled)
{
	DLL_AVerGetNoiseReductionEnabled dll_Fun;
	dll_Fun=(DLL_AVerGetNoiseReductionEnabled)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetNoiseReductionEnabled");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pbEnabled);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoStreamMixingProperty)(HANDLE,DWORD,VIDEO_STREAM_INFO);
LONG WINAPI AVerSetVideoStreamMixingProperty(HANDLE hCaptureObject, DWORD dwStreamID, VIDEO_STREAM_INFO VideoStreamInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoStreamMixingProperty");
#endif
	DLL_AVerSetVideoStreamMixingProperty dll_Fun;
	dll_Fun=(DLL_AVerSetVideoStreamMixingProperty)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoStreamMixingProperty");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwStreamID,VideoStreamInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoStreamMixingProperty)(HANDLE,DWORD,VIDEO_STREAM_INFO*);
LONG WINAPI AVerGetVideoStreamMixingProperty(HANDLE hCaptureObject, DWORD dwStreamID, VIDEO_STREAM_INFO *pVideoStreamInfo)
{
	DLL_AVerGetVideoStreamMixingProperty dll_Fun;
	dll_Fun=(DLL_AVerGetVideoStreamMixingProperty)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoStreamMixingProperty");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwStreamID,pVideoStreamInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerMixVideoStream)(HANDLE,DWORD,BYTE *,DWORD,LONG,__int64,DWORD);
LONG WINAPI AVerMixVideoStream(HANDLE hCaptureObject, DWORD dwStreamID, BYTE *pData, DWORD dwStride, LONG lLength, __int64 tRefTime, DWORD dwOptions)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerMixVideoStream");
#endif
	DLL_AVerMixVideoStream dll_Fun;
	dll_Fun=(DLL_AVerMixVideoStream)GetProcAddress(g_Dllcontrol.m_hdll,"AVerMixVideoStream");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwStreamID,pData,dwStride,lLength,tRefTime,dwOptions);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoEnhanceMode)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoEnhanceMode(HANDLE hCaptureObject, DWORD dwMode)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoEnhanceMode");
#endif
	DLL_AVerSetVideoEnhanceMode dll_Fun;
	dll_Fun=(DLL_AVerSetVideoEnhanceMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoEnhanceMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoEnhanceMode)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoEnhanceMode(HANDLE hCaptureObject, DWORD *pdwMode)
{
	DLL_AVerGetVideoEnhanceMode dll_Fun;
	dll_Fun=(DLL_AVerGetVideoEnhanceMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoEnhanceMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoClippingRect)(HANDLE,RECT);
LONG WINAPI AVerSetVideoClippingRect(HANDLE hCaptureObject, RECT rcClippingRect)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoClippingRect");
#endif
	DLL_AVerSetVideoClippingRect dll_Fun;
	dll_Fun=(DLL_AVerSetVideoClippingRect)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoClippingRect");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,rcClippingRect);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoClippingRect)(HANDLE,RECT*);
LONG WINAPI AVerGetVideoClippingRect(HANDLE hCaptureObject, RECT *prcClippingRect)
{
	DLL_AVerGetVideoClippingRect dll_Fun;
	dll_Fun=(DLL_AVerGetVideoClippingRect)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoClippingRect");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,prcClippingRect); 
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoMirrorMode)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoMirrorMode(HANDLE hCaptureObject, DWORD dwMode)
{
	DLL_AVerSetVideoMirrorMode dll_Fun;
	dll_Fun=(DLL_AVerSetVideoMirrorMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoMirrorMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoMirrorMode)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoMirrorMode(HANDLE hCaptureObject, DWORD *pdwMode)
{
	DLL_AVerGetVideoMirrorMode dll_Fun;
	dll_Fun=(DLL_AVerGetVideoMirrorMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoMirrorMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoRotateMode)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoRotateMode(HANDLE hCaptureObject, DWORD dwMode)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoRotateMode");
#endif
	DLL_AVerSetVideoRotateMode dll_Fun;
	dll_Fun=(DLL_AVerSetVideoRotateMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoRotateMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoRotateMode)(HANDLE,DWORD*);
LONG WINAPI AVerGetVideoRotateMode(HANDLE hCaptureObject, DWORD *pdwMode)
{
	DLL_AVerGetVideoRotateMode dll_Fun;
	dll_Fun=(DLL_AVerGetVideoRotateMode)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoRotateMode");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwMode);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoUpscaleBlackRect)(HANDLE,RECT);
LONG WINAPI AVerSetVideoUpscaleBlackRect(HANDLE hCaptureObject, RECT rcUpscaleRect)
{
	DLL_AVerSetVideoUpscaleBlackRect dll_Fun;
	dll_Fun=(DLL_AVerSetVideoUpscaleBlackRect)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoUpscaleBlackRect");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,rcUpscaleRect);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoUpscaleBlackRect)(HANDLE,RECT *);
LONG WINAPI AVerGetVideoUpscaleBlackRect(HANDLE hCaptureObject, RECT *prcUpscaleRect)
{
	DLL_AVerGetVideoUpscaleBlackRect dll_Fun;
	dll_Fun=(DLL_AVerGetVideoUpscaleBlackRect)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoUpscaleBlackRect");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,prcUpscaleRect);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerMotionDetection)(HANDLE,MOTION_DETECT_INFO*);
LONG WINAPI AVerMotionDetection(HANDLE hCaptureObject, MOTION_DETECT_INFO *pMotionDetectInfo)
{
	DLL_AVerMotionDetection dll_Fun;
	dll_Fun=(DLL_AVerMotionDetection)GetProcAddress(g_Dllcontrol.m_hdll,"AVerMotionDetection");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pMotionDetectInfo); 
	return hr;
}
typedef LONG (WINAPI *DLL_AVerPauseVideo)(HANDLE,BOOL,DWORD);
LONG WINAPI AVerPauseVideo(HANDLE hCaptureObject, BOOL bPause, DWORD dwOptions)
{
	DLL_AVerPauseVideo dll_Fun;
	dll_Fun=(DLL_AVerPauseVideo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerPauseVideo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,bPause,dwOptions);
	return hr;
}

// Capture Audio
typedef LONG (WINAPI *DLL_AVerCaptureAudioSampleStart)(HANDLE,AUDIOPRCSCALLBACK,LONGPTR);
LONG WINAPI AVerCaptureAudioSampleStart(HANDLE hCaptureObject, AUDIOPRCSCALLBACK lpCallback, LONGPTR lCallbackUserData)
{
	DLL_AVerCaptureAudioSampleStart dll_Fun;
	dll_Fun=(DLL_AVerCaptureAudioSampleStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureAudioSampleStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,lpCallback,lCallbackUserData);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureAudioSampleStartEx)(HANDLE,AUDIO_CAPTURE_INFO);
LONG WINAPI AVerCaptureAudioSampleStartEx(HANDLE hCaptureObject, AUDIO_CAPTURE_INFO CaptureInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerCaptureAudioSampleStartEx");
#endif
	DLL_AVerCaptureAudioSampleStartEx dll_Fun;
	dll_Fun=(DLL_AVerCaptureAudioSampleStartEx)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureAudioSampleStartEx");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,CaptureInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureAudioSampleStop)(HANDLE);
LONG WINAPI AVerCaptureAudioSampleStop(HANDLE hCaptureObject)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerCaptureAudioSampleStartEx");
#endif
	DLL_AVerCaptureAudioSampleStop dll_Fun;
	dll_Fun=(DLL_AVerCaptureAudioSampleStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureAudioSampleStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}


// Capture Image
typedef LONG (WINAPI *DLL_AVerCaptureImageStart)(HANDLE,CAPTURE_IMAGE_INFO*);
LONG WINAPI AVerCaptureImageStart(HANDLE hCaptureObject, CAPTURE_IMAGE_INFO *pCaptureImageInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerCaptureImageStart");
#endif
	DLL_AVerCaptureImageStart dll_Fun;
	dll_Fun=(DLL_AVerCaptureImageStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureImageStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCaptureImageInfo); 
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureImageStop)(HANDLE,DWORD);
LONG WINAPI AVerCaptureImageStop(HANDLE hCaptureObject, DWORD dwImageType)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerCaptureImageStop");
#endif
	DLL_AVerCaptureImageStop dll_Fun;
	dll_Fun=(DLL_AVerCaptureImageStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureImageStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwImageType);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureSingleImage)(HANDLE,CAPTURE_SINGLE_IMAGE_INFO*);
LONG WINAPI AVerCaptureSingleImage(HANDLE hCaptureObject, CAPTURE_SINGLE_IMAGE_INFO *pCaptureSingleImageInfo)
{
	DLL_AVerCaptureSingleImage dll_Fun;
	dll_Fun=(DLL_AVerCaptureSingleImage)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureSingleImage");
	if(dll_Fun==NULL)
	{ 
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCaptureSingleImageInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureSingleImageToBuffer)(HANDLE,BYTE*,LONG*,BOOL,DWORD);
LONG WINAPI AVerCaptureSingleImageToBuffer(HANDLE hCaptureObject, BYTE *lpBmpData, LONG *plBufferSize, BOOL bOverlayMix, DWORD dwTimeout)
{
	DLL_AVerCaptureSingleImageToBuffer dll_Fun;
	dll_Fun=(DLL_AVerCaptureSingleImageToBuffer)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureSingleImageToBuffer");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,lpBmpData,plBufferSize,bOverlayMix,dwTimeout);
	return hr;
}

// Capture Video
typedef LONG (WINAPI *DLL_AVerCaptureVideoSequenceStart)(HANDLE,VIDEO_CAPTURE_INFO);
LONG WINAPI AVerCaptureVideoSequenceStart(HANDLE hCaptureObject, VIDEO_CAPTURE_INFO CaptureInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	char *pszSaveType = NULL;
	switch(CaptureInfo.dwSaveType)
	{
	case ST_AVI: pszSaveType = "avi"; break;
	case ST_MPG: pszSaveType = "mpg"; break;
	case ST_MP4: pszSaveType = "mp4"; break;
	case ST_TS: pszSaveType = "ts"; break;
	case ST_WAV: pszSaveType = "wav"; break;
	case ST_CALLBACK_RGB24:
	case ST_CALLBACK_ARGB:
	case ST_CALLBACK: pszSaveType = "callback video"; break;
	}
	g_GATool.PostData("Capture SDK", "AVerCaptureVideoSequenceStart", pszSaveType);
#endif

	DLL_AVerCaptureVideoSequenceStart dll_Fun;
	dll_Fun=(DLL_AVerCaptureVideoSequenceStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureVideoSequenceStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,CaptureInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureVideoSequenceStop)(HANDLE);
LONG WINAPI AVerCaptureVideoSequenceStop(HANDLE hCaptureObject)
{
	DLL_AVerCaptureVideoSequenceStop dll_Fun;
	dll_Fun=(DLL_AVerCaptureVideoSequenceStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureVideoSequenceStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetAudioRecordEnabled)(HANDLE,BOOL);
LONG WINAPI AVerSetAudioRecordEnabled(HANDLE hCaptureObject, BOOL bEnabled)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetAudioRecordEnabled");
#endif
	DLL_AVerSetAudioRecordEnabled dll_Fun;
	dll_Fun=(DLL_AVerSetAudioRecordEnabled)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetAudioRecordEnabled");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,bEnabled);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetAudioRecordEnabled)(HANDLE,BOOL*);
LONG WINAPI AVerGetAudioRecordEnabled(HANDLE hCaptureObject, BOOL *pbEnabled)
{
	DLL_AVerGetAudioRecordEnabled dll_Fun;
	dll_Fun=(DLL_AVerGetAudioRecordEnabled)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAudioRecordEnabled");
	if(dll_Fun==NULL)
	{ 
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pbEnabled);
	return hr;
}

// Encoder Setting
typedef LONG (WINAPI *DLL_AVerSetMpeg2VideoEncoderInfo)(HANDLE,MPEG2_VIDEOENCODER_INFO*);
LONG WINAPI AVerSetMpeg2VideoEncoderInfo(HANDLE hCaptureObject, MPEG2_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetMpeg2VideoEncoderInfo");
#endif
	DLL_AVerSetMpeg2VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetMpeg2VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetMpeg2VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetMpeg2VideoEncoderInfo)(HANDLE,MPEG2_VIDEOENCODER_INFO*);
LONG WINAPI AVerGetMpeg2VideoEncoderInfo(HANDLE hCaptureObject, MPEG2_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerGetMpeg2VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetMpeg2VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetMpeg2VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetMpeg2AudioEncoderInfo)(HANDLE,MPEG2_AUDIOENCODER_INFO*);
LONG WINAPI AVerSetMpeg2AudioEncoderInfo(HANDLE hCaptureObject, MPEG2_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetMpeg2AudioEncoderInfo");
#endif
	DLL_AVerSetMpeg2AudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetMpeg2AudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetMpeg2AudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetMpeg2AudioEncoderInfo)(HANDLE,MPEG2_AUDIOENCODER_INFO*);
LONG WINAPI AVerGetMpeg2AudioEncoderInfo(HANDLE hCaptureObject, MPEG2_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
	DLL_AVerGetMpeg2AudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetMpeg2AudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetMpeg2AudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetHardwareVideoAccelerationCapabilities)(HANDLE,DWORD*);
LONG WINAPI AVerGetHardwareVideoAccelerationCapabilities(HANDLE hCaptureObject, DWORD *pdwCapabilities)
{
	DLL_AVerGetHardwareVideoAccelerationCapabilities dll_Fun;
	dll_Fun=(DLL_AVerGetHardwareVideoAccelerationCapabilities)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetHardwareVideoAccelerationCapabilities");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwCapabilities);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetMpeg4VideoEncoderInfo)(HANDLE,MPEG4_VIDEOENCODER_INFO*);
LONG WINAPI AVerSetMpeg4VideoEncoderInfo(HANDLE hCaptureObject, MPEG4_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetMpeg4VideoEncoderInfo");
#endif
	DLL_AVerSetMpeg4VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetMpeg4VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetMpeg4VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetMpeg4VideoEncoderInfo)(HANDLE,MPEG4_VIDEOENCODER_INFO*);
LONG WINAPI AVerGetMpeg4VideoEncoderInfo(HANDLE hCaptureObject, MPEG4_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerGetMpeg4VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetMpeg4VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetMpeg4VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetMpeg4AudioEncoderInfo)(HANDLE,MPEG4_AUDIOENCODER_INFO*);
LONG WINAPI AVerSetMpeg4AudioEncoderInfo(HANDLE hCaptureObject, MPEG4_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetMpeg4AudioEncoderInfo");
#endif
	DLL_AVerSetMpeg4AudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetMpeg4AudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetMpeg4AudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetMpeg4AudioEncoderInfo)(HANDLE,MPEG4_AUDIOENCODER_INFO*);
LONG WINAPI AVerGetMpeg4AudioEncoderInfo(HANDLE hCaptureObject, MPEG4_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
	DLL_AVerGetMpeg4AudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetMpeg4AudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetMpeg4AudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}

// HW Encoder Capture Card Setting 
typedef LONG (WINAPI *DLL_AVerHwSetVideoEncoderInfo)(HANDLE,HW_VIDEOENCODER_INFO*);
LONG WINAPI AVerHwSetVideoEncoderInfo(HANDLE hCaptureObject, HW_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerHwSetVideoEncoderInfo");
#endif
	DLL_AVerHwSetVideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerHwSetVideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwSetVideoEncoderInfo");
	if(dll_Fun==NULL)
	{ 
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerHwGetVideoEncoderInfo)(HANDLE,HW_VIDEOENCODER_INFO*);
LONG WINAPI AVerHwGetVideoEncoderInfo(HANDLE hCaptureObject, HW_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerHwGetVideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerHwGetVideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwGetVideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerHwSetAudioEncoderInfo)(HANDLE,HW_AUDIOENCODER_INFO*);
LONG WINAPI AVerHwSetAudioEncoderInfo(HANDLE hCaptureObject, HW_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerHwSetAudioEncoderInfo");
#endif
	DLL_AVerHwSetAudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerHwSetAudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwSetAudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerHwGetAudioEncoderInfo)(HANDLE,HW_AUDIOENCODER_INFO*);
LONG WINAPI AVerHwGetAudioEncoderInfo(HANDLE hCaptureObject, HW_AUDIOENCODER_INFO *pAudioEncoderInfo)
{
	DLL_AVerHwGetAudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerHwGetAudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwGetAudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pAudioEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerHwCaptureStreamStart)(HANDLE,HW_STREAM_CAPTURE_INFO*);
LONG WINAPI AVerHwCaptureStreamStart(HANDLE hCaptureObject, HW_STREAM_CAPTURE_INFO *pCaptureInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerHwCaptureStreamStart");
#endif
	DLL_AVerHwCaptureStreamStart dll_Fun;
	dll_Fun=(DLL_AVerHwCaptureStreamStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwCaptureStreamStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCaptureInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerHwCaptureStreamStop)(HANDLE);
LONG WINAPI AVerHwCaptureStreamStop(HANDLE hCaptureObject)
{
	DLL_AVerHwCaptureStreamStop dll_Fun;
	dll_Fun=(DLL_AVerHwCaptureStreamStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerHwCaptureStreamStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}

// Event Callback 
typedef LONG (WINAPI *DLL_AVerSetEventCallback)(HANDLE,NOTIFYEVENTCALLBACK,DWORD,LPVOID);
LONG WINAPI AVerSetEventCallback(HANDLE hCaptureObject, NOTIFYEVENTCALLBACK lpCallback, DWORD dwOptions, LPVOID lpUserData)
{
	DLL_AVerSetEventCallback dll_Fun;
	dll_Fun=(DLL_AVerSetEventCallback)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetEventCallback");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,lpCallback,dwOptions,lpUserData); 
	return hr;
}

// ASI Input (ex: CD910)
typedef LONG (WINAPI *DLL_AVerTsCaptureStreamStart)(HANDLE,TS_STREAM_CAPTURE_INFO*);
LONG WINAPI AVerTsCaptureStreamStart(HANDLE hCaptureObject, TS_STREAM_CAPTURE_INFO *pCaptureInfo)
{
	DLL_AVerTsCaptureStreamStart dll_Fun;
	dll_Fun=(DLL_AVerTsCaptureStreamStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerTsCaptureStreamStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCaptureInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerTsCaptureStreamStop)(HANDLE);
LONG WINAPI AVerTsCaptureStreamStop(HANDLE hCaptureObject)
{
	DLL_AVerTsCaptureStreamStop dll_Fun;
	dll_Fun=(DLL_AVerTsCaptureStreamStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerTsCaptureStreamStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerTsSetStreamCallback)(HANDLE,TS_STREAM_CALLBACK_INFO*);
LONG WINAPI AVerTsSetStreamCallback(HANDLE hCaptureObject, TS_STREAM_CALLBACK_INFO *pCallbackInfo)
{
	DLL_AVerTsSetStreamCallback dll_Fun;
	dll_Fun=(DLL_AVerTsSetStreamCallback)GetProcAddress(g_Dllcontrol.m_hdll,"AVerTsSetStreamCallback");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pCallbackInfo);
	return hr;
}

//SDI Audio Setting
typedef LONG (WINAPI *DLL_AVerSetEmbeddedAudioChannel)(HANDLE,DWORD);
LONG WINAPI AVerSetEmbeddedAudioChannel(HANDLE hCaptureObject, DWORD dwChannels)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetEmbeddedAudioChannel");
#endif
	DLL_AVerSetEmbeddedAudioChannel dll_Fun;
	dll_Fun=(DLL_AVerSetEmbeddedAudioChannel)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetEmbeddedAudioChannel");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwChannels);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetEmbeddedAudioChannel)(HANDLE,DWORD*);
LONG WINAPI AVerGetEmbeddedAudioChannel(HANDLE hCaptureObject, DWORD *pdwChannels)
{
	DLL_AVerGetEmbeddedAudioChannel dll_Fun;
	dll_Fun=(DLL_AVerGetEmbeddedAudioChannel)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetEmbeddedAudioChannel");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwChannels);
	return hr;
}


typedef LONG (WINAPI *DLL_AVerGetVideoColorAdjustment)(HANDLE,VIDEO_COLOR_ADJUSTMENT*);
LONG WINAPI AVerGetVideoColorAdjustment(HANDLE hCaptureObject, VIDEO_COLOR_ADJUSTMENT *pVideoColorAdjustment)
{
	DLL_AVerGetVideoColorAdjustment dll_Fun;
	dll_Fun=(DLL_AVerGetVideoColorAdjustment)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoColorAdjustment");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoColorAdjustment);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetVideoColorAdjustment)(HANDLE,VIDEO_COLOR_ADJUSTMENT*);
LONG WINAPI AVerSetVideoColorAdjustment(HANDLE hCaptureObject, VIDEO_COLOR_ADJUSTMENT *pVideoColorAdjustment)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetVideoColorAdjustment");
#endif
	DLL_AVerSetVideoColorAdjustment dll_Fun;
	dll_Fun=(DLL_AVerSetVideoColorAdjustment)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoColorAdjustment");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoColorAdjustment);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerOverlayMarquee)(HANDLE,CAP_OVERLAY_MARQUEE_INFO*);
LONG WINAPI AVerOverlayMarquee(HANDLE hCaptureObject, CAP_OVERLAY_MARQUEE_INFO *pVideoColorAdjustment)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerOverlayMarquee");
#endif
	DLL_AVerOverlayMarquee dll_Fun;
	dll_Fun=(DLL_AVerOverlayMarquee)GetProcAddress(g_Dllcontrol.m_hdll,"AVerOverlayMarquee");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoColorAdjustment);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetAudioSpectrumInfo)(HANDLE,SPECTRUM_ANALYZE_INFO *);
LONG WINAPI AVerGetAudioSpectrumInfo(HANDLE hCaptureObject, SPECTRUM_ANALYZE_INFO *pSpectrumInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetAudioSpectrumInfo");
#endif
	DLL_AVerGetAudioSpectrumInfo dll_Fun;
	dll_Fun=(DLL_AVerGetAudioSpectrumInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAudioSpectrumInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pSpectrumInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetAudioLoundnessInfo)(HANDLE,LOUDNESS_ANALYZE_INFO*);
LONG WINAPI AVerGetAudioLoundnessInfo(HANDLE hCaptureObject, LOUDNESS_ANALYZE_INFO *pLoundnessInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetAudioLoundnessInfo");
#endif
	DLL_AVerGetAudioLoundnessInfo dll_Fun;
	dll_Fun=(DLL_AVerGetAudioLoundnessInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAudioLoundnessInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pLoundnessInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerSetEncoderTypeInfo)(HANDLE,ENCODER_TYPE_INFO*);
LONG WINAPI AVerSetEncoderTypeInfo(HANDLE hCaptureObject, ENCODER_TYPE_INFO *pInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetEncoderTypeInfo", "h264+aac");
#endif
	DLL_AVerSetEncoderTypeInfo dll_Fun;
	dll_Fun=(DLL_AVerSetEncoderTypeInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetEncoderTypeInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetEncoderTypeInfo)(HANDLE,ENCODER_TYPE_INFO*);
LONG WINAPI AVerGetEncoderTypeInfo(HANDLE hCaptureObject, ENCODER_TYPE_INFO *pInfo)
{
	DLL_AVerGetEncoderTypeInfo dll_Fun;
	dll_Fun=(DLL_AVerGetEncoderTypeInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetEncoderTypeInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetVideoAccelerationCapabilities)(HANDLE,DWORD,DWORD*);
LONG WINAPI AVerGetVideoAccelerationCapabilities(HANDLE hCaptureObject, DWORD dwVideoEncoderType,DWORD *pdwCapabilities)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerGetVideoAccelerationCapabilities");
#endif

	DLL_AVerGetVideoAccelerationCapabilities dll_Fun;
	dll_Fun=(DLL_AVerGetVideoAccelerationCapabilities)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoAccelerationCapabilities");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwVideoEncoderType,pdwCapabilities);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetH264VideoEncoderInfo)(HANDLE,H264_VIDEOENCODER_INFO*);
LONG WINAPI AVerSetH264VideoEncoderInfo(HANDLE hCaptureObject, H264_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetH264VideoEncoderInfo");
#endif
	DLL_AVerSetH264VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetH264VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetH264VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerGetH264VideoEncoderInfo)(HANDLE,H264_VIDEOENCODER_INFO*);
LONG WINAPI AVerGetH264VideoEncoderInfo(HANDLE hCaptureObject, H264_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerGetH264VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetH264VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetH264VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetH265VideoEncoderInfo)(HANDLE,H265_VIDEOENCODER_INFO*);
LONG WINAPI AVerSetH265VideoEncoderInfo(HANDLE hCaptureObject, H265_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetH265VideoEncoderInfo");
#endif
	DLL_AVerSetH265VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetH265VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetH265VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetH265VideoEncoderInfo)(HANDLE,H265_VIDEOENCODER_INFO*);
LONG WINAPI AVerGetH265VideoEncoderInfo(HANDLE hCaptureObject, H265_VIDEOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerGetH265VideoEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetH265VideoEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetH265VideoEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSetAACAudioEncoderInfo)(HANDLE,AAC_AUDIOENCODER_INFO*);
LONG WINAPI AVerSetAACAudioEncoderInfo(HANDLE hCaptureObject, AAC_AUDIOENCODER_INFO *pVideoEncoderInfo)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerSetAACAudioEncoderInfo");
#endif
	DLL_AVerSetAACAudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerSetAACAudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetAACAudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetAACAudioEncoderInfo)(HANDLE,AAC_AUDIOENCODER_INFO*);
LONG WINAPI AVerGetAACAudioEncoderInfo(HANDLE hCaptureObject, AAC_AUDIOENCODER_INFO *pVideoEncoderInfo)
{
	DLL_AVerGetAACAudioEncoderInfo dll_Fun;
	dll_Fun=(DLL_AVerGetAACAudioEncoderInfo)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetAACAudioEncoderInfo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pVideoEncoderInfo);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerCaptureVideoSequencePause)(HANDLE,DWORD );
LONG WINAPI AVerCaptureVideoSequencePause(HANDLE hCaptureObject,DWORD dwstatus)
{
#ifdef AVER_GOOGLEANALYTIC
	g_GATool.PostData("Capture SDK", "AVerCaptureVideoSequencePause");
#endif
	DLL_AVerCaptureVideoSequencePause dll_Fun;
	dll_Fun=(DLL_AVerCaptureVideoSequencePause)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureVideoSequencePause");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwstatus);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerCaptureSingleImageToDICOM)(HANDLE,LPWSTR);
LONG WINAPI AVerCaptureSingleImageToDICOM(HANDLE hCaptureObject, LPWSTR szDICOMConfigFilePath)
{
	DLL_AVerCaptureSingleImageToDICOM dll_Fun;
	dll_Fun=(DLL_AVerCaptureSingleImageToDICOM)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCaptureSingleImageToDICOM");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,szDICOMConfigFilePath);
	return hr;
}



typedef LONG (WINAPI *DLL_AVerSetVideoColorSpace)(HANDLE,DWORD);
LONG WINAPI AVerSetVideoColorSpace(HANDLE hCaptureObject, DWORD dwColorSpace)
{
	DLL_AVerSetVideoColorSpace dll_Fun;
	dll_Fun=(DLL_AVerSetVideoColorSpace)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSetVideoColorSpace");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwColorSpace);
	return hr;
}


typedef LONG (WINAPI *DLL_AVerGetVideoColorSpace)(HANDLE,DWORD *);
LONG WINAPI AVerGetVideoColorSpace(HANDLE hCaptureObject, DWORD *pdwColorSpace)
{
	DLL_AVerGetVideoColorSpace dll_Fun;
	dll_Fun=(DLL_AVerGetVideoColorSpace)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoColorSpace");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pdwColorSpace);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerGetVideoColorSpaceSupported)(HANDLE,DWORD,DWORD*);
LONG WINAPI AVerGetVideoColorSpaceSupported(HANDLE hCaptureObject, DWORD dwVideoSource, DWORD *pdwSupported)
{
	DLL_AVerGetVideoColorSpaceSupported dll_Fun;
	dll_Fun=(DLL_AVerGetVideoColorSpaceSupported)GetProcAddress(g_Dllcontrol.m_hdll,"AVerGetVideoColorSpaceSupported");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,dwVideoSource,pdwSupported);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerCallbackRawVideoDataStart)(HANDLE,CALLBACK_VIDEO_INFO*);
LONG WINAPI AVerCallbackRawVideoDataStart(HANDLE hCaptureObject, CALLBACK_VIDEO_INFO *pInfo)
{
	DLL_AVerCallbackRawVideoDataStart dll_Fun;
	dll_Fun=(DLL_AVerCallbackRawVideoDataStart)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCallbackRawVideoDataStart");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,pInfo);
	return hr;
}


typedef LONG (WINAPI *DLL_AVerCallbackRawVideoDataStop)(HANDLE);
LONG WINAPI AVerCallbackRawVideoDataStop(HANDLE hCaptureObject)
{
	DLL_AVerCallbackRawVideoDataStop dll_Fun;
	dll_Fun=(DLL_AVerCallbackRawVideoDataStop)GetProcAddress(g_Dllcontrol.m_hdll,"AVerCallbackRawVideoDataStop");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerStartRecordFile)(HANDLE,HANDLE *,LPWSTR);
LONG WINAPI AVerStartRecordFile(HANDLE hCaptureObject,HANDLE *phRecordObject,LPWSTR szRecordConfigFilePath)
{
	DLL_AVerStartRecordFile dll_Fun;
	dll_Fun=(DLL_AVerStartRecordFile)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStartRecordFile");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,phRecordObject,szRecordConfigFilePath);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerPauseRecordFile)(HANDLE,DWORD);
LONG WINAPI AVerPauseRecordFile(HANDLE hRecordObject,DWORD dwstatus)
{
	DLL_AVerPauseRecordFile dll_Fun;
	dll_Fun=(DLL_AVerPauseRecordFile)GetProcAddress(g_Dllcontrol.m_hdll,"AVerPauseRecordFile");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hRecordObject,dwstatus);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerSplitRecordFile)(HANDLE);
LONG WINAPI AVerSplitRecordFile(HANDLE hRecordObject)
{
	DLL_AVerSplitRecordFile dll_Fun;
	dll_Fun=(DLL_AVerSplitRecordFile)GetProcAddress(g_Dllcontrol.m_hdll,"AVerSplitRecordFile");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hRecordObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerStopRecordFile)(HANDLE);
LONG WINAPI AVerStopRecordFile(HANDLE hRecordObject)
{
	DLL_AVerStopRecordFile dll_Fun;
	dll_Fun=(DLL_AVerStopRecordFile)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStopRecordFile");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hRecordObject);
	return hr;
}


typedef LONG (WINAPI *DLL_AVerStartNetStreaming)(HANDLE,HANDLE *,LPWSTR);
LONG WINAPI AVerStartNetStreaming(HANDLE hCaptureObject,HANDLE *phNetStreamingObject,LPWSTR szNetStreamingConfigFilePath)
{
	DLL_AVerStartNetStreaming dll_Fun;
	dll_Fun=(DLL_AVerStartNetStreaming)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStartNetStreaming");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureObject,phNetStreamingObject,szNetStreamingConfigFilePath);
	return hr;
}


typedef LONG (WINAPI *DLL_AVerStopNetStreaming)(HANDLE);
LONG WINAPI AVerStopNetStreaming(HANDLE hNetStreamingObject)
{
	DLL_AVerStopNetStreaming dll_Fun;
	dll_Fun=(DLL_AVerStopNetStreaming)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStopNetStreaming");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hNetStreamingObject);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerNetStreamingGetStatus)(HANDLE,NSStatusType,ULONGLONG *);
LONG WINAPI AVerNetStreamingGetStatus(HANDLE hStreamingObject, NSStatusType eNSStatusType, ULONGLONG *pStatus)
{
	DLL_AVerNetStreamingGetStatus dll_Fun;
	dll_Fun=(DLL_AVerNetStreamingGetStatus)GetProcAddress(g_Dllcontrol.m_hdll,"AVerNetStreamingGetStatus");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hStreamingObject,eNSStatusType,pStatus);
	return hr;
}

typedef LONG (WINAPI *DLL_AVerNetStreamingGetURL)(HANDLE,WCHAR *,DWORD *);
LONG WINAPI AVerNetStreamingGetURL(HANDLE hStreamingObject, WCHAR *pwszURL, DWORD *pdwLength)
{
	DLL_AVerNetStreamingGetURL dll_Fun;
	dll_Fun=(DLL_AVerNetStreamingGetURL)GetProcAddress(g_Dllcontrol.m_hdll,"AVerNetStreamingGetURL");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hStreamingObject,pwszURL,pdwLength);
	return hr;
}


//3D Preview
typedef LONG (WINAPI *DLL_AVerStart3DPreview)(HANDLE,HANDLE,HWND,HANDLE *,LPWSTR);
LONG WINAPI AVerStart3DPreview(HANDLE hCaptureCH1Object,HANDLE hCaptureCH2Object,HWND hWnd,HANDLE *ph3DObject,LPWSTR sz3DConfigFilePath)
{
	DLL_AVerStart3DPreview dll_Fun;
	dll_Fun=(DLL_AVerStart3DPreview)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStart3DPreview");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(hCaptureCH1Object,hCaptureCH2Object,hWnd,ph3DObject,sz3DConfigFilePath);
	return hr;
}
typedef LONG (WINAPI *DLL_AVerStop3DPreview)(HANDLE);
LONG WINAPI AVerStop3DPreview(HANDLE h3DObject)
{
	DLL_AVerStop3DPreview dll_Fun;
	dll_Fun=(DLL_AVerStop3DPreview)GetProcAddress(g_Dllcontrol.m_hdll,"AVerStop3DPreview");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(h3DObject);
	return hr;
}
typedef LONG (WINAPI *DLL_AVer3DWindowSetVideoWindowPosition)(HANDLE,RECT);
LONG WINAPI AVer3DWindowSetVideoWindowPosition(HANDLE h3DObject,RECT rectVideoWnd)
{
	DLL_AVer3DWindowSetVideoWindowPosition dll_Fun;
	dll_Fun=(DLL_AVer3DWindowSetVideoWindowPosition)GetProcAddress(g_Dllcontrol.m_hdll,"AVer3DWindowSetVideoWindowPosition");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(h3DObject,rectVideoWnd);
	return hr;
}
typedef LONG (WINAPI *DLL_AVer3DWindowRepaintVideo)(HANDLE);
LONG WINAPI AVer3DWindowRepaintVideo(HANDLE h3DObject)
{
	DLL_AVer3DWindowRepaintVideo dll_Fun;
	dll_Fun=(DLL_AVer3DWindowRepaintVideo)GetProcAddress(g_Dllcontrol.m_hdll,"AVer3DWindowRepaintVideo");
	if(dll_Fun==NULL)
	{
		return CAP_EC_UNKNOWN_ERROR;
	}
	LONG hr=dll_Fun(h3DObject);
	return hr;
}
