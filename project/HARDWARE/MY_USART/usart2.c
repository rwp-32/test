#include "include.h"
#include  "usart2.h"


#if EN_USART2_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	  
  
void uart2_init(u32 bound){
    //GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
		//USART2_TX   P2
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		//USART2_RX	  P3
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}

void USART2_IRQHandler(void)                	//����1�жϷ������
	{
//	u8 Res;
		
		unsigned char Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	   	
		
		Res =USART_ReceiveData(USART2);
		uart_receive_input(Res);
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//			Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
//			uart_receive_input(Res);
//			printf("%c\n",Res);
//		}
//		if((USART2_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART2_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
//				else USART2_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART2_RX_STA|=0x4000;
//				else
//					{
//					USART2_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					uart_receive_input(Res);
//					printf("%x\n",Res);
//					USART2_RX_STA++;
//					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
//     } 
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif

//����2ֱ�ӷ����ַ�����
void  uart2_send_data(char *data)
{
	
	while(*data!=NULL)					
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); 
		USART_SendData(USART2,*data); 
		data++;
	}
	
}



