/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       main.c
 * @brief      野火KL26 平台主程序
 * @author     野火科技
 * @version    v5.0
 * @date       2013-12-14
 */

#include "common.h"
#include "include.h"

float SPEED_CONTROL_P=2.1,SPEED_CONTROL_I=1.5,SPEED_CONTROL_D=0,CAR_SPEED_SET=44;

/*!
*  @brief      PORTC和D中断服务函数
*  @since      v5.0
*/
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //引脚号

    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))           //PTA6触发中断
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位

        /*  以下为用户任务  */
        nrf_handler();

        /*  以上为用户任务  */
    }
}


void Init_NRF()
{
    //*********************************************************************
    printf("\n\n\n***********无线模块NRF24L01+测试************");
    while(!nrf_init())                  //初始化NRF24L01+ ,等待初始化成功为止
    {
        printf("\n  NRF与MCU连接失败，请重新检查接线。\n");
    }
      //*********************************************************************  
    set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);    			//设置 PORTE 的中断复位函数为 PORTE_VECTORn
    enable_irq(PORTC_PORTD_IRQn);
}

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       LED测试
 */
void  main(void)
{
    uint8 buff[DATA_PACKET];
    int relen = 0, i;
    
    
    //======================================================
    //NRF Init
    Init_NRF();
    PIDSetting _pidsettings[PIDSETTING_NUM];
    DIYParameter _diyparameter[DIYPARAMETER_NUM];
    WholeSetting _wholesettings[GLOBAL_SETTING_NUM];
    //NRF_Init End
    
   
//    led_init(LED1);                         //初始化LED1
    while(1)
    {
        //FOR RECEIVE
        relen = nrf_rx(buff,DATA_PACKET);               //等待接收一个数据包，数据存储在buff里
        if(relen != 0)
        {
             NRF_Recieve(buff, _pidsettings, PIDSETTING_NUM, _diyparameter, DIYPARAMETER_NUM, _wholesettings, GLOBAL_SETTING_NUM);
       
//            //在这里设置接收到的设置参数（PID和DIY参数）
//            //========================================================
//            //舵机
//            if(_pidsettings[0].FlagValueChanged == 1)
//            {
//                /*在这里输入你的变量名——下同*/
//                SPEED_CONTROL_P = _pidsettings[0].Value_P;
//                SPEED_CONTROL_I = _pidsettings[0].Value_I;
//                SPEED_CONTROL_D = _pidsettings[0].Value_D;
//                _pidsettings[0].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Servo_ACK, "ACK");
//            }
//            //========================================================
//            //非直立的电机
//            if(_pidsettings[1].FlagValueChanged == 1)
//            {
//                ANGLE_CONTROL_P = _pidsettings[1].Value_P;
//                ANGLE_CONTROL_I = _pidsettings[1].Value_I;
//                ANGLE_CONTROL_D = _pidsettings[1].Value_D;
//                _pidsettings[1].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Nonbalance_Motor_ACK, "ACK");
//            }
//            //========================================================
//            //角度
//            if(_pidsettings[2].FlagValueChanged == 1)
//            {
//                ANGLE_CONTROL_P = _pidsettings[2].Value_P;
//                //ANGLE_CONTROL_I = _pidsettings[2].Value_I;
//                ANGLE_CONTROL_D = _pidsettings[2].Value_D;
//                _pidsettings[2].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Stand_ACK, "ACK");
//            }
//            //========================================================
//            //速度
//            if(_pidsettings[3].FlagValueChanged == 1)
//            {
//                SPEED_CONTROL_P = _pidsettings[3].Value_P;
//                SPEED_CONTROL_I = _pidsettings[3].Value_I;
//                SPEED_CONTROL_D = _pidsettings[3].Value_D;
//                
////                //参数
////                g_fSpeedControlOut = 0;
////                g_fSpeedControlOutNew = 0;
////                g_fSpeedControlOutOld = 0;
////                fsampleerror1 = 0;
//                _pidsettings[3].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Speed_ACK, "ACK");
//                
//                printf("recvi!");
//            }
//            //========================================================
//            //方向
//            if(_pidsettings[4].FlagValueChanged == 1)
//            {
//                DIRECTION_CONTROL_P = _pidsettings[4].Value_P;
//                //DIRECTION_CONTROL_I = _pidsettings[4].Value_I;
//                DIRECTION_CONTROL_D = _pidsettings[4].Value_D;
//                _pidsettings[4].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Direction_ACK, "ACK");
//            }
//            //////////////////////////////////////////////////////////
//            //自定义参数一
//            if (_diyparameter[0].FlagValueChanged == 1)
//            {
//                CAR_SPEED_SET = _diyparameter[0].DIY_Value;
//                _diyparameter[0].FlagValueChanged = 0;
//                SendPack_Echo(SendBackDIY_ACK, DIY_Para_1_ACK, "ACK");
//            }
//            //=======================================================
//            //自定义参数二
//            if (_diyparameter[1].FlagValueChanged == 1)
//            {
//                //diyTest = _diyparameter[1].DIY_Value;
//                //_diyparameter[1].FlagValueChanged = 0;
//                //SendPack_Echo(SendBackDIY_ACK, DIY_Para_2_ACK, "ACK");
//            }
//            //=======================================================
//            //========================================
            //对于获取下位机参数的响应，写需要回发的变量类型
            if(_wholesettings[0].need_Send == 1)
            {
                
                printf("I will send\n");
                //****************************************
                //PID参数回发
                //SendPack_PID(SendBackPID, Balance_Stand, ANGLE_CONTROL_P, 0, ANGLE_CONTROL_D, 1, 1); //直立PID
                SendPack_PID(SendBackPID, Balance_Speed, SPEED_CONTROL_P, SPEED_CONTROL_I, SPEED_CONTROL_D, 1, 1); //速度PID
                //SendPack_PID(SendBackPID, Balance_Direction, DIRECTION_CONTROL_P, 0, DIRECTION_CONTROL_D, 1, 1); //方向PID
                //****************************************
                //自定义参数
                SendPack_Short(SendBackDIY,DIY_Para_1, 10, 1, 1);
                SendPack_Short(SendBackDIY,DIY_Para_2, 100, 1, 1);
                SendPack_Short(SendBackDIY,DIY_Para_3, 10.2, 1, 1);
               
                _wholesettings[0].need_Send = 0;
            }     
          
              //========================================================
              //========================================================
              //紧急停车！！！！！！！！！！！
              if(_wholesettings[1].need_Send == 1)
              {
                  //关闭需要关闭的中断
                  //disable_irq(PORTE_IRQn);
                  
//                  //关闭输出
//                  ftm_pwm_duty(FTM0, FTM_CH0, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH1, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH2, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH3, 1000);
                  
                  SendPack_Echo(9, 1, "ACK");
              }
              //========================================================
        }
        
        //=======================================================
        //参数发送区域
        //=======================================================
        //摄像头图像
        //SendPack_Camera(Camera, Camera_1, imgbuff, CAMERA_SIZE);
        //****************************************
        //CCD图像
        //SendPack_CCD(2, 1, (uint8_t *)&CCD_BUFF[0], TSL1401_SIZE, 1, 1);
        //****************************************
        //实时参数
        //SendPack_Short(Electricity,Electricity_1, /*你的变量名*/ 0, 1, 0);
        //****************************************
        //实时参数
        SendPack_Short(RealTime,RealTime_1, (int)1, 1, 1);
        SendPack_Short(RealTime,RealTime_2, (int)2, 1, 1);
        SendPack_Short(RealTime,RealTime_3, (int)22, 1, 1);
        SendPack_Short(RealTime,RealTime_4, (int)33, 1, 1);
        SendPack_Short(RealTime,RealTime_5, (int)45, 1, 1);
        SendPack_Short(RealTime,RealTime_6, (int)33, 1, 1);
        //****************************************
        //========================================
        DELAY_MS(10);
    }
}