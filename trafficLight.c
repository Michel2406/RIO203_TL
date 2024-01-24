/*
 * main.c
 * 
 * Copyright 2023  <samuel2406@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, writeData to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "writeData.h"

#define LedPinRed 0
#define LedPinGreen 1
#define LedPinBlue 2


void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen, 0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(unsigned char r_val, unsigned char g_val, unsigned char b_val)
{	
	softPwmWrite(LedPinRed,   0xff-r_val);
	softPwmWrite(LedPinGreen, 0xff-g_val);
	softPwmWrite(LedPinBlue, 0xff-b_val);
}

int main(void)
{
	char * filename = "data.json";
	char * data;
	int ret_writeData;
	printf("Traffic Light simulation\n");
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	ledInit();
	dataToSend = malloc(sizeof(JsonData));

	dataToSend->latitude = 48.71299;
	dataToSend->longitude = 2.20034;
	dataToSend->color = NULL;

	writeData(filename, "gps", dataToSend);

	while(1){
		ledColorSet(0xff,0x0,0x0);//Red
		dataToSend->color = "Red";
		writeData(filename, "color", dataToSend);
		delay(3000);

		ledColorSet(0x0,0xff,0x0);  //Green
		dataToSend->color = "Green";
		writeData(filename, "color", dataToSend);
		delay(3000);

		ledColorSet(0xff, 0xff, 0x0);//yellow
		dataToSend->color = "Yellow";
		writeData(filename, "color", dataToSend);
		delay(3000);
	}

	free(dataToSend);

	return 0;
}

