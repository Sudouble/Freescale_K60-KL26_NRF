 /*!
  *     COPYRIGHT NOTICE
  *     Copyright (c) 2013,Ұ��Ƽ�
  *     All rights reserved.
  *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
  *
  *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ������������������ҵ��;��
  *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
  *
  * @file       FIRE_LED.c
  * @brief      led��������ʵ��
  * @author     Ұ��Ƽ�
  * @version    v5.0
  * @date       2013-07-9
  */

/*
 * ����ͷ�ļ�
 */
#include "common.h"
#include "MKL_port.h"
#include "MKL_gpio.h"
#include "FIRE_LED.H"


/*
 * ����LED ��Ŷ�Ӧ�Ĺܽ�
 */
PTXn_e LED_PTxn[LED_MAX] = {PTD4,PTD5,PTD6,PTD7};


/*!
 *  @brief      ��ʼ��LED�˿�
 *  @param      LED_e    LED���
 *  @since      v5.0
 *  Sample usage:       LED_init (LED0);    //��ʼ�� LED0
 */
void    led_init(LED_e ledn)
{
    if(ledn < LED_MAX)
    {
        gpio_init(LED_PTxn[ledn],GPO,LED_OFF);
    }
    else
    {
        ledn = LED_MAX;
        while(ledn--)
        {
            gpio_init(LED_PTxn[ledn],GPO,LED_OFF);
        }

    }
}



/*!
 *  @brief      ����LED������
 *  @param      LED_e           LED��ţ�LED0��LED1��LED2��LED3��
 *  @param      LED_status      LED����״̬��LED_ON��LED_OFF��
 *  @since      v5.0
 *  Sample usage:       LED (LED0,LED_ON);    //���� LED0
 */
void    led(LED_e ledn,LED_status status)
{
    gpio_set(LED_PTxn[ledn],status);
}

/*!
 *  @brief      ����LED������ת
 *  @param      LED_e           LED��ţ�LED0��LED1��LED2��LED3��
 *  @since      v5.0
 *  Sample usage:       LED_turn (LED0);    // LED0������ת
 */
void led_turn(LED_e ledn)
{
    gpio_turn(LED_PTxn[ledn]);
}