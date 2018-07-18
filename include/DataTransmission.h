#pragma once

//#include "definition.h"
//#include <Windows.h>
//#include <tchar.h>
//#include <iostream>
//#include <opencv2\opencv.hpp>

#include <uavdef.h>

//using std::string;




namespace DataTran
{
	// ��������ģ��
	UAV_EXPORTS bool OpenSerialPort(unsigned char *_RS, double *_height);
	UAV_EXPORTS void SendData2UAV(unsigned char SS, float pX, float pY, float vX, float vY, float useTime);

	//UAV������Ϣ
	UAV_EXPORTS extern float pixelError;//�����������
	UAV_EXPORTS extern float highPara_1;
	UAV_EXPORTS extern float highPara_2;
	UAV_EXPORTS extern float carHighValue; //С���ĸ߶�
	UAV_EXPORTS extern float cross_Length;

	UAV_EXPORTS extern int confirmNum;
	UAV_EXPORTS extern int confirmedNum;


//inValueΪ����ĸ߶�ֵ��Para_iΪ�����Ӧ�Ĳ���ֵ��calTypeΪ��Ҫ�����״̬
//��������calTypeΪ�߶ȼ������ؿ��״̬����ʵ��״̬���*��ǰ��������ֵ���ɣ���Ϊ�߶ȹ��ƾ���״̬����ʵ�����ؾ���*��ǰ��������ֵ
	UAV_EXPORTS float calPixcelAndDist(float inValue, float Para_1, float Para_2, unsigned char calType);
	UAV_EXPORTS float calPixcelAndDist(float inValue, unsigned char calType);

}