#ifndef _NERDIY_H
#define _NERDIY_H

#include  "VCAN_NRF24L0.h"
#include  "common.h"
#include  "stdio.h"
#include  "stdlib.h"

#ifndef DATA_PACKET
#define DATA_PACKET 32
#endif

//这个是给 atoi使用的宏定义
#define MAX_INT ((1 << 16) - 1)
#define MIN_INT (-(1 << 16))

//定义参数收发送的数量
#define PIDSETTING_NUM 5
#define DIYPARAMETER_NUM 16
#define GLOBAL_SETTING_NUM 3

//===================================
//参数美军型定义//全部从1开始！
//===================================
//总的类型分类
typedef enum
{
  Camera = 1,      //摄像头
  CCD,             //CCD
  Electricity,     //电感数据
  RealTime,        //回发的实时数据
  SendBackPID,     //回发的PID数值
  SendBackDIY,     //回发的自定义参数
  SendBackPID_ACK, //确定收到PID设置信息_ACK
  SendBackDIY_ACK  //确定收到自定义参数设置信息_ACK
}Father;

//===================================
//子类型分类
//==================================
//摄像头
typedef enum
{
  Camera_1 = 1, //第一个摄像头
  Camera_2,     //第二个
  Camera_3
}Child_Camera;

//CCD枚举类型
typedef enum
{
  CCD_1 = 1, //第一个CCD
  CCD_2,     //第二个CCD
  CCD_3
}Child_CCD;

//电感枚举类型
typedef enum
{
  Electricity_1 = 1, //第一个电感的参数
  Electricity_2,     //,,,,,
  Electricity_3,
  Electricity_4,
  Electricity_5,
  Electricity_6,
  Electricity_7,
  Electricity_8,
  Electricity_9
}Child_Electricity;

//实时参数枚举类型
typedef enum
{
  RealTime_1 = 1,   //实时参数一
  RealTime_2,       //.....
  RealTime_3,
  RealTime_4,
  RealTime_5,
  RealTime_6,
  RealTime_7,
  RealTime_8,
  RealTime_9
}Child_RealTime;

//PID类型枚举
typedef enum
{
  Servo = 1,         //舵机PID
  Nonbalance_Motor,  //非直立PID
  Balance_Stand,     //直立车——直立PID
  Balance_Speed,     //直立车——速度PID
  Balance_Direction  //直立车——方向PID
}Child_SendBackPID;

//自定义参数枚举
typedef enum
{
  DIY_Para_1 = 1,   //第一个自定义参数
  DIY_Para_2,       //第二个自定义参数
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
  Servo_ACK = 1,          //回发确认已经设置好——舵机PID
  Nonbalance_Motor_ACK,   //回发确认已经设置好——电机PID
  Balance_Stand_ACK,      //回发确认已经设置好——直立PID
  Balance_Speed_ACK,      //回发确认已经设置好——速度PID
  Balance_Direction_ACK   //回发确认已经设置好——方向PID
}Child_SendBackPID_ACK;   

typedef enum
{
  DIY_Para_1_ACK = 1,    //回发确认已经设置好——第一个自定义参数
  DIY_Para_2_ACK,        //回发确认已经设置好——第二个自定义参数
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
//作为回发给电脑的数据格式接口定义
//***************************************************

//各种PID参数
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  float Value_P;
  float Value_I;
  float Value_D;
}PIDSetting; 

//各种自定义参数
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  float DIY_Value;
}DIYParameter;

//需要回发的所有参数
typedef struct
{
  int FlagValueChanged;
  int father;
  int child;
  int need_Send;
}WholeSetting;
//***************************************************

//发送的数组可以无限大

//data--要发送的数据 ；actualLen--需要发送数据的长度；sendlen，一次性发送的长度 (定值)：DATA_PACKET - 1 = 31
extern void SendPack_Long(unsigned char *data,int actualLen, int sendlen); 
extern void SendPack_Short(int father, int child, float value, int hasHead, int hasEnd); //一次发送只能小于32为的数组
extern void SendPack_Echo(int father, int child, char *sendACK);  //发送确认信号
extern void SendPack_PID(int father, int child, float P, float I, float D, int hasHead, int hasEnd); //一次发送只能小于32为的数组
extern void SendPack_CCD(int father, int child, uint8 *ccdbuff, int ccdwidth, int hasHead, int hasEnd);//一次发送只能小于32为的数组
extern void SendPack_Camera(int father, int child, uint8 *camerabuff, int camera_size);
extern int NRF_Recieve(unsigned char *data, PIDSetting *pidsetting, int num_PID, DIYParameter *diypara,int numDIY, WholeSetting *wholesetting, int numWhole);//OK
float atof_self(const unsigned char *str, int start, int end);
int atoi_self(const unsigned char *str, int start, int end);

#endif