#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////	 
////������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
////Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
////�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////// 	  

   	   		   
//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������	 
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //����SDA 

#define SALVE_ADDR 0x80
#define  HSB 0
#define  LSB  1


#define HUMI_HOLD_MASTER  0xE5
#define TEMP_HOLD_MASTER  0xE3

extern float humiture[4];  
extern u8 humiture_buff1[20];
extern u8 humiture_buff2[20];



typedef  union union16_
{
	unsigned int uint;
	unsigned char uchar[2];
}union16;

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void  SHT30_read_result_myiic(u8 addr);  // ��ȡ��ʪ�Ⱥ��� 
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

void Measure_Sh30(unsigned char model,union16 *value); 
#endif
















