#include  "include.h"


//#include  "lcd_play.h"
//#include  "lcd.h"
//#include  "myiic.h"


/******************************************************************************
      ����˵����LCDz��ʾ��ʪ��ֵ
      ������ݣ�tem_x,tem_y   �¶�ֵ��ʼ���� 75
								hum_x,hum_y   ʪ��ֵ����ʼ���� 110
                index ���ֵ����
                size  �ֺ�  ��С
								u16 color ������ɫ����
      ����ֵ��  ��
******************************************************************************/
/* void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color)	*/


//���� ����ʪ����ʾ��LCD
void  humiture_display(u16 tem_y,u16 hum_y,u8 size,u16 color )
{
		
    	SHT30_read_result_myiic(0x44);
		 	LCD_ShowChinese(10,tem_y,11,size,color);   //��
			LCD_ShowChinese(45,tem_y,12,size,color);   //��
	    LCD_ShowNum1(80,tem_y,humiture[0],4,color);//�޸��¶�ֵ
			LCD_ShowChar(150,tem_y,'C',size,color);
	
	
			LCD_ShowChinese(10,hum_y,13,size,color);   //ʪ
			LCD_ShowChinese(45,hum_y,12,size,color);   //��
	    LCD_ShowNum1(80,hum_y,humiture[2],4,color);//�޸��¶�ֵ
			LCD_ShowChar(150,hum_y,'%',size,color);
	
//			LCD_ShowChinese(10,90,14,16,RED);   //԰
//			LCD_ShowChinese(45,90,15,16,RED);  //��
    



}