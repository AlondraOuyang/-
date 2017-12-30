


#include  "flash.h"
#include "stm32f10x_flash.h"
#include "led.h"

#define STM32_FLASH_BASE  0x08000000  

extern u8 g_flag;



 
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  


 uint16_t STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}

 #if 1
void STMFLASH_Write(u32 WriteAddr,u16 Value)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr < STM32_FLASH_BASE || WriteAddr % 4) 
	{
		return ;
	}
	FLASH_Unlock();									 //���� CR�Ĵ���
  FLASH_DataCacheCmd(DISABLE);     //FLASH�����ڼ�,�����ֹ���ݻ���
 	
	addrx=WriteAddr;				         //д�����ʼ��ַ
	endaddr=WriteAddr+4;	           //д��Ľ�����ַ
	
	if(addrx<0X1FFF0000)			       //ֻ�����洢��,����Ҫִ�в�������!!
	{
		while(addrx<endaddr)		       //ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)   //�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);  //VCC=2.7~3.6V֮��!!
				if(status!=FLASH_COMPLETE)break;	  //����������
			}
			else addrx +=4;
		} 
	}
	
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)
		{
		 if(FLASH_ProgramWord(WriteAddr,Value)!=FLASH_COMPLETE)//д������
			{ 
				break;	//д���쳣
			}
		FLASH_ProgramWord(WriteAddr,Value);  
		FLASH_DataCacheCmd(ENABLE);
	  FLASH_Lock();
		}
 }
}
  
#endif
	
#if 0
void STMFLASH_Clear(void)
 {
	 uint32_t clearAddr = 0x0800C004;
   while(clearAddr<=0x080FFFFF)
	{
	 FLASH_Status status = FLASH_COMPLETE;
	
	  u32 start_addrx;
	  u32 end_addr;	
    if(clearAddr < STM32_FLASH_BASE || clearAddr % 4) return ;
	  FLASH_Unlock();									 
    FLASH_DataCacheCmd(DISABLE);   
 	
	  start_addrx=clearAddr;				       
	  end_addr=clearAddr+4;	
	
	  if(start_addrx<0X1FFF0000)			     
	 {
		while(start_addrx<end_addr)		     
		
		{
			if(STMFLASH_ReadWord(start_addrx)!=0XFFFFFFFF)   
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(start_addrx),VoltageRange_3); 
				if(status!=FLASH_COMPLETE)
					break;	 
			}
			else 
				start_addrx +=4;
		} 
	 }
	
	 clearAddr+=4;
	 
	 if(clearAddr >= 0x080FFFFF)
	 {
		turn_led(LED5,OFF);
	  g_flag = 0;
	 }
 }

}
#endif


u32  STMFLASH_Read(u32 ReadAddr)   	
{
     
	   u32  pBuffer;
		 
	   pBuffer=STMFLASH_ReadWord(ReadAddr);
     
	   return pBuffer;
   
}
