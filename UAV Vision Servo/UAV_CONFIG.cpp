#include "UAV_CONFIG.h"

namespace UAV_CONFIG
{
	int video_type = 1; //Ĭ�ϴ��ļ���
	std::string note_video_type = "video_type: ��Ƶ�����ͣ�1���ļ�����2ѡ����̨";

	std::string video_path = "E:\\���˻���������\\��Ƶ����\\��ʵ-FLETD-3.mp4";
	std::string note_video_path = "video_path: ��Ƶ�ļ�·��";

	bool SaveConfig(std::string filepath)
	{
		cv::FileStorage fs(filepath, cv::FileStorage::WRITE);
		if (!fs.isOpened())
			return false;

		cvWriteComment(fs.fs, note_video_type.c_str(), 0);
		fs << "video_type" << (int)video_type;

		cvWriteComment(fs.fs, note_video_path.c_str(), 0);
		fs << "video_path" << (std::string)video_path;

		fs.release();

		return true;
	}

	bool LoadConfig(std::string filepath)
	{
		cv::FileStorage fs(filepath, cv::FileStorage::READ);
		if (!fs.isOpened())
			return false;

		video_type = (int)fs["video_type"];
		video_path = (std::string)fs["video_path"];

		fs.release();
		return true;
	}
}