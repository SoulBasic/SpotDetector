#include "Detector.h"


Detector::Detector(int threshVal, int minArea = 110) :
	_threshVal(threshVal),
    _minArea(minArea),
	_running(true),
	_frame_count(0),
	_fps(0),
	_show_ellipse(false),
	_show_target(true),
	_captureAdaptor(nullptr),
	_frame_writer(nullptr),
	_log_file(nullptr),
	_log_checktime(0),
	_offset({0,0}),
	_abs_center({0,0}),
	_cell_length(0),
	_seq_modbus(COMM_START_SEQUENCE),
	_csock(INVALID_SOCKET),
	_ret(0)
{

	std::thread tt(std::bind(&Detector::timeThread, this));
	tt.detach();
	std::thread ct(std::bind(&Detector::clearThread, this));
	ct.detach();
	

}

Detector::~Detector()
{
	if (_frame_writer != nullptr)
	{
		cvReleaseVideoWriter(&_frame_writer);
	}

	if (_csock != INVALID_SOCKET)
	{
		closesocket(_csock);
	}
	WSACleanup();
}


void Detector::timeThread()
{
	MSG msg;
	SetTimer(NULL, 0, 1000/ REPORT_RATE, NULL);

	while (int a = GetMessage(&msg, NULL, 0, 0) && _running)
	{
		if (a != -1 && msg.message == WM_TIMER)
		{
			_fps = _frame_count * 5;
			_frame_count = 0;
			send_modbus_packet();

#ifdef LOG_VIDEOANDPICTURE
			imwrite((LOG_PICTURE_PATH + get_time_string(_now_time, true) + ".jpg"), _frame_write_cache);
#endif

			if (_log_file != nullptr)
			{
				fprintf(
					_log_file,
					"[LOG][%s]offset_x = %d offset_y = %d abs_x = %d abs_y = %d\n",
					get_time_string(_now_time, false).c_str(),
					_offset.x,
					_offset.y,
					_offset.x + 50,
					50 - _offset.y);
			}
			
		}
	}
}






void Detector::send_modbus_packet()
{
	if (INVALID_SOCKET == _csock)
	{
		return;
	}
	//组织二进制Modbus协议报文
	unsigned char sendBuf[21];
	short temps = _seq_modbus++;
	unsigned char* temp = reinterpret_cast<unsigned char*>(&temps);
	sendBuf[0] = *(temp+1);//前两位为传输标志，2个字节的序列号
	sendBuf[1] = *(temp);
	sendBuf[2] = 0;//协议标志，两个字节，0000为Modbus TCP协议
	sendBuf[3] = 0;
	sendBuf[4] = 0;//长度字段（前半部分字节）
	sendBuf[5] = 15;//随后字节数
	sendBuf[6] = COMM_DEVICE_UNIT;//单元标志，定义连接目的节点的其他设备
	sendBuf[7] = 0x10;//Modbus功能码 写多个保持寄存器操作
	sendBuf[8] = COMM_START_ADDRESS_UP; //写寄存器起始地址高字节
	sendBuf[9] = COMM_START_ADDRESS_DOWN; //写寄存器起始地址低字节

	sendBuf[10] = 0x00; //写寄存器数量高字节
	sendBuf[11] = 0x04; //写寄存器数量低字节
	sendBuf[12] = 0x08; //数据长度
	
	//写四个值到报文中
	temps = _offset.x;
	sendBuf[13] = *(temp+1);
	sendBuf[14] = *(temp);

	temps = _offset.y;
	sendBuf[15] = *(temp+1);
	sendBuf[16] = *(temp);


	temps = _offset.x + 50;
	sendBuf[17] = *(temp+1);
	sendBuf[18] = *(temp);

	temps = 50 - _offset.y;
	sendBuf[19] = *(temp+1);
	sendBuf[20] = *(temp);
	// ----------------


	send(_csock, reinterpret_cast<char*>(sendBuf), sizeof(sendBuf), 0);//发送报文
	int ret = recv(_csock, _recvBuf, sizeof(_recvBuf), 0);//接收响应报文

	_ret = ret;
#ifdef _DEBUG
	qDebug("ret = %d", ret);
	for (int i = 0; i < ret; i++)
	{
		printf("%d ", _recvBuf[i]);
	}
	printf("\n");
#endif // _DEBUG

}

