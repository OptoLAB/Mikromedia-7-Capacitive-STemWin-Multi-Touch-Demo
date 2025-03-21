/*
J. Bajic - 2020.
*/

#ifndef SSD1963_H
#define SSD1963_H

#include "stm32f7xx_hal.h"

/* Port */
//init Display GPIO with STM32Cube
//Activate CRC
//DISP_DATA
#define DATA_PORT	GPIOG
//DISP_RST
#define RST_PORT	GPIOF
#define RST_PIN		GPIO_PIN_12
//DISP_CS
#define CS_PORT		GPIOF
#define CS_PIN		GPIO_PIN_13
//DISP_DC
#define DC_PORT		GPIOF
#define DC_PIN		GPIO_PIN_14
//DISP_RD
#define RD_PORT		GPIOF
#define RD_PIN		GPIO_PIN_15
//DISP_WR
#define WR_PORT		GPIOJ
#define WR_PIN		GPIO_PIN_3

/* SSD1963 commands */
#define SSD1963_NOP							0x0000
#define SSD1963_SOFT_RESET  				0x0001
#define SSD1963_GET_POWER_MODE 				0x000A
#define SSD1963_GET_ADDRESS_MODE			0x000B
#define SSD1963_GET_DISPLAY_MODE			0x000D
#define SSD1963_GET_TEAR_EFFECT_STATUS 		0x000E
#define SSD1963_ENTER_SLEEP_MODE			0x0010
#define SSD1963_EXIT_SLEEP_MODE				0x0011
#define SSD1963_ENTER_PARTIAL_MODE			0x0012
#define SSD1963_ENTER_NORMAL_MODE			0x0013
#define SSD1963_EXIT_INVERT_MODE			0x0020
#define SSD1963_ENTER_INVERT_MODE			0x0021
#define SSD1963_SET_GAMMA_CURVE				0x0026
#define SSD1963_SET_DISPLAY_OFF				0x0028
#define SSD1963_SET_DISPLAY_ON				0x0029
#define SSD1963_SET_COLUMN_ADDRESS			0x002A
#define SSD1963_SET_PAGE_ADDRESS			0x002B
#define SSD1963_WRITE_MEMORY_START			0x002C
#define SSD1963_READ_MEMORY_START			0x002E
#define SSD1963_SET_PARTIAL_AREA			0x0030
#define SSD1963_SET_SCROLL_AREA				0x0033
#define SSD1963_SET_TEAR_OFF				0x0034
#define SSD1963_SET_TEAR_ON					0x0035
#define SSD1963_SET_ADDRESS_MODE			0x0036
#define SSD1963_SET_SCROLL_START			0x0037
#define SSD1963_EXIT_IDLE_MODE				0x0038
#define SSD1963_ENTER_IDLE_MODE				0x0039
#define SSD1963_SET_PIXEL_FORMAT			0x003A
#define SSD1963_WRITE_MEMORY_CONTINUE		0x003C
#define SSD1963_READ_MEMORY_CONTINUE		0x003E
#define SSD1963_SET_TEAR_SCANLINE			0x0044
#define SSD1963_GET_SCANLINE				0x0045
#define SSD1963_READ_DDB					0x00A1
#define SSD1963_SET_LCD_MODE				0x00B0
#define SSD1963_GET_LCD_MODE				0x00B1
#define SSD1963_SET_HORI_PERIOD				0x00B4
#define SSD1963_GET_HORI_PERIOD				0x00B5
#define SSD1963_SET_VERT_PERIOD				0x00B6
#define SSD1963_GET_VERT_PERIOD				0x00B7
#define SSD1963_SET_GPIO_CONF				0x00B8
#define SSD1963_GET_GPIO_CONF				0x00B9
#define SSD1963_SET_GPIO_VALUE				0x00BA
#define SSD1963_GET_GPIO_STATUS				0x00BB
#define SSD1963_SET_POST_PROC				0x00BC
#define SSD1963_GET_POST_PROC				0x00BD
#define SSD1963_SET_PWM_CONF				0x00BE
#define SSD1963_GET_PWM_CONF				0x00BF
#define SSD1963_GET_GDISP_GEN0				0x00C0
#define SSD1963_SET_GDISP_GEN0				0x00C1
#define SSD1963_GET_GDISP_GEN1				0x00C2
#define SSD1963_SET_GDISP_GEN1				0x00C3
#define SSD1963_GET_GDISP_GEN2				0x00C4
#define SSD1963_SET_GDISP_GEN2				0x00C5
#define SSD1963_GET_GDISP_GEN3				0x00C6
#define SSD1963_SET_GDISP_GEN3				0x00C7
#define SSD1963_SET_GPIO0_ROP				0x00C8
#define SSD1963_GET_GPIO0_ROP				0x00C9
#define SSD1963_SET_GPIO1_ROP				0x00CA
#define SSD1963_GET_GPIO1_ROP				0x00CB
#define SSD1963_SET_GPIO2_ROP				0x00CC
#define SSD1963_GET_GPIO2_ROP				0x00CD
#define SSD1963_SET_GPIO3_ROP				0x00CE
#define SSD1963_GET_GPIO3_ROP				0x00CF
#define SSD1963_SET_DBC_CONF				0x00D0
#define SSD1963_GET_DBC_CONF				0x00D1
#define SSD1963_SET_DBC_TH					0x00D4
#define SSD1963_GET_DBC_TH					0x00D5
#define SSD1963_SET_PLL						0x00E0
#define SSD1963_SET_PLL_MN					0x00E2
#define SSD1963_GET_PLL_MN					0x00E3
#define SSD1963_GET_PLL_STATUS				0x00E4
#define SSD1963_SET_DEEP_SLEEP				0x00E5
#define SSD1963_SET_LSHIFT_FREQ				0x00E6
#define SSD1963_GET_LSHIFT_FREQ				0x00E7
#define SSD1963_SET_PIXEL_DATA_INTERFACE 	0x00F0
	#define SSD1963_PDI_8BIT			0
	#define SSD1963_PDI_12BIT			1
	#define SSD1963_PDI_16BIT			2
	#define SSD1963_PDI_16BIT565		3
	#define SSD1963_PDI_18BIT			4
	#define SSD1963_PDI_24BIT			5
	#define SSD1963_PDI_9BIT			6
