#include "stm32f4xx_hal.h"
#include "ili9341.h"


SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
void MX_SPI1_Init(void);
void ili9341_writecmd(uint8_t cmd);
void ili9341_writedata(uint8_t data);
void ili9341_setaddr(uint8_t x1,uint8_t y1,uint16_t x2,uint16_t y2);
void ili9341_init(void);
void ili9341_fill(uint16_t color);
void ili9341_draw(uint8_t *buff);

void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  HAL_SPI_Init(&hspi1);

}

void ili9341_writecmd(uint8_t cmd)
{
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);	//DC to 0
HAL_SPI_Transmit(&hspi1,&cmd,1,1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);	//DC to 1
}

void ili9341_writedata(uint8_t data)
{
HAL_SPI_Transmit(&hspi1,&data,1,1000);
}

void ili9341_init(void)
{
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);	//RESET to 0
HAL_Delay(100);	
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);	//RESET to 1

ili9341_writecmd(0xCB);
ili9341_writedata(0x39);
ili9341_writedata(0x2C);
ili9341_writedata(0x00);
ili9341_writedata(0x34);
ili9341_writedata(0x02);

ili9341_writecmd(0xCF);  
ili9341_writedata(0x00); 
ili9341_writedata(0XC1); 
ili9341_writedata(0X30);
	
 HAL_Delay(10);
	
ili9341_writecmd(0xE8);  
ili9341_writedata(0x85); 
ili9341_writedata(0x00); 
ili9341_writedata(0x78); 
 
ili9341_writecmd(0xEA);  
ili9341_writedata(0x00); 
ili9341_writedata(0x00); 

ili9341_writecmd(0xED);  
ili9341_writedata(0x64); 
ili9341_writedata(0x03); 
ili9341_writedata(0X12); 
ili9341_writedata(0X81);

ili9341_writecmd(0xF7);  
ili9341_writedata(0x20); 

ili9341_writecmd(0xC0);    //Power control 
ili9341_writedata(0x23);   //VRH[5:0] 

ili9341_writecmd(0xC1);    //Power control 
ili9341_writedata(0x10);   //SAP[2:0];BT[3:0] 

ili9341_writecmd(0xC5);    //VCM control 
ili9341_writedata(0x3e);   //Contrast
ili9341_writedata(0x28); 

ili9341_writecmd(0xC7);    //VCM control2 
ili9341_writedata(0x86);   //--

ili9341_writecmd(0x36);    // Memory Access Control 
ili9341_writedata(0x28);   //RGB565 Horizontal orientation
//ili9341_writedata(0x08);   //RGB565 Vertical orientation

ili9341_writecmd(0x3A);    
ili9341_writedata(0x55); 

ili9341_writecmd(0xB1);    
ili9341_writedata(0x00);  
ili9341_writedata(0x18); 

ili9341_writecmd(0xB6);    // Display Function Control 
ili9341_writedata(0x08); 
ili9341_writedata(0x82);
ili9341_writedata(0x27);  

ili9341_writecmd(0x11);    //Exit Sleep 
HAL_Delay(100); 
ili9341_writecmd(0x29);    //Display on 
ili9341_writecmd(0x2c);

}

void ili9341_setaddr(uint8_t x1,uint8_t y1,uint16_t x2,uint16_t y2)
{
ili9341_writecmd(0x2A);
ili9341_writedata(x1>>8);
ili9341_writedata(x1);
ili9341_writedata(x2>>8);
ili9341_writedata(x2);
	
ili9341_writecmd(0x2B);
ili9341_writedata(y1>>8);
ili9341_writedata(y1);
ili9341_writedata(y2>>8);
ili9341_writedata(y2);
	
ili9341_writecmd(0x2C);
}

void ili9341_fill(uint16_t color)
{

}

void ili9341_draw(uint8_t *buff)
{
ili9341_setaddr(0,0,153,144);//11088 for 153*144
HAL_SPI_Transmit_DMA(&hspi1,buff,44352);
}