std::string Detector::get_time_string(time_t timestamp, bool is_file_name)
{
	if (timestamp < 0)return "";
	struct tm tm;
	char s[40];
	tm = *localtime(&timestamp);
	if (is_file_name)
	{
		strftime(s, sizeof(s), LOG_VIDEO_NAME, &tm);
	}
	else
	{
		strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
	}

	std::string str(s);
	return str;
}

void Detector::clearThread()
{
	while (_running)
	{
		std::vector<std::string> vec;
		time_t now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		getFiles(LOG_PATH, vec, now);
#ifdef LOG_VIDEOANDPICTURE
		getFiles(LOG_VIDEO_PATH, vec, now);
		getFiles(LOG_PICTURE_PATH, vec, now);
#endif // LOG_VIDEOANDPICTURE



		for (auto& str : vec)
		{
			remove(str.c_str());
		}
		std::this_thread::sleep_for(std::chrono::seconds(LOG_EXPIRE_DETECT_TIME));
	}

}

int Detector::getFiles(const char* path, std::vector<std::string>& arr, time_t now)
{
	int num_of_img = 0;
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	char p[700] = { 0 };
	strcpy(p, path);
	strcat(p, "\\*");
	char buf[256];
	if ((hFile = _findfirst(p, &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					continue;
			}
			else
			{

				strcpy(buf, path);
				strcat(buf, "\\");
				strcat(buf, fileinfo.name);
				struct stat st1;
				stat(buf, &st1);
				if (now - st1.st_ctime > LOG_EXPIRE_TIME)
				{
					arr.push_back(buf);
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return num_of_img;
}

void Detector::pointRotate(Point2d& point, Point2d& pivot, int angle)
{
	int x = point.x, y = point.y;//旋转的点
	int dx = pivot.x, dy = pivot.y;//被绕着旋转的点
	point.x = (x - dx)*cos(angle * M_PI / 180) - (y - dy)*sin(angle * M_PI / 180) + dx;
	point.y = (y - dy)*cos(angle * M_PI / 180) + (x - dx)*sin(angle * M_PI / 180) + dy;
}

void Detector::lineRotate(Line2d& line, Point2d& pivot, int angle)
{
	pointRotate(line.first, pivot, angle);
	pointRotate(line.second, pivot, angle);
}

double Detector::getDistance(Point2f P, Point2f A, Point2f B)
{
		//计算r |AB| |AP| |BP| |PC|
		double ab = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2)); // |AB|
		double ap = sqrt(pow((P.x - A.x), 2) + pow((P.y - A.y), 2)); // |AP|
		double bp = sqrt(pow((P.x - B.x), 2) + pow((P.y - B.y), 2)); // |BP|
		double r = 0;
		r = ((P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y)) / pow(ab, 2);
		//double distance = 0;
		double distance = 0;
		if (ab > 0)
		{
			if (r >= 1)
				distance = bp;
			else if (r > 0 && r < 1)
				distance = sqrt(pow(ap, 2) - r * r*pow(ab, 2));
			else
				distance = ap;
		}
		if (isinf(distance)|| isnan(distance))
		{
			distance = 0;
		}

		return distance;
}



void Detector::setAdaptor(std::shared_ptr<CaptureAdaptor> adaptor)
{
	_captureAdaptor = adaptor;
	_abs_center.x = 0;
}

Mat& Detector::frame()
{
	if (_captureAdaptor == nullptr)
	{
		_captureAdaptor = std::make_shared<PictureCaptureAdaptor>("error.png");
	}
	_captureAdaptor->getFrame(_frame_cache);//从数据源适配器中获取一帧

	if (_running)
	{
		process(_frame_cache);
		
	}
	if (_abs_center.x == 0)//计算标靶的精确位置信息
	{
		_abs_center = Point2d(static_cast<float>(_frame_cache.cols) * 0.5083, static_cast<float>(_frame_cache.rows) * 0.5017);
		_cell_length = static_cast<float>(_frame_cache.cols)*0.0675;
		_hor = Line2d(_abs_center.x, 0, _abs_center.x, _frame_cache.rows);
		_ver = Line2d(0, _abs_center.y, _frame_cache.cols, _abs_center.y);
		lineRotate(_hor, _abs_center, TARGET_OFFSET_ANGLE);
		lineRotate(_ver, _abs_center, TARGET_OFFSET_ANGLE);

	}
#ifdef LOG_VIDEOANDPICTURE
	if (!_frame_cache.empty())
	{
		IplImage frame_img = IplImage(_frame_cache);
		if (_frame_writer != nullptr)
		{
			cvWriteFrame(_frame_writer, &frame_img);
		}
	}
	_frame_write_cache = _frame_cache.clone();
#endif 



	return _frame_cache;
}

bool Detector::initPLC()
{
	//该方法是socket网络编程中由客户端向服务器发起TCP连接的固定标准写法
	WORD version = MAKEWORD(2, 2);
	WSADATA data;
	if (SOCKET_ERROR == WSAStartup(version, &data))
	{
		_csock = INVALID_SOCKET;
		qDebug("初始化Winsock环境失败");
		return false;
	}
	_csock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_csock == INVALID_SOCKET) {
		return false;
	}
	sockaddr_in _csin = {};
	_csin.sin_family = AF_INET;
	if (BIND_ADDRESS)
	{
		_csin.sin_port = htons(MASTER_PORT);
		_csin.sin_addr.S_un.S_addr = inet_addr(MASTER_ADDRESS);
		if (SOCKET_ERROR == bind(_csock, reinterpret_cast<sockaddr*>(&_csin), sizeof(_csin)))
		{
			_csock = INVALID_SOCKET;
			qDebug("bind error");
			return false;
		}
	}
	_csin.sin_port = htons(SLAVE_PORT);
	_csin.sin_addr.S_un.S_addr = inet_addr(SLAVE_ADDRESS);
	if (SOCKET_ERROR == connect(_csock, reinterpret_cast<sockaddr*>(&_csin), sizeof(_csin)))
	{
		_csock = INVALID_SOCKET;
		qDebug("connect error");
		return false;
	}
	return true;
}



bool Detector::calcXOR(std::string & cmd)
{
	const char* str = cmd.c_str();
	char fcs[2] = { '\0','\0' };
	if (str == nullptr || fcs == nullptr)
		return false;
	char ch = *str;
	for (int i = 1; i < cmd.length(); i++) {
		ch ^= *(str + i); //异或运算
	}
	char ct = ch >> 4; //取异或结果的高四位
	if (ct > 9) //转为ASCII码
		ct += 'A' - 10;
	else
		ct += '0';
	*fcs = ct;
	ct = ch & 0x0F; //取异或结果的低四位
	if (ct > 9) //转为ASCII码
		ct += 'A' - 10;
	else
		ct += '0';
	*(fcs + 1) = ct;
	cmd.push_back(fcs[0]);
	cmd.push_back(fcs[1]);
	cmd.push_back('*');
	cmd.push_back('\r');
	return true;
}

void Detector::stoa_hex(short src, char* dest)
{
	if (dest == nullptr)return;
	sprintf(dest, "%04x", src);
	int sz = strlen(dest);
	if (sz > 4)
	{
		std::string temp(4, '0');
		for (int i = 0; i < 4; i++)
		{
			temp[i] = dest[sz - 4 + i];
		}
		strcpy(dest, temp.c_str());
	}
}


void Detector::process(Mat& srcImg)
{
	_frame_count++;
	
	if (srcImg.empty())return;
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);//色域转换
	Mat dstImg = srcImg.clone();
	Mat tempImg = srcImg.clone();
	cvtColor(dstImg, dstImg, CV_GRAY2BGR);
	GaussianBlur(tempImg, tempImg, Size(3, 3), 0, 0);//高斯滤波
	threshold(tempImg, tempImg, _threshVal, 255, CV_THRESH_BINARY);//二值化
	//imshow("binimg", srcImg);
	//Canny(srcImg, srcImg, 100, 200); //轮廓化
	//imshow("Canny", srcImg);
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarcy;
	findContours(tempImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//取轮廓
	std::vector<RotatedRect> box(contours.size());

	time_t now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (now - _log_checktime > LOG_SINGLETIME)
	{
		auto time_string = get_time_string(now, true);
		{
			auto temp = fopen((LOG_PATH + time_string + ".log").c_str(), "wt");
			auto temp1 = _log_file;
			_log_file = temp;
			if (temp1 != nullptr)
			{
				fclose(temp1);
			}
		}
#ifdef LOG_VIDEOANDPICTURE
		{
			CvSize sz(640, 480);
			auto temp = cvCreateVideoWriter((LOG_VIDEO_PATH + time_string + ".avi").c_str(), CV_FOURCC('M', 'P', '4', '2'), 25, sz, 1);
			auto temp1 = _frame_writer;
			_frame_writer = temp;
			if (temp1 != nullptr && &temp1 != nullptr)
			{
				cvReleaseVideoWriter(&temp1);
			}
		}
#endif // LOG_VIDEOANDPICTURE
		_log_checktime = now;
	}
	_now_time = now;

	putText(dstImg, get_time_string(_now_time, false), cv::Point(5, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));//帧率文字
	putText(dstImg, _ret == 12 ? "COMM_OK" : "COMM_ERROR", cv::Point(5, 40), FONT_HERSHEY_SIMPLEX, 0.5, _ret == 12 ? Scalar(0, 255, 0) : Scalar(0, 0, 255));
	putText(dstImg, std::to_string(_fps) + "FPS", cv::Point(5, 60), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));//帧率文字
	int max_index = 0;
	float max_area = 0;
	for (int i = 0; i < contours.size(); i++)//求拟合椭圆
	{
		if (contours[i].size() >= MIN_CONTOUR_SIZE)
		{
			box[i] = fitEllipse(Mat(contours[i]));
			Size2f size = box[i].size;
			if (size.height > _minArea && size.width > _minArea && size.height*size.width > max_area)
			{
				max_area = size.height*size.width;
				max_index = i;
			}
		}
	}
	if (max_area != 0)//计算偏移坐标及绘制必要的信息
	{
		Point2f center = box[max_index].center;
		//double offsetx = getDistance(center, _ver.first, _ver.second);
		//double offsety = getDistance(center, _hor.first, _hor.second);
		Point2d temp, temp1;
		int angle = 4;
		temp.x = center.x*cos(angle* M_PI / 180) + center.y*sin(angle* M_PI / 180);
		temp.y = center.y*cos(angle* M_PI / 180) - center.x*sin(angle* M_PI / 180);
		temp1.x = _abs_center.x*cos(angle* M_PI / 180) + _abs_center.y*sin(angle* M_PI / 180);
		temp1.y = _abs_center.y*cos(angle* M_PI / 180) - _abs_center.x*sin(angle* M_PI / 180);//求偏移坐标
		_offset.x = static_cast<int>((temp.x - temp1.x) * 10 / _cell_length);
		_offset.y = static_cast<int>((temp1.y - temp.y) * 10 / _cell_length);
		
		std::string text = 
			"(" + 
			std::to_string(_offset.x) +
			"," + 
			std::to_string(_offset.y) +
			")";
		putText(dstImg, text, cv::Point(5, 80), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

		

		//text =
		//	"(" +
		//	std::to_string(_offset.x + 50) +
		//	"," +
		//	std::to_string(50 - _offset.yS) +
		//	")";
		//putText(dstImg, text, cv::Point(5, 60), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
		line(dstImg, Point2f(center.x, center.y - 8), Point2f(center.x, center.y + 8), Scalar(0, 0, 255), 2, 8);
		line(dstImg, Point2f(center.x - 8, center.y), Point2f(center.x + 8, center.y), Scalar(0, 0, 255), 2, 8);//绘制中心十字
		if (_show_ellipse)
		{
			ellipse(dstImg, box[max_index], Scalar(0, 255, 0), 1, 8);
		}
	}
	if (_show_target)
	{
		draw_target(dstImg);
	}
	
	srcImg = dstImg;

}

void Detector::draw_target(Mat & srcImg)
{
	line(srcImg, _hor.first, _hor.second, Scalar(0, 255, 0), 1, 8);
	line(srcImg, _ver.first, _ver.second, Scalar(0, 255, 0), 1, 8);
	circle(srcImg, Point2f(_abs_center.x, _abs_center.y), _cell_length, Scalar(0, 255, 0), 1, 8);
	circle(srcImg, Point2f(_abs_center.x, _abs_center.y), 2 * _cell_length, Scalar(0, 255, 0), 1, 8);
	circle(srcImg, Point2f(_abs_center.x, _abs_center.y), 3 * _cell_length, Scalar(0, 255, 0), 1, 8);
}