#define SSD1963_GET_PIXEL_DATA_INTERFACE 	0x00F1

#define SSD1963_ADDR_MODE_FLIP_VERT           (1 << 0)
#define SSD1963_ADDR_MODE_FLIP_HORZ           (1 << 1)
#define SSD1963_ADDR_MODE_LATCH_RIGHT_TO_LEFT (1 << 2)
#define SSD1963_ADDR_MODE_BGR                 (1 << 3)
#define SSD1963_ADDR_MODE_REFRESH_BOTTOM_UP   (1 << 4)
#define SSD1963_ADDR_MODE_PAG_COL_ADDR_ORDER  (1 << 5)
#define SSD1963_ADDR_MODE_COL_ADDR_ORDER      (1 << 6)
#define SSD1963_ADDR_MODE_PAGE_ADDR_ORDER     (1 << 7)

/*Port*/
#define SET_RST                 RST_PORT->BSRR = RST_PIN
#define CLR_RST                 RST_PORT->BSRR = (uint32_t)RST_PIN << 16
#define SET_CS                  CS_PORT->BSRR = CS_PIN
#define CLR_CS                  CS_PORT->BSRR = (uint32_t)CS_PIN << 16
#define SET_DC                  DC_PORT->BSRR = DC_PIN
#define CLR_DC                  DC_PORT->BSRR = (uint32_t)DC_PIN << 16
#define SET_RD                  RD_PORT->BSRR = RD_PIN
#define CLR_RD                  RD_PORT->BSRR = (uint32_t)RD_PIN << 16
#define SET_WR                  WR_PORT->BSRR = WR_PIN
#define CLR_WR                  WR_PORT->BSRR = (uint32_t)WR_PIN << 16

#define writeStrobe             { CLR_WR; asm("NOP"); SET_WR; }


/*TFT 800x480*/
#define TFT_FPS 60ULL
#define TFT_WIDTH				800ULL
#define TFT_HSYNC_BACK_PORCH	42ULL
#define TFT_HSYNC_FRONT_PORCH	8ULL
#define TFT_HSYNC_PULSE			2ULL

#define TFT_HEIGHT				480ULL
#define TFT_VSYNC_BACK_PORCH	11ULL
#define TFT_VSYNC_FRONT_PORCH	6ULL
#define TFT_VSYNC_PULSE			6ULL


#define	TFT_HSYNC_PERIOD	(TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH + TFT_WIDTH  + TFT_HSYNC_FRONT_PORCH)
#define	TFT_VSYNC_PERIOD	(TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH + TFT_HEIGHT + TFT_VSYNC_FRONT_PORCH)

#define TFT_PCLK			(TFT_HSYNC_PERIOD * TFT_VSYNC_PERIOD * TFT_FPS)

#define LCD_FPR				((TFT_PCLK * 1048576)/100000000)
#define mHIGH(x) 			(x >> 8)
#define mLOW(x) 			(x & 0xFF)

//--------------------------------------------------------------------------------
void SSD1963_WriteCommand(uint16_t Data);
void SSD1963_WriteData(uint16_t Data);
void SSD1963_WriteDataMultiple(uint16_t *Data, int NumItems);
uint16_t SSD1963_ReadData(void);
void SSD1963_ReadDataMultiple(uint16_t *Data, int NumItems);
void SSD1963_Init(void);
void SSD1963_SetArea(uint16_t sx, uint16_t ex, uint16_t sy, uint16_t ey);
void SSD1963_FillArea(uint16_t sx, uint16_t ex, uint16_t sy, uint16_t ey, uint16_t color);
void SSD1963_ClearScreen(uint16_t color);
void SSD193_SetPixel(uint16_t x, uint16_t y, uint16_t color);
void SSD1963_SetBacklight(uint8_t BL);
void SSD1963_SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom);
void SSD1963_SetScrollStart(uint16_t line);
//--------------------------------------------------------------------------------

#endif
