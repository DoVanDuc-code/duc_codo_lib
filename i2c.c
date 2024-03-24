#include "i2c.h"
#define Dev_Address 0x68<<1   // truyen co 7bit 
//extern I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef *_hi2c;
/*
//========================== HUONG DAN SU DUNG ==================================//
	- Thu vien nay co the dung cho 2 dong module realtime: DS3231, DS1307
	- Thu vien su dung hai ham de doc va ghi du lieu tai thang ghi cua realtime lan luot
	la RTC_Readtime && RTC_Writetime.
	- Cách dùng thu vien:
	+ Thu vien nay dùng cho nhieu cong I2C trên cùng 1 con vdk
	+ Khi add thu vien vào code chung ta can tao nen mot RTC_typedef _hi2c_;
	+ Viet ham khoi tao I2C bang ham: RTC_Init();
	+ Truyen vao các tham so moi cho Ic bat dau dem tu gia tri moi
	+ Sau khi IC bat dau dem thi cta comman nhung gia tri moi do lai.
	+ viet ham Write 
	+ viet ham read trong vong lap while(1)
	
*/
uint8_t decimal_to_bcd(uint8_t num)
{
	return (num / 10)<<4 | (num % 10);
}


uint8_t bcd_to_decimal(uint8_t num)
{
	return (num >> 4) * 10 + (num & 0x0f);
}

//===================================================//
void RTC_Writetime(RTC_Typedef *rtc)
{
	uint8_t buff[8];
	buff[0] = 0;
	buff[1] = decimal_to_bcd(rtc->dt.second);
	buff[2] = decimal_to_bcd(rtc->dt.min);
	buff[3] = decimal_to_bcd(rtc->dt.hour);
	buff[4] = decimal_to_bcd(rtc->dt.day);
	buff[5] = decimal_to_bcd(rtc->dt.date);
	buff[6] = decimal_to_bcd(rtc->dt.month);
	buff[7] = decimal_to_bcd(rtc->dt.year);
	HAL_I2C_Master_Transmit(_hi2c, Dev_Address, buff, 8, 200);
}

void RTC_Readtime(RTC_Typedef *rtc)
{
	uint8_t add_reg = 0;
	uint8_t buff[7];
	HAL_I2C_Master_Transmit(_hi2c, Dev_Address, &add_reg, 1, 100);
	HAL_I2C_Master_Receive(_hi2c, Dev_Address, buff, 7, 200);
	rtc->dt.second = bcd_to_decimal(buff[0]);
	rtc->dt.min = bcd_to_decimal(buff[1]);
	rtc->dt.hour = bcd_to_decimal(buff[2]);
	rtc->dt.day = bcd_to_decimal(buff[3]);
	rtc->dt.date = bcd_to_decimal(buff[4]);
	rtc->dt.month = bcd_to_decimal(buff[5]);
	rtc->dt.year = bcd_to_decimal(buff[6]);
}

void RTC_init(RTC_Typedef *rtc, I2C_HandleTypeDef *hi2c_)
{
	_hi2c = hi2c_;
}
