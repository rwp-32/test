#include "myiic.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


float humiture[4];        //ʵ����ʪ����ֵ
//u8 Refresh_SHT30_Data=0;
u8 humiture_buff1[20];
u8 humiture_buff2[20];

//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//  SCL=1;
//  SDA_OUT =1;
	
	IIC_SCL=1;
	IIC_SDA=1;

}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


void Measure_Sh30(unsigned char model,union16  *value)
{
	int i;
	IIC_Start();
  IIC_Send_Byte(0x80);
	//IIC_Send_Byte(mode);
	i =600;
	while(i--)
		//delay_x_us();
	  delay_us(1);
	IIC_Start();
	IIC_Send_Byte(0x80+1);
	value->uchar[HSB]= IIC_Read_Byte(1);
  IIC_Ack();
	value->uchar[LSB]= IIC_Read_Byte(1);
	IIC_NAck();
	IIC_Stop();
}

//  ��ʪ�Ȼ�ȡ����
void  SHT30_read_result_myiic(u8 addr)
{
	u8 test;
	u16 tem,hum;
	u16 buff[6];
	float Temperature = 0;
	float Humidity =0;
	
	
	IIC_Start();
	IIC_Send_Byte(addr<<1 | 0);
	test =IIC_Wait_Ack();
	printf("SHT30 Ӧ���Ƿ�ɹ��� %d\n",test);	
	IIC_Send_Byte(0x2C);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x06);
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(50);
	IIC_Start();
	IIC_Send_Byte(addr<<1 | 1);
	if(IIC_Wait_Ack()==0)
	{	
		buff[0]=IIC_Read_Byte(1);
		buff[1]=IIC_Read_Byte(1);
		buff[2]=IIC_Read_Byte(1);
		buff[3]=IIC_Read_Byte(1);
		buff[4]=IIC_Read_Byte(1);
		buff[5]=IIC_Read_Byte(0);
		IIC_Stop();				
	}
	tem = ((buff[0]<<8)|buff[1]);
	hum = ((buff[3]<<8)|buff[4]);
	
//ת��ʵ���¶�
	Temperature =(175.0*(float)tem/65535.0-45);
	Humidity = (100.0*(float)hum/65535.0);

	//���˴������Ϣ
	if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))
	{
		memset(humiture,0,sizeof(humiture));
		humiture[0] = Temperature;
		humiture[2] = Humidity;
		printf("��ʪ�ȣ�%f  %f \n",humiture[0],humiture[2]);
		sprintf(humiture_buff1,"%6.2f*C   %6.2f%%",Temperature,Humidity);	
	}
	printf("��ʪ�ȣ�%s\n",humiture_buff1);	
	hum =0;
	tem =0;
}
