#pragma once
#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#define M_PI 3.14159265
#define NOMINMAX

#define CAPTURE_FRAMERATE 2500 //�ɼ���֡��(֡��*100)

#define TARGET_OFFSET_ANGLE -3 //���ƫ�ƽ�
#define MIN_CONTOUR_SIZE 100 //��С���������ֵ
#define REPORT_RATE 2 //ͨ�ű�����(HZ)�����ɴ���25�������׳��ֲ���Ԥ֪����

#define BIND_ADDRESS false //�̶�������ַ(�˴�Ϊfalse�����������ַ�˿ڼ�Ϊ�Զ�����)
#define MASTER_ADDRESS "192.168.1.17" //����IP��ַ(PC)
#define MASTER_PORT 3000//�����˿ں�(PC)

#define SLAVE_ADDRESS "192.168.1.18"//�ӻ�IP��ַ(������)
#define SLAVE_PORT 502//�ӻ��˿ں�(PC)

#define COMM_DEVICE_UNIT 0x01

#define COMM_START_SEQUENCE 0x01 //ͨ��TCP�������кų�ʼֵ

#define COMM_START_ADDRESS_UP 0x01  //ͨ��д��ļĴ����׵�ַ
#define COMM_START_ADDRESS_DOWN 0x00



//ȡ����һ�е�ע�Ϳɴ򿪽�ͼ��¼��
//#define LOG_VIDEOANDPICTURE

#define LOG_ROOT_PATH "D:/SpotDetectStorange/" //��־�����Ŀ¼
#define LOG_PATH "D:/SpotDetectStorange/Log/" //��־����Ŀ¼
#define LOG_PICTURE_PATH "D:/SpotDetectStorange/Picture/" //��־ͼƬĿ¼
#define LOG_VIDEO_PATH "D:/SpotDetectStorange/Video/" //��־��ƵĿ¼

#define LOG_SINGLETIME 1800 //ÿ����־�ļ��ļ�¼ʱ�䣬Ĭ�ϰ�Сʱ��1800s������Ϊһ���ļ�

#define LOG_VIDEO_NAME "%Y-%m-%d %H-%M-%S" //�������־�ļ�����ʽ

#define LOG_EXPIRE_TIME 3600 * 72 //��־����ʱ��(Ĭ��72Сʱ)
#define LOG_EXPIRE_DETECT_TIME 600 //���μ����ڲ����������־���ʱ�䣬Ĭ��10����


#endif // !_CONFIG_HPP_


