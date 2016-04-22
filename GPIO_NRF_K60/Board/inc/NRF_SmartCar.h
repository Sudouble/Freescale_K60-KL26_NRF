#ifndef _NERDIY_H
#define _NERDIY_H

#include  "VCAN_NRF24L0.h"
#include  "common.h"
#include  "stdio.h"
#include  "stdlib.h"

#ifndef DATA_PACKET
#define DATA_PACKET 32
#endif

//����Ǹ� atoiʹ�õĺ궨��
#define MAX_INT ((1 << 16) - 1)
#define MIN_INT (-(1 << 16))

//��������շ��͵�����
#define PIDSETTING_NUM 5
#define DIYPARAMETER_NUM 16
#define GLOBAL_SETTING_NUM 3

//===================================
//���������Ͷ���//ȫ����1��ʼ��
//===================================
//�ܵ����ͷ���
typedef enum
{
  Camera = 1,      //����ͷ
  CCD,             //CCD
  Electricity,     //�������
  RealTime,        //�ط���ʵʱ����
  SendBackPID,     //�ط���PID��ֵ
  SendBackDIY,     //�ط����Զ������
  SendBackPID_ACK, //ȷ���յ�PID������Ϣ_ACK
  SendBackDIY_ACK  //ȷ���յ��Զ������������Ϣ_ACK
}Father;

//===================================
//�����ͷ���
//==================================
//����ͷ
typedef enum
{
  Camera_1 = 1, //��һ������ͷ
  Camera_2,     //�ڶ���
  Camera_3
}Child_Camera;

//CCDö������
typedef enum
{
  CCD_1 = 1, //��һ��CCD
  CCD_2,     //�ڶ���CCD
  CCD_3
}Child_CCD;

//���ö������
typedef enum
{
  Electricity_1 = 1, //��һ����еĲ���
  Electricity_2,     //,,,,,
  Electricity_3,
  Electricity_4,
  Electricity_5,
  Electricity_6,
  Electricity_7,
  Electricity_8,
  Electricity_9
}Child_Electricity;

//ʵʱ����ö������
typedef enum
{
  RealTime_1 = 1,   //ʵʱ����һ
  RealTime_2,       //.....
  RealTime_3,
  RealTime_4,
  RealTime_5,
  RealTime_6,
  RealTime_7,
  RealTime_8,
  RealTime_9
}Child_RealTime;

//PID����ö��
typedef enum
{
  Servo = 1,         //���PID
  Nonbalance_Motor,  //��ֱ��PID
  Balance_Stand,     //ֱ��������ֱ��PID
  Balance_Speed,     //ֱ���������ٶ�PID
  Balance_Direction  //ֱ������������PID
}Child_SendBackPID;

//�Զ������ö��
typedef enum
{
  DIY_Para_1 = 1,   //��һ���Զ������
  DIY_Para_2,       //�ڶ����Զ������
  DIY_Para_3,       //....
  DIY_Para_4,
  DIY_Para_5,
  DIY_Para_6,
  DIY_Para_7,
  DIY_Para_8,
  DIY_Para_9,
  DIY_Para_10,
  DIY_Para_11,
  DIY_Para_12,
  DIY_Para_13,
  DIY_Para_14,
  DIY_Para_15,
  DIY_Para_16
}Child_SendBackDIY;

//
typedef enum
{
  Servo_ACK = 1,          //�ط�ȷ���Ѿ����úá������PID
  Nonbalance_Motor_ACK,   //�ط�ȷ���Ѿ����úá������PID
  Balance_Stand_ACK,      //�ط�ȷ���Ѿ����úá���ֱ��PID
  Balance_Speed_ACK,      //�ط�ȷ���Ѿ����úá����ٶ�PID
  Balance_Direction_ACK   //�ط�ȷ���Ѿ����úá�������PID
}Child_SendBackPID_ACK;   

typedef enum
{
  DIY_Para_1_ACK = 1,    //�ط�ȷ���Ѿ����úá�����һ���Զ������
  DIY_Para_2_ACK,        //�ط�ȷ���Ѿ����úá����ڶ����Զ������
  DIY_Para_3_ACK,        //...
  DIY_Para_4_ACK,
  DIY_Para_5_ACK,
  DIY_Para_6_ACK,
  DIY_Para_7_ACK,
  DIY_Para_8_ACK,
  DIY_Para_9_ACK,
  DIY_Para_10_ACK,
  DIY_Para_11_ACK,
  DIY_Para_12_ACK,
  DIY_Para_13_ACK,
  DIY_Para_14_ACK,
  DIY_Para_15_ACK,
  DIY_Para_16_ACK
}Child_SendBackDIY_ACK;

//***************************************************
//��Ϊ�ط������Ե����ݸ�ʽ�ӿڶ���
//***************************************************

//����PID����
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  float Value_P;
  float Value_I;
  float Value_D;
}PIDSetting; 

//�����Զ������
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  float DIY_Value;
}DIYParameter;

//��Ҫ�ط������в���
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  int need_Send;
}WholeSetting;
//***************************************************

//���͵�����������޴�

//data--Ҫ���͵����� ��actualLen--��Ҫ�������ݵĳ��ȣ�sendlen��һ���Է��͵ĳ��� (��ֵ)��DATA_PACKET - 1 = 31
extern void SendPack_Long(unsigned char *data,int actualLen, int sendlen); 
extern void SendPack_Short(int father, int child, float value, int hasHead, int hasEnd); //һ�η���ֻ��С��32Ϊ������
extern void SendPack_Echo(int father, int child, char *sendACK);  //����ȷ���ź�
extern void SendPack_PID(int father, int child, float P, float I, float D, int hasHead, int hasEnd); //һ�η���ֻ��С��32Ϊ������
extern void SendPack_CCD(int father, int child, uint8 *ccdbuff, int ccdwidth, int hasHead, int hasEnd);//һ�η���ֻ��С��32Ϊ������
extern void SendPack_Camera(int father, int child, uint8 *camerabuff, int camera_size);
extern int NRF_Recieve(unsigned char *data, PIDSetting *pidsetting, int num_PID, DIYParameter *diypara,int numDIY, WholeSetting *wholesetting, int numWhole);//OK
float atof_self(const unsigned char *str, int start, int end);
int atoi_self(const unsigned char *str, int start, int end);

#endif