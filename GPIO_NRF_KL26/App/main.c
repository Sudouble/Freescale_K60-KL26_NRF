/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      Ұ��KL26 ƽ̨������
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2013-12-14
 */

#include "common.h"
#include "include.h"

float SPEED_CONTROL_P=2.1,SPEED_CONTROL_I=1.5,SPEED_CONTROL_D=0,CAR_SPEED_SET=44;

/*!
*  @brief      PORTC��D�жϷ�����
*  @since      v5.0
*/
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //���ź�

    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))           //PTA6�����ж�
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ

        /*  ����Ϊ�û�����  */
        nrf_handler();

        /*  ����Ϊ�û�����  */
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
    set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);    			//���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
    enable_irq(PORTC_PORTD_IRQn);
}

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       LED����
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
    
   
//    led_init(LED1);                         //��ʼ��LED1
    while(1)
    {
        //FOR RECEIVE
        relen = nrf_rx(buff,DATA_PACKET);               //�ȴ�����һ�����ݰ������ݴ洢��buff��
        if(relen != 0)
        {
             NRF_Recieve(buff, _pidsettings, PIDSETTING_NUM, _diyparameter, DIYPARAMETER_NUM, _wholesettings, GLOBAL_SETTING_NUM);
       
//            //���������ý��յ������ò�����PID��DIY������
//            //========================================================
//            //���
//            if(_pidsettings[0].FlagValueChanged == 1)
//            {
//                /*������������ı�����������ͬ*/
//                SPEED_CONTROL_P = _pidsettings[0].Value_P;
//                SPEED_CONTROL_I = _pidsettings[0].Value_I;
//                SPEED_CONTROL_D = _pidsettings[0].Value_D;
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
////                //����
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
            //���ڻ�ȡ��λ����������Ӧ��д��Ҫ�ط��ı�������
            if(_wholesettings[0].need_Send == 1)
            {
                
                printf("I will send\n");
                //****************************************
                //PID�����ط�
                //SendPack_PID(SendBackPID, Balance_Stand, ANGLE_CONTROL_P, 0, ANGLE_CONTROL_D, 1, 1); //ֱ��PID
                SendPack_PID(SendBackPID, Balance_Speed, SPEED_CONTROL_P, SPEED_CONTROL_I, SPEED_CONTROL_D, 1, 1); //�ٶ�PID
                //SendPack_PID(SendBackPID, Balance_Direction, DIRECTION_CONTROL_P, 0, DIRECTION_CONTROL_D, 1, 1); //����PID
                //****************************************
                //�Զ������
                SendPack_Short(SendBackDIY,DIY_Para_1, 10, 1, 1);
                SendPack_Short(SendBackDIY,DIY_Para_2, 100, 1, 1);
                SendPack_Short(SendBackDIY,DIY_Para_3, 10.2, 1, 1);
               
                _wholesettings[0].need_Send = 0;
            }     
          
              //========================================================
              //========================================================
              //����ͣ������������������������
              if(_wholesettings[1].need_Send == 1)
              {
                  //�ر���Ҫ�رյ��ж�
                  //disable_irq(PORTE_IRQn);
                  
//                  //�ر����
//                  ftm_pwm_duty(FTM0, FTM_CH0, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH1, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH2, 1000);
//                  ftm_pwm_duty(FTM0, FTM_CH3, 1000);
                  
                  SendPack_Echo(9, 1, "ACK");
              }
              //========================================================
        }
        
        //=======================================================
        //������������
        //=======================================================
        //����ͷͼ��
        //SendPack_Camera(Camera, Camera_1, imgbuff, CAMERA_SIZE);
        //****************************************
        //CCDͼ��
        //SendPack_CCD(2, 1, (uint8_t *)&CCD_BUFF[0], TSL1401_SIZE, 1, 1);
        //****************************************
        //ʵʱ����
        //SendPack_Short(Electricity,Electricity_1, /*��ı�����*/ 0, 1, 0);
        //****************************************
        //ʵʱ����
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