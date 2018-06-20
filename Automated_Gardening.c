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


#include "adc.h"
#include "lcd.h"
#include "pwm.h"

int main()
{

	adc_init();	//initializing the adc
	lcd_init();	//initializing the lcd
	pwm_init();	//initializing the pwm
	
	int a,b,c;
	
	while (1)
	{
	
	a=adc_read(0);		//Soil_Sensor is connected to PortA pin0
	b=adc_read(1);		//LM35 is connected to POrtA pin1
	b=b*0.488;			//converting value from lm35 to degree C 
	c=read(portd,0);	//taking input from PIR sensor
	
	
	
	
	
	for(int i=1;i<=2;i++)
	{
		if(i==1)
		{
			a=adc_read(0);
            while(a>2000)
			{
	
				pwm(180);
		
				write(portb,7,h);
		
				write(portd,6,h);
				write(portd,7,l);
		

				lcd_gotoxy(0,0);	//lcd_gotoxy(column,row);
				lcd_string("Wat.");
				
				lcd_gotoxy(0,1);
				lcd_num(a);
                a=adc_read(0);

			}

	
	
			if(a<2000)	//if the soil doesn't require water, it will stay in this loop
			{
			
				
				write(portd,6,l);	//turning off the motor
				write(portd,7,l);
				
				write(portb,7,l);	//turning off the power supply
				

				lcd_gotoxy(0,0);	//lcd_gotoxy(column,row)
				lcd_string("Mois");
                lcd_gotoxy(0,1);
                lcd_num(a);
                a=adc_read(0);
			
			}
			
		
		}
		
		if(i==2)
		{
			c=read(portd,0);
            
            while(c==1)	//bird detection
			{
				write(portb,7,h);
				write(portd,4,h);
				write(portd,5,l);
				
				
				lcd_gotoxy(12,0);
                lcd_string("PIR");
                lcd_gotoxy(12,1);
				lcd_num(c);
                c=read(portd,0);
			}
			
			if(c==0)
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