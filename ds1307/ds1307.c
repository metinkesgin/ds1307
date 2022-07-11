/*
 * ds1307.c
 *
 *  Created on: Jul 10, 2022
 *      Author: metin
 */
#include "ds1307.h"

void RTC_init(I2C_HandleTypeDef* i2c,RTC_t* rtc){

	rtc->date = 1;
	rtc->day = SUNDAY;
	rtc->hour = 1;
	rtc->minute = 1;
	rtc->month = JANUARY;
	rtc->second = 1;
	rtc->year = 1;
	rtc->i2c = i2c;
	RTC_BufferReset(rtc);
	HAL_Delay(20);
}

void RTC_WriteRegister(RTC_t* rtc,uint8_t address,uint8_t value){
	HAL_I2C_Mem_Write(rtc->i2c , DS1307_ADDRESS, address, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);
}
void RTC_ReadRegister(RTC_t* rtc,uint8_t address,uint8_t byte){
	HAL_I2C_Mem_Read(rtc->i2c, DS1307_ADDRESS, address, I2C_MEMADD_SIZE_8BIT, &byte, 1, 100);
}
void RTC_setSecond(RTC_t* rtc ,uint8_t value){
	RTC_WriteRegister(rtc, DS1307_SECOND, EncodeBCD(value));

}
void RTC_setMinute(RTC_t* rtc ,uint8_t value){
	RTC_WriteRegister(rtc, DS1307_MINUTE, EncodeBCD(value));
}
void RTC_setHour(RTC_t* rtc,uint8_t value ){
	RTC_WriteRegister(rtc, DS1307_HOUR, EncodeBCD(value));
}
void RTC_setDay(RTC_t* rtc ,days_t value){
	RTC_WriteRegister(rtc, DS1307_DAY, EncodeBCD((uint8_t)value));
}
void RTC_setDate(RTC_t* rtc ,uint8_t value){
	RTC_WriteRegister(rtc, DS1307_DATE, EncodeBCD(value));
}
void RTC_setMonth(RTC_t* rtc ,months_t value){
	RTC_WriteRegister(rtc, DS1307_MONTH, EncodeBCD((uint8_t)value));
}
void RTC_setYear(RTC_t* rtc ,uint8_t value){
	RTC_WriteRegister(rtc, DS1307_YEAR, EncodeBCD(value));
}
void RTC_BufferReset(RTC_t* rtc){
	for (int i = 0; i < BUFFER_LENGTH; i++) {
		rtc->buffer[i] = 0;
	}
}
uint8_t DecodeBCD(uint8_t bin) {
	return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}
uint8_t EncodeBCD(uint8_t dec) {
	return (dec % 10 + ((dec / 10) << 4));
}

void RTC_ReadALL(RTC_t *rtc){
	HAL_I2C_Mem_Read(rtc->i2c, DS1307_ADDRESS, DS1307_SECOND, I2C_MEMADD_SIZE_8BIT, rtc->buffer, 7, 100);
	rtc->second = DecodeBCD(rtc->buffer[0]);
	rtc->minute = DecodeBCD(rtc->buffer[1]);
	rtc->hour   = DecodeBCD(rtc->buffer[2]);
	rtc->day    = DecodeBCD(rtc->buffer[3]);
	rtc->date   = DecodeBCD(rtc->buffer[4]);
	rtc->month  = DecodeBCD(rtc->buffer[5]);
	rtc->year   = DecodeBCD(rtc->buffer[6]);
	rtc->size = sprintf(rtc->print,"20%u:%u:%u:%u:%u:%u:%u\n",rtc->year,rtc->month,rtc->date,rtc->hour,rtc->minute,rtc->second);
	RTC_BufferReset(rtc);
}

