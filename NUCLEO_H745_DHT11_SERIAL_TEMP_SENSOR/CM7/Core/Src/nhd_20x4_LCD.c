//-KB,-5-11-202-
//nhd_20x4_LCD.c

#include <nhd_20x4_LCD.h>
#include "stm32h7xx_hal.h"

/*********** Define the LCD PINS below ****************/

#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOD
#define RW_Pin GPIO_PIN_2
#define RW_GPIO_Port GPIOD
#define EN_Pin GPIO_PIN_3
#define EN_GPIO_Port GPIOD
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOD

//define the timer handler below
#define timer htim1

extern TIM_HandleTypeDef timer;
void five_ns_delay (int ns)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);	//clear timer
	HAL_TIM_Base_Start_IT(&timer);	//start timer
	while (__HAL_TIM_GET_COUNTER(&timer) < ns);
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //debugging LED
}

void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);  //rs = 1 for data, rs = 0 for command

	// write data to the respective pin

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data>>0)&0x01));

	lcd_nibble();	//pulse LCD enable pin to initiate data transfer
	//HAL_Delay(1);  	//wait for 1 ms while the enable pin settles

    //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //debugging LED
}

void lcd_send_cmd (char cmd)
{
    char datatosend;

    //send upper nibble first
    datatosend = ((cmd>>4)&0x0f);
	send_to_lcd(datatosend, 0);

    //send lower nibble
    datatosend = ((cmd)&0x0f);
    send_to_lcd(datatosend,0);  //RS must be 0 while sending command

    HAL_Delay(2);
}

void lcd_send_data (char data)
{
	char datatosend;

    //send upper nibble first
    datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);

    //send lower nibble
    datatosend = ((data)&0x0f);
    send_to_lcd(datatosend,1);  //RS must be 1 while sending data

    HAL_Delay(2);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col) //fix for 4x20 LCD !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
        case 2:
            col |= 0xE0;
            break;
        case 3:
            col |= 0xF0;
            break;
    }

    lcd_send_cmd (col);
}


void nhd_LCD_Init (void)
{
	//4 bit initialization
	HAL_Delay(50);  //wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  //wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  //wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  //4bit mode
	HAL_Delay(10);

	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); debugging LED

  //display initialization
	/*lcd_send_cmd (0x28); //Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x10); //Set Cursor
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x0);  //clear display
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	*/

	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)


}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_nibble() {
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	five_ns_delay(65);								//325ns enable pulse width delay
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); 	//debugging LED
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
}

