#pragma  once

#define UAV_WAITING_NOTHING          0x02    //������������κ��޸�
#define UAV_CHANGING_RESOLUTION      0x03    //�޸ķֱ��ʣ���֡��Ч


    // RS: Cross and Circle Detection
#define TARGET_CONFIRM               0x32    // IS: Ŀ��ȷ��
#define UAV_C2_DETECTION_YES         0x31    // SS: Cross has beed detected

#define UAV_C1_DETECTION             0x40    // RS: Cross Detection


#define UAV_EXIT                     0xf0    // RS: Exit Vision Servo


enum ReceiveState
{
	// ����״̬��ռ��ǰ4λ(0000)0000
	UAV_WAITING = 0x10, // RS, IS, SS: ���˻�������ȴ�״̬
	UAV_RESET = 0x20,    // RS: ���˻���������״̬
	UAV_C2_DETECTION = 0x30,

	// ����״̬, ռ�ú�4λ0000(0000)
	MOTiON_DETECTION = 0x01, // ���˻���ֹ������Ŀ��
	UNIFORM_ROI = 0x02,    // ���Ȳ�ȡ����Ŀ��
};

enum InnerState
{
	CV_TARGET_DETECTION = 0x31,
	CV_TARGET_CONFIRM = 0x32,
};

enum SendState
{
	CV_WAITING = 0x10,
	CV_C1_DETECTION_YES = 0x41,
	CV_C1_DETECTION_NO = 0x42,
};




#define COPY_RESOLUTION_1920_1080  0x10   //ԭʼͼƬ��С
#define NUMBER_1920_1080           1920*1080

#define COPY_RESOLUTION_960_540    0x11   //������С2��
#define NUMBER_960_540             960*540

#define COPY_RESOLUTION_480_270    0x12   //������С4��
#define NUMBER_480_270             480*270

#define COPY_RESOLUTION_240_135    0x13   //������С8��
#define NUMBER_240_135             240*135




#define UAV_CLB_HIGH2PIXEL     1          //�궨״̬���߶ȹ�������(px/cm)
#define UAV_CLB_PIXEL2DIST     2          //�궨״̬���߶ȹ��ƾ���(cm/px)