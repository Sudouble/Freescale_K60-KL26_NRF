/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
//       led_turn(LED1); 
        nrf_handler();
    }
}

void Init_NRF()
{
    //*********************************************************************
    printf("\n\n\n***********����ģ��NRF24L01+����************");
    while(!nrf_init())                  //��ʼ��NRF24L01+ ,�ȴ���ʼ���ɹ�Ϊֹ
    {
        printf("\n  NRF��MCU����ʧ�ܣ������¼����ߡ�\n");
    }
      //*********************************************************************  
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    			//���� PORTE ���жϷ�����Ϊ PORTE_VECTORn
    enable_irq(PORTE_IRQn);
}

void Init_Other()
{
    //**************************���PWM��ʼ��******************************
    ftm_pwm_init(FTM0, FTM_CH0, 10000, 1000);                       
    ftm_pwm_init(FTM0, FTM_CH1, 10000, 1000);
    ftm_pwm_init(FTM0, FTM_CH2, 10000, 1000);                       
    ftm_pwm_init(FTM0, FTM_CH3, 10000, 1000);
    //*********************************************************************
}

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� LED �����Ƿ�����
                ������Ч����LED0��LED1ͬʱ������˸
 */
void main()
{
    uint8 buff[DATA_PACKET];
    int relen = 0, i;
    
    
    //======================================================
    //NRF Init
    Init_NRF();
    PIDSetting _pidsettings[PIDSETTING_NUM];
    DIYParameter _diyparameter[DIYPARAMETER_NUM];
    WholeSetting _wholesettings[GLOBAL_SETTING_NUM];
    
    for(i = 0; i < PIDSETTING_NUM; ++i)
    {
        _pidsettings[i].father = 0;
        _pidsettings[i].child = 0;
        _pidsettings[i].Value_P = 0;
        _pidsettings[i].Value_I = 0;
        _pidsettings[i].Value_D = 0;
    }
    for(i = 0; i < DIYPARAMETER_NUM; ++i)
    {
        _diyparameter[i].father = 0;
        _diyparameter[i].child = 0;
        _diyparameter[i].DIY_Value = 0;
    }
    for(i = 0; i < GLOBAL_SETTING_NUM; ++i)
    {
        _wholesettings[i].father = 0;
        _wholesettings[i].child = 0;
        _wholesettings[i].need_Send = 0;
    }
    //NRF_Init End
   
//    led_init(LED1);                         //��ʼ��LED1
    
    while(1)
    {
        //FOR RECEIVE
        relen = nrf_rx(buff,DATA_PACKET);               //�ȴ�����һ�����ݰ������ݴ洢��buff��
        if(relen != 0)
        {
//            NRF_Recieve(buff, _pidsettings, PIDSETTING_NUM, _diyparameter, DIYPARAMETER_NUM, _wholesettings, GLOBAL_SETTING_NUM);
//            
//            //���������ý��յ������ò�����PID��DIY������
//            //========================================================
//            //���
//            if(_pidsettings[0].FlagValueChanged == 1)
//            {
//                /*������������ı�����������ͬ*/
//                ANGLE_CONTROL_P = _pidsettings[0].Value_P;
//                ANGLE_CONTROL_I = _pidsettings[0].Value_I;
//                ANGLE_CONTROL_D = _pidsettings[0].Value_D;
//                _pidsettings[0].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Servo_ACK, "ACK");
//            }
//            //========================================================
//            //��ֱ���ĵ��
//            if(_pidsettings[1].FlagValueChanged == 1)
//            {
//                ANGLE_CONTROL_P = _pidsettings[1].Value_P;
//                ANGLE_CONTROL_I = _pidsettings[1].Value_I;
//                ANGLE_CONTROL_D = _pidsettings[1].Value_D;
//                _pidsettings[1].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Nonbalance_Motor_ACK, "ACK");
//            }
//            //========================================================
//            //�Ƕ�
//            if(_pidsettings[2].FlagValueChanged == 1)
//            {
//                ANGLE_CONTROL_P = _pidsettings[2].Value_P;
//                //ANGLE_CONTROL_I = _pidsettings[2].Value_I;
//                ANGLE_CONTROL_D = _pidsettings[2].Value_D;
//                _pidsettings[2].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Stand_ACK, "ACK");
//            }
//            //========================================================
//            //�ٶ�
//            if(_pidsettings[3].FlagValueChanged == 1)
//            {
//                SPEED_CONTROL_P = _pidsettings[3].Value_P;
//                SPEED_CONTROL_I = _pidsettings[3].Value_I;
//                SPEED_CONTROL_D = _pidsettings[3].Value_D;
//                
//                //����
//                g_fSpeedControlOut = 0;
//                g_fSpeedControlOutNew = 0;
//                g_fSpeedControlOutOld = 0;
//                fsampleerror1 = 0;
//                _pidsettings[3].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Speed_ACK, "ACK");
//            }
//            //========================================================
//            //����
//            if(_pidsettings[4].FlagValueChanged == 1)
//            {
//                DIRECTION_CONTROL_P = _pidsettings[4].Value_P;
//                //DIRECTION_CONTROL_I = _pidsettings[4].Value_I;
//                DIRECTION_CONTROL_D = _pidsettings[4].Value_D;
//                _pidsettings[4].FlagValueChanged = 0;
//                SendPack_Echo(SendBackPID_ACK, Balance_Direction_ACK, "ACK");
//            }
//            //////////////////////////////////////////////////////////
//            //�Զ������һ
//            if (_diyparameter[0].FlagValueChanged == 1)
//            {
//                CAR_SPEED_SET = _diyparameter[0].DIY_Value;
//                _diyparameter[0].FlagValueChanged = 0;
//                SendPack_Echo(SendBackDIY_ACK, DIY_Para_1_ACK, "ACK");
//            }
//            //=======================================================
//            //�Զ��������
//            if (_diyparameter[1].FlagValueChanged == 1)
//            {
//                //diyTest = _diyparameter[1].DIY_Value;
//                //_diyparameter[1].FlagValueChanged = 0;
//                //SendPack_Echo(SendBackDIY_ACK, DIY_Para_2_ACK, "ACK");
//            }
//            //=======================================================
//            //========================================
//            //���ڻ�ȡ��λ����������Ӧ��д��Ҫ�ط��ı�������
//            if(_wholesettings[0].need_Send == 1)
//            {
//                
//                printf("I will send\n");
//                //****************************************
//                //PID�����ط�
//                SendPack_PID(SendBackPID, Balance_Stand, ANGLE_CONTROL_P, 0, ANGLE_CONTROL_D, 1, 0); //ֱ��PID
//                SendPack_PID(SendBackPID, Balance_Speed, SPEED_CONTROL_P, SPEED_CONTROL_I, SPEED_CONTROL_D, 0, 0); //�ٶ�PID
//                SendPack_PID(SendBackPID, Balance_Direction, DIRECTION_CONTROL_P, 0, DIRECTION_CONTROL_D, 0, 0); //����PID
//                //****************************************
//                //�Զ������
//                SendPack_Short(SendBackDIY,DIY_Para_1, 10, 0, 0);
//                //SendPack_Short(SendBackDIY,DIY_Para_2, diyTest, 0, 0);
//                SendPack_Short(SendBackDIY,DIY_Para_3, 10, 0, 1);
//               
//                _wholesettings[0].need_Send = 0;
//            }     
          
              //========================================================
              //========================================================
              //����ͣ������������������������
              if(_wholesettings[1].need_Send == 1)
              {
                  //�ر���Ҫ�رյ��ж�
                  disable_irq(PORTE_IRQn);
                  DisableInterrupts; //���������
                  
                  //�ر����
                  ftm_pwm_duty(FTM0, FTM_CH0, 1000);
                  ftm_pwm_duty(FTM0, FTM_CH1, 1000);
                  ftm_pwm_duty(FTM0, FTM_CH2, 1000);
                  ftm_pwm_duty(FTM0, FTM_CH3, 1000);
              }
              //========================================================
              //========================================================
//            printf("\n���յ�����:%s \n", buff);             //��ӡ���յ�������
        }
        
        //=======================================================
        //������������
        //=======================================================
        //����ͷͼ��
        //û��ʹ�á���������
        //****************************************
        //CCDͼ�񣨲����ã�������
        //SendPack_CCD(2, 1, (uint8_t *)&CCD_BUFF[0], TSL1401_SIZE, 1, 1);
        //****************************************
        //��в���
        //SendPack_Short(Electricity,Electricity_1, /*��ĵ�б�����*/ 0, 1, 0);
        //****************************************
        //ʵʱ����
        SendPack_Short(RealTime,RealTime_1, (int)1, 1, 0);
        SendPack_Short(RealTime,RealTime_2, (int)2, 0, 0);
        SendPack_Short(RealTime,RealTime_3, (int)22, 0, 0);
        SendPack_Short(RealTime,RealTime_4, (int)33, 0, 0);
        SendPack_Short(RealTime,RealTime_5, (int)45, 0, 0);
        SendPack_Short(RealTime,RealTime_6, (int)33, 0, 1);
        //****************************************
        //========================================
        DELAY_MS(10);
    }
}
