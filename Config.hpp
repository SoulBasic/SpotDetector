#pragma once
#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#define M_PI 3.14159265
#define NOMINMAX

#define CAPTURE_FRAMERATE 2500 //采集卡帧率(帧率*100)

#define TARGET_OFFSET_ANGLE -3 //标靶偏移角
#define MIN_CONTOUR_SIZE 100 //最小轮廓检测阈值
#define REPORT_RATE 2 //通信报告率(HZ)，不可大于25，否则易出现不可预知错误

#define BIND_ADDRESS false //固定主机地址(此处为false下面的主机地址端口即为自动分配)
#define MASTER_ADDRESS "192.168.1.17" //主机IP地址(PC)
#define MASTER_PORT 3000//主机端口号(PC)

#define SLAVE_ADDRESS "192.168.1.18"//从机IP地址(触摸屏)
#define SLAVE_PORT 502//从机端口号(PC)

#define COMM_DEVICE_UNIT 0x01

#define COMM_START_SEQUENCE 0x01 //通信TCP连接序列号初始值

#define COMM_START_ADDRESS_UP 0x01  //通信写入的寄存器首地址
#define COMM_START_ADDRESS_DOWN 0x00



//取消下一行的注释可打开截图和录像
//#define LOG_VIDEOANDPICTURE

#define LOG_ROOT_PATH "D:/SpotDetectStorange/" //日志保存根目录
#define LOG_PATH "D:/SpotDetectStorange/Log/" //日志数据目录
#define LOG_PICTURE_PATH "D:/SpotDetectStorange/Picture/" //日志图片目录
#define LOG_VIDEO_PATH "D:/SpotDetectStorange/Video/" //日志视频目录

#define LOG_SINGLETIME 1800 //每个日志文件的记录时间，默认半小时（1800s）保存为一个文件

#define LOG_VIDEO_NAME "%Y-%m-%d %H-%M-%S" //保存的日志文件名格式

#define LOG_EXPIRE_TIME 3600 * 72 //日志过期时间(默认72小时)
#define LOG_EXPIRE_DETECT_TIME 600 //两次检查过期并清理过期日志间隔时间，默认10分钟


#endif // !_CONFIG_HPP_


