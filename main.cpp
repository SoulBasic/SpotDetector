#include "mainwindow.h"
#include <qwidget.h>
#include <QApplication>
#include <Windows.h>
#include <tchar.h>
#include <direct.h>
void set_automatically_start()//设置开机自启动
{
	HKEY hKey;

	//1、找到系统的启动项  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///打开启动项       
	{
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, _T("SpotDetect"), RRF_RT_REG_SZ, 0, strDir, &nLength);

		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			RegSetValueEx(hKey, _T("SpotDetect"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1) * sizeof(TCHAR));
			RegCloseKey(hKey);
		}
	}

}


int main(int argc, char *argv[])
{
	set_automatically_start();
	_mkdir(LOG_ROOT_PATH);
	_mkdir(LOG_PATH);
	_mkdir(LOG_PICTURE_PATH);
	_mkdir(LOG_VIDEO_PATH);
	
	QApplication a(argc, argv);
    MainWindow w;
	w.showMaximized();
	w.show();
    return a.exec();
}
