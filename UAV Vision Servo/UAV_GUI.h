#pragma once
#include <Windows.h>
#include "resource.h"
#include <opencv2\opencv.hpp>
#include <string>

namespace UAV_GUI
{
	extern HINSTANCE hInstance;
	void initHINSTANCE();
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	extern HWND hwnd_console;

	extern HWND hwnd_main;
	extern HWND hwnd_view_1; // ԭʼͼƬ�ӽ�
	extern std::string tilde_view_1; // �ӽ�1����
	extern HWND hwnd_view_2; // ԭʼͼƬ�ӽ�
	extern std::string tilde_view_2; // �ӽ�2����
	extern HWND hwnd_view_3; // ԭʼͼƬ�ӽ�
	extern std::string tilde_view_3; // �ӽ�2����
	extern cv::Mat Img_back; // ����ͼƬ
	void CreateMainGUI();



	extern HWND hwnd_method_height;
	extern HWND hwnd_resolution_height;

}