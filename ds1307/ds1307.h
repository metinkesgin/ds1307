/*
 * ds1307.h
 *
 *  Created on: Jul 10, 2022
 *      Author: metin
 */

#ifndef INC_DS1307_H_
#define INC_DS1307_H_


#include "stdint.h"
#include "main.h"

#define DS1307_ADDRESS 0x68 << 1
#define DS1307_SECOND  0X00
#define DS1307_MINUTE  0X01
#define DS1307_HOUR    0X02
#define DS1307_DAY     0X03
#define DS1307_DATE    0X04
#define DS1307_MONTH   0X05
#define DS1307_YEAR    0X06
#define BUFFER_LENGTH  7

typedef enum {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,

}months_t;

typedef enum {
	SUNDAY = 1,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THORSDAY,
	FRİDAY,
	SATURDAY,
}days_t;

typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t second; // 00-59
	uint8_t minute; // 00-59
	uint8_t hour;   // 00-24
	days_t day;	    // 01-07
	uint8_t date;	// 01-31
	months_t month;	// 01-12
	uint8_t year;	// 00-99
	uint8_t buffer[BUFFER_LENGTH];
	char* print;
	uint8_t size;
}RTC_t;

void RTC_init(I2C_HandleTypeDef*,RTC_t*);
uint8_t RTC_getSecond(RTC_t*);
void RTC_setSecond(RTC_t*,uint8_t);
void RTC_setMinute(RTC_t*,uint8_t);
void RTC_setHour(RTC_t*,uint8_t);
void RTC_setDay(RTC_t*,days_t);
void RTC_setDate(RTC_t*,uint8_t);
void RTC_setMonth(RTC_t*,months_t);
void RTC_setYear(RTC_t*,uint8_t);
void RTC_WriteRegister(RTC_t*,uint8_t,uint8_t);
void RTC_ReadRegister(RTC_t*,uint8_t,uint8_t);
void RTC_BufferReset(RTC_t*);
void RTC_ReadALL(RTC_t*);
uint8_t DecodeBCD(uint8_t);
uint8_t EncodeBCD(uint8_t);


#endif /* INC_DS1307_H_ */
