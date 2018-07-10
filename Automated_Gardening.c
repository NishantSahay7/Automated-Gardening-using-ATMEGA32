/////////////////////////////////////////////////////////////////////////////////////////////////////
//  Project Name : Automated_Gardening
//
//  Target Board : atmega32
//
//  Date Created : 06-11-2017 12:56:07
// 
//  Online Resource  : www.electronicsforstudents.com
//
//  Libraries Included : 
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include<avr/io.h>
#include<util/delay.h>


#include "adc.h"	//Including ADC Library
#include "lcd.h"	//Including LCD Library
#include "pwm.h"	//Including PWM Library

int main()
{

	adc_init();	//initializing the ADC
	lcd_init();	//initializing the LCD
	pwm_init();	//initializing the PWM
	
	int a,b,c;
	
	while (1)
	{
	
	//---------Checking the value of different sensors connected---------------------------------
	
	a=adc_read(0);		//Soil_Sensor is connected to PortA pin0
	
	//Uncomment 'b' if you are using LM35 at Port A Pin 1
	//b=adc_read(1);		//LM35 is connected to POrtA pin1
	//b=b*0.488;		//converting value from lm35 to degree C 
	c=read(portd,0);	//taking input from PIR sensor, where PIR sensor is connected to PORTD Pin 0 
	
	
	//Giving two loops, i=1,2 for
	for(int i=1;i<=2;i++)
	{
		if(i==1)	//Loop1: Water Content detection
		{
			a=adc_read(0);
            	
			while(a>350)			//Here 350 is the moisture content of the soil given by the soil sensor, to decide what value your soil gives, checkc it in two conditions: once when it is wet and once when it is dry
			{
				pwm(180);		//For controlling the speed of water flow by motor
		
				write(portb,7,h);	//Switching on the relay, which is for turning on the Power 12v Power Supply for the motor driver
		
				write(portd,6,h);	//Turning the motor ON
				write(portd,7,l);
		

				lcd_gotoxy(0,0);	//lcd_gotoxy(column,row);
				lcd_string("Wat.");	// Means watering the plant
				
				lcd_gotoxy(0,1);
				lcd_num(a);
               			a=adc_read(0);
			}

	
			if(a<350)	//This loop is for turning of the motor and the power supplies
			{
			
				write(portd,6,l);	//turning off the motor
				write(portd,7,l);
				
				write(portb,7,l);	//turning off the power supply
				

				//Displaying respective messages
				
				lcd_gotoxy(0,0);	//lcd_gotoxy(column,row)
				lcd_string("Mois");
                		lcd_gotoxy(0,1);
                		lcd_num(a);
                		a=adc_read(0);
			}
			
		
		}
		
		if(i==2)	//Loop2: Observation for presence of Bird through PIR Sensor
		{
			c=read(portd,0);	//Getting the value from PIR Sensor
            
            		while(c==1)	//Enters loop if bird is detected
			{
				write(portb,7,h);	//Turns on Power supply
				write(portd,4,h);	//Turns on Second Motor
				write(portd,5,l);
				
				
				lcd_gotoxy(12,0);
                		lcd_string("PIR");
                		lcd_gotoxy(12,1);
				lcd_num(c);
              			c=read(portd,0);
			}
			
			if(c==0)	//If bird is not there, turns the motor and power supply off
			{
				write(portd,4,l);
				write(portd,5,l);
				
				write(portb,7,l);
				
				lcd_gotoxy(12,0);
              			lcd_string("PIR");
				lcd_gotoxy(12,1);
				lcd_num(c);
				
			}
			
			//CODE IF LM35 IS INTERFACED, REMOVE // AND USE
			//lcd_gotoxy(6,0);
			//lcd_string("LM35");
			//lcd_gotoxy(6,1);
			//lcd_num(b);
			//lcd_gotoxy(7,1);
			//lcd_string(" C");
			
			}
	}
	}

}
