#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

typedef struct 
{
	uint8_t second;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}Date_time;

typedef struct 
{
	I2C_HandleTypeDef *_hi2c;
	Date_time dt;
}RTC_Typedef;


void RTC_Writetime(RTC_Typedef *rtc);
void RTC_Readtime(RTC_Typedef *rtc);
void RTC_init(RTC_Typedef *rtc, I2C_HandleTypeDef *hi2c_);
#endif
