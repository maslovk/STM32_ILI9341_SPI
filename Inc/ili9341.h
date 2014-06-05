#include "stm32f4xx_hal.h"

void MX_SPI1_Init(void);
void ili9341_writecmd(uint8_t cmd);
void ili9341_writedata(uint8_t data);
void ili9341_setaddr(uint8_t x1,uint8_t y1,uint16_t x2,uint16_t y2);
void ili9341_init(void);
void ili9341_fill(uint16_t color);
void ili9341_draw(uint8_t *buff);
