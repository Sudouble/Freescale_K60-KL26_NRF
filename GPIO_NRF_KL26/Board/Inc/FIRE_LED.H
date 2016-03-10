 /*!
  *     COPYRIGHT NOTICE
  *     Copyright (c) 2013,Ұ��Ƽ�
  *     All rights reserved. 
  *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
  *
  *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ������������������ҵ��;��
  *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
  *
  * @file       FIRE_LED.h
  * @brief      led����ͷ�ļ�
  * @author     Ұ��Ƽ�
  * @version    v5.0
  * @date       2013-07-9
  */

#ifndef __FIRE_LED_H__
#define __FIRE_LED_H__


/*! ö��LED��� */
typedef enum
{
  LED0,
  LED1,
  LED2,
  LED3,
  LED_MAX,
}LED_e;

/*! ö��LED����״̬ */
typedef enum LED_status
{
  LED_ON  =   0,            //����(��Ӧ�͵�ƽ)
  LED_OFF =   1             //�ư�(��Ӧ�ߵ�ƽ)
}LED_status; 


extern void    led_init(LED_e);            //��ʼ��LED�˿�
extern void    led(LED_e,LED_status);      //����LED������
extern void    led_turn(LED_e);            //����LED������ת

#endif  //__FIRE_LED_H__