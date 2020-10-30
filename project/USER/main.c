//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : LCD SPI�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND     ��Դ��
//              VCC     3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2
//              DC   PA3
//              CS   PA4   
//							BLK  PA5 ���Ʊ���
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
//All rights reserved
//******************************************************************************/


#include  "include.h"
#include  "system.h"
typedef struct Sht30_value
{
	union16  temp;
	union16  humi;
	unsigned char  crc;
}sht30_value_ST,*p_sht_value_ST;

sht30_value_ST   gv_sht30_value;   

int main(void)
 {	
	 delay_init();	    	 //��ʱ������ʼ��	  
	 NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 Lcd_Init();			//��ʼ��OLED 
	 IIC_Init();	 
   uart_init(9600);
	 uart2_init(9600);
	 LCD_Clear(WHITE);
	 BACK_COLOR=WHITE;
	 LED_ON;
	 bt_protocol_init();
	 while(1)
	 {
		 	LCD_ShowChinese(45,0,5,32,RED);   //��
			LCD_ShowChinese(80,0,6,32,RED);   //��
			LCD_ShowChinese(115,0,7,32,RED);   //԰
			LCD_ShowChinese(155,0,3,32,RED);  //��
		  humiture_display(75,110,16,BLACK);
	    bluetooth_to_scrawl();
   }
}