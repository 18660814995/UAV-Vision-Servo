#include "VIDEO_STREAM.h"

namespace VIDEO_STREAM
{
	cv::VideoCapture cap;
	cv::Mat ImgC, ImgR, ImgT;
	unsigned char img_gray[1080 * 1920];
	unsigned int imageType = COPY_RESOLUTION_960_540;
	bool isUpdateImage = false;
	int frameNumber = 0;
	int globalID = 0;

	HANDLE phCaptureObject;
	CRITICAL_SECTION img_lock;
	
	bool Open_Ave_C353()
	{
		DWORD pdwDeviceNum = 0;
		LPWSTR szDeviceName = new WCHAR[256];


		AVerGetDeviceNum(&pdwDeviceNum);
		std::cout << "���ݲɼ�������Ϊ�� " << pdwDeviceNum << std::endl;
		if (pdwDeviceNum == 0)
		{
			std::cout << "��ⲻ�����ݲɼ������˳�����" << std::endl;
			return false;
		}
		AVerGetDeviceName(0, szDeviceName);
		for (int i = 0; i<256 && szDeviceName[i] != 52685; i++)
			std::cout << (char)szDeviceName[i];
		std::cout << std::endl;
		return true;
	}
	bool Set_AVe_C353_Stream(bool isShow, HWND hwnd)
	{
		LONG getFunInfor;
		getFunInfor = AVerCreateCaptureObject(0, hwnd, &phCaptureObject);
		if (getFunInfor != 0)
		{
			printf("������Ƶ����ʧ�ܣ�������Ϊ�� %d", getFunInfor); 
			return false;
		}
		getFunInfor = AVerSetVideoSource(phCaptureObject, VIDEOSOURCE_HDMI);
		if (getFunInfor != 0)
		{
			printf("������Ƶ��Դʧ�ܣ�������Ϊ�� %d", getFunInfor);
			return false;
		}
		VIDEO_RESOLUTION pVideoResolution;
		pVideoResolution.dwVersion = 1;
		pVideoResolution.dwVideoResolution = VIDEORESOLUTION_1920X1080;
		pVideoResolution.bCustom = FALSE;
		getFunInfor = AVerSetVideoResolutionEx(phCaptureObject, &pVideoResolution);
		if (getFunInfor != 0)
		{
			printf("������Ƶ�ֱ���ʧ�ܣ�������Ϊ�� %d", getFunInfor);
			return false;
		}

		if (isShow)
		{
			RECT rectVideoWnd;
			rectVideoWnd.left = 0;
			rectVideoWnd.top = 0;
			rectVideoWnd.right = 480;
			rectVideoWnd.bottom = 270;
			getFunInfor = AVerSetVideoWindowPosition(phCaptureObject, rectVideoWnd);
			if (getFunInfor != 0)
			{
				printf("������Ƶ��ʾλ��ʧ�ܣ�������Ϊ�� %d", getFunInfor);
				return false;
			}
		}
		getFunInfor = AVerStartStreaming(phCaptureObject);
		if (getFunInfor != 0)
		{
			printf("��ʼ��Ƶ��ʧ�ܣ�������Ϊ�� %d", getFunInfor);
			return false;
		}
		return true;
	}
	void Delete_Ave_C353()
	{
		LONG infor;
		infor = AVerCaptureVideoSequenceStop(phCaptureObject);
		infor = AVerHwCaptureStreamStop(phCaptureObject);

		AVerStopStreaming(phCaptureObject);
		AVerDeleteCaptureObject(phCaptureObject);

	}

	HANDLE handle_video_stream;
	bool initVideoStream()
	{
		InitializeCriticalSection(&img_lock);
		ImgC = UAV_GUI::Img_back.clone();
		ImgR = UAV_GUI::Img_back.clone();
		ImgT = UAV_GUI::Img_back.clone();

		if (UAV_CONFIG::video_type == 1) //�ļ���Ƶ��
		{
			cap.open(UAV_CONFIG::video_path);
			if (!cap.isOpened())
			{
				printf("��Ƶ�ļ���ʧ�ܣ�\n");
				return false;
			}
		}
		else if (UAV_CONFIG::video_type == 2) //��̨��Ƶ��
		{
			bool res;
			res = Open_Ave_C353();
			if (res == false)
				return false;
			res = Set_AVe_C353_Stream(true, UAV_GUI::hwnd_view_1); // ׼����ʾ��Ƶ
			if (res == false)
				return false;

			// ���ûص�����
			LONG pInfo;
			VIDEO_CAPTURE_INFO CaptureInfo;
			CaptureInfo.dwCaptureType = CT_SEQUENCE_FRAME;//ָ����֡Ϊ��λץȡ
			CaptureInfo.dwSaveType = ST_CALLBACK;//����YUY2���ݸ��ص�����
			CaptureInfo.bOverlayMix = FALSE;//����ͼ�����������ͼ�����Ϣ
			CaptureInfo.lpCallback = Camera_CALLBACK;
			pInfo = AVerCaptureVideoSequenceStart(phCaptureObject, CaptureInfo);
			if (pInfo != 0)
			{
				printf("�ص�����ץȡͼ��ʧ�ܣ�������Ϊ�� %d\n", pInfo);
				return false;
			}
		}
		else
			return false;

		handle_video_stream = CreateThread(NULL, 0, VIDEO_STREAM_CALLBACK, NULL, 0, NULL);
		return true;
		
	}
	// ���������Ҫ�Ǹ�����ʾ����ͼ�������ļ���Ƶ�ļ���������������ԭʼͼ�����ݣ������������ȡ��Ҫ�ķֱ���ͼ��

	
	DWORD WINAPI VIDEO_STREAM_CALLBACK(LPVOID lpParam)
	{
		double t1, t2;
		int sleep_t;
		while (1)
		{
			// ����ԭʼͼ
			t1 = cv::getTickCount();

			// ��̨����ڲ����Լ�����ͼ��ĺ���
			if (UAV_CONFIG::video_type == 1)
			{
				cap >> ImgC;
				if (ImgC.empty())
					break;
				frameNumber++;
				cv::imshow(UAV_GUI::tilde_view_1, ImgC);

				cv::Mat Img_temp;
				if (ImgC.channels() > 1)
					cv::cvtColor(ImgC, Img_temp, CV_RGB2GRAY);
				else
					Img_temp = ImgC.clone();
				if (isUpdateImage == false)
				{
					globalID = frameNumber;
					switch (imageType)
					{
					case COPY_RESOLUTION_1920_1080:
					{
						memcpy(img_gray, Img_temp.data, sizeof(unsigned char)*NUMBER_1920_1080);
						break;
					}
					case COPY_RESOLUTION_960_540:
					{
						unsigned char *_data = Img_temp.data;
						int idx_i, idx_o;
						for (int i = 0; i < 540; i++)
						{
							idx_i = i * 960;
							idx_o = i * 1920;
							for (int j = 0; j < 960; j++)
							{
								img_gray[idx_i + j] = _data[(idx_o + j) << 1];
							}
						}
					}
					default:
						break;
					}
					isUpdateImage = true;
				}
				
			}

			EnterCriticalSection(&img_lock);
			cv::imshow(UAV_GUI::tilde_view_2, ImgR);
			cv::imshow(UAV_GUI::tilde_view_3, ImgT);
			LeaveCriticalSection(&VIDEO_STREAM::img_lock);
			t2 = cv::getTickCount();
			sleep_t = 30 - (t2 - t1) * 1000 / cv::getTickFrequency();
			if (sleep_t <= 0) sleep_t = 1;
			Sleep(sleep_t);
		}
		return DWORD(0);
	}
	BOOL WINAPI Camera_CALLBACK(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, __int64 tRefTime, LONGPTR lUserData)
	{
		frameNumber++;
		if (isUpdateImage == false)
		{
			globalID = frameNumber;
			int idx_i, idx_o;
			switch (imageType)
			{
			case COPY_RESOLUTION_1920_1080:
			{
				for (int i = 0; i < NUMBER_1920_1080; i++)
					img_gray[i] = pbData[i << 1];
				isUpdateImage = true;
				break;
			}
			case COPY_RESOLUTION_960_540:
			{
				for (int i = 0; i < 540; i++)
				{
					idx_i = i * 960;
					idx_o = i * 1920;
					for (int j = 0; j < 960; j++)
					{
						img_gray[idx_i + j] = pbData[(idx_o + j) << 2];
					}
				}
				isUpdateImage = true;
				break;
			}
			case COPY_RESOLUTION_480_270:
			{
				for (int i = 0; i < 270; i++)
				{
					idx_i = i * 480;
					idx_o = i * 1920;
					for (int j = 0; j < 480; j++)
					{
						img_gray[idx_i + j] = pbData[(idx_o + j) << 3];
					}
				}
				isUpdateImage = true;
				break;
			}
			case COPY_RESOLUTION_240_135:
			{
				for (int i = 0; i < 135; i++)
				{
					idx_i = i * 240;
					idx_o = i * 1920;
					for (int j = 0; j < 240; j++)
					{
						img_gray[idx_i + j] = pbData[(idx_o + j) << 4];
					}
				}
				isUpdateImage = true;
				break;
			}
			default:
				break;
			}
		}
		return true;
	}
}