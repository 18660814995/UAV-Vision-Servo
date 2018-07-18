#include <iostream>

#include "UAV_GUI.h"
#include "UAV_CONFIG.h"
#include "VIDEO_STREAM.h"
#include "UAV_STRATEGY.h"

#include <simulation.h>
#include <DataTransmission.h>
#include <logfiles_io.h>

INT_PTR Simulation_UAV_CALLBACK2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

int main()
{


	//UAV_CONFIG::SaveConfig("Config\\UAV_CONFIG.xml");
	//return 0;
	UAV_CONFIG::LoadConfig("Config\\UAV_CONFIG.xml");
	SetConsoleTitle(TEXT("����Ŀ������ - v2.0"));
	UAV_GUI::hwnd_console = ::GetConsoleWindow();


	//  ��ʼ������ʵ��
	UAV_GUI::initHINSTANCE();
	UAV_GUI::CreateMainGUI();
	
	// ��������ģ��
	SIMULATION::createSimulation_UAV2PC(UAV_GUI::hwnd_main); // �����������
	SIMULATION::SetMessageSend(&UAV_STRATEGY::image_type, &UAV_STRATEGY::uav_height); // �������ݣ�UAV��ֱ���޸Ļ�������
	SIMULATION::GetMessageReceive(&UAV_STRATEGY::isSend, &UAV_STRATEGY::pc_type, UAV_STRATEGY::data, &UAV_STRATEGY::pilpline_time);
	SIMULATION::StartUAVSimulator();


	// ����ģ��
	//bool isOpen = DataTran::OpenSerialPort(&UAV_STRATEGY::RS, &UAV_STRATEGY::uav_height);
	//if (!isOpen)
	//	printf("Warning: Can't open serial port.\n");


	// ��Ƶ����ʼ��ʵ������View1��ͼ����ʾ��Ӧ��ͼ��
	VIDEO_STREAM::initVideoStream(); //��ʼ���󣬽����õ�ǰ����µĻҶ�������Ϣ

	// ��Ƶ¼�������ݴ洢
	if(!UAV_IO::InitLogFiles(true, true, true, true, true))
		printf("Warning: Can't create log files.\n");


	// ����ʹ��
	UAV_STRATEGY::CreateStrategy();



	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return 0;
}



