/*
 * app.c
 *
 * Created: 01/12/2022 16:57:21
 *  Author: Ayaya
 */ 

#include "app.h"

// Global variable for receiving the data sent by UART
static volatile char uart_data = 0;
// Global variable for the pressed key and stop flag that is used to stop the control mode
volatile static uint8_t data = 0 , stop_flag =0;

//initialization function // void setup
void app_init()
{
	// Initiating the LCD
	LCD_init();
	// Initiating Keypad
	KPD_init();
	// Initiating LEDs for temperature stats Low , Normal and High
	LED_init(LED_LOW);
	LED_init(LED_NORMAL);
	LED_init(LED_HIGH);
	// Initiating BUZZER for Fire alarm
	BUZZER_init(BUZZER_1);
	// Initiating EEPROM to save High and ?Low temperature values
	EEPROM_INIT();
	// Initiating ADC for temperature sensor
	ADC_init();
	// Initiating external interrupt 0 to sense the interrupt at the falling edge
	EXT_INT_0_init(falling_edge_sense);
	// Initiating UART with baud rate of 9600
	UART_Init(BAUD_RATE);
	UART_setCallBcak(func_RXC_ISR);
	UART_RXC_interruptEnable();
	// Initiating Timer0 --> PWM phase correct mode 
	timer0_init(PWM_PHASE_CORRECT_MODE, PRESCALAR_256);
	// Initiating button and set it as pull up
	button_init(BUTTON);
	button_set_pullUp(BUTTON);
	// Displaying project name on LCD at the start
	LCD_sendString("Temp. control");
	LCD_displayStringRowColumn(1,0, "Project");
	_delay_ms(300);
}
// void loop
void app_start()
{
	// Reading high and low temperature saved in EEPROM
	uint8_t t_high = EEPROM_READ(0x10 , EEPROM_ADRESS);
    uint8_t t_low = EEPROM_READ(0x20 , EEPROM_ADRESS);
	// LCD displays 1st and 2nd mode to select between them
	LCD_clear_screen();
	LCD_displayStringRowColumn(0,0, "1-Start Control");
	LCD_displayStringRowColumn(1,0, "2-Enter T values");
	while (1)
	{
		// stop flag value is 0 --> you can start control system 
		stop_flag = 0;
		// Getting the pressed key from Keypad
		data = KPD_get_key();
		// If data = 0 ---> Key not pressed --> do nothing till its pressed
		if (data != 0)
		{
			// Depending on the pressed key --> do the case 
			switch (data)
			{
				case '+':
					// Displays 2nd screen that shows the 3rd mode
					LCD_clear_screen();
					LCD_displayStringRowColumn(0,0, "3-Display T values");
					break;
				case '-':
					// Displays 1st screen that shows 1st and 2nd mode
					LCD_clear_screen();
					LCD_displayStringRowColumn(0,0, "1-Start Control");
					LCD_displayStringRowColumn(1,0, "2-Enter T values");
					break;
				case '1':
					// Start mode 1 ---> start controlling the system
					mode_1(t_high , t_low);
					break;
				case '2':
					// Start mode 2 ---> Take High and Low temperature values from the user throught Keypad
					// Then save it on the EEPROM
					mode_2(&t_high , &t_low);
					break;
				case '3':
					// Start mode 3 ---> Displayes High and Low temperature values saved on the EEPROM
					mode_3(t_high , t_low);
					break;
				case 'c':
					// Pressing 'on' stops the control system and returns you back to 1st screen
					LCD_clear_screen();
					LCD_displayStringRowColumn(0,0, "1-Start Control");
					LCD_displayStringRowColumn(1,0, "2-Enter T values");
					break;
				default:
					// Pressing anything other than previous cases returns you to 1st screen
					LCD_clear_screen();
					LCD_displayStringRowColumn(0,0, "1-Start Control");
					LCD_displayStringRowColumn(1,0, "2-Enter T values");
					break;
			}
		}
		
	}
}


// Mode 1 for Starting the control system
void mode_1(uint8_t temp_H , uint8_t temp_L)
{
	// Defining variables for ADC value and the current temperature read from the sensor
	uint32_t ADC_val = 0;
	uint8_t t_current = 0;
	
	LCD_clear_screen();
	// Control system will run while the stop flag value is 0
	// When the stop flag value is set to 1 it will stop
	while (stop_flag == 0)
	{
		LCD_displayStringRowColumn(0,0,"System under control");
		// Reading ADC value from channel 0
		ADC_val = ADC_read(ADC_CH0);
		// Calculating the current temperature value 
		t_current = ((500*ADC_val)/1023);
		
		// If the user started the control system before entering high and low temp values --> return to home screen		
		if (temp_H == temp_L || temp_L > temp_H)
		{
			LCD_clear_screen();
			LCD_sendString("Enter T values first");
			return;
		}
		// Else --> High and Low temp values are saved 
		else
		{
			// Normal state is when current temperature is between High and Low values
			if (t_current >= temp_L  && t_current <= temp_H)
			{
				// Start Normal temperature mode
				Normal_temp_mode(&t_current ,&ADC_val , temp_H, temp_L);
			}
			// High state is when current temperature is above High value and below fire alarm value
			else if (t_current > temp_H && t_current < 70)
			{
				// Start High temperature mode
				High_temp_mode(&t_current, &ADC_val , temp_H, temp_L);
			}
			// Fire alarm is when current temperature is above 70
			else if (t_current >= 70)
			{
				// Start fire alarm mode
				Fire_alarm_mode(&t_current, &ADC_val);
			}
			// Low state is when current temperature is below Low value
			else if (t_current < temp_L)
			{
				// Start low temperature mode
				Low_temp_mode(&t_current , &ADC_val, temp_H, temp_L);
			}
		}
		
	}
	// Stop flag is set to 1 ---> Force stop the control mode and return to home screen
	if (stop_flag == 1)
	{
		// Send "Control mode stopped" message to the user through UART
		UART_sendString("Control mode stopped");
		// Send "Enter" to display next message in new line
		UART_Transmit(13);
		// Turn off all LEDs
		LED_OFF(LED_NORMAL);
		LED_OFF(LED_LOW);
		LED_OFF(LED_HIGH);
		// Turn off BUZZER
		BUZZER_OFF(BUZZER_1);
		// Stop the fan
		timer0_dutyCycle(PWM_PHASE_CORRECT_MODE, 0);
		// Display home screen
		LCD_displayStringRowColumn(0,0, "1-Start Control");
		LCD_displayStringRowColumn(1,0, "2-Enter T values");
	}
}

// Normal temperature mode --> current temperature is between High and Low values
void Normal_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L)
{
	// Send "Normal state" message to the user through UART 
	UART_sendString("Normal state");
	// Send "Enter" to display next message in new line
	UART_Transmit(13);
	// Display normal state on LCD
	LCD_displayStringRowColumn(1,0,"Normal, T=     ");
	// Turn on Normal LED
	LED_ON(LED_NORMAL);
	// Turn off Low and High LEDs
	LED_OFF(LED_LOW);
	LED_OFF(LED_HIGH);
	// Turn off BUZZER
	BUZZER_OFF(BUZZER_1);
	// Run the fan at half speed (255/2)
	timer0_dutyCycle(PWM_PHASE_CORRECT_MODE, 128);
	// Keep the normal temperature mode running while current temperature is still in normal range
	while ((*t_current >= temp_L  && *t_current <= temp_H) && stop_flag == 0)
	{
		// Keep reading ADC value and calculate the current temperature
		*ADC_val = ADC_read(ADC_CH0);
		*t_current = ((500*(*ADC_val))/1023);
		// Display the current temperature on the LCD
		LCD_displayIntegerRowColumn(1,12, *t_current);
		// Keep reading the pressed key from the Keypad
		data = KPD_get_key();
		// If user pressed 'on'
		if (data == 'c')
		{
			// Set the stop flag to 1 ---> Control system will stop and will return to home screen
			stop_flag = 1;
		}
	}
}

// High temperature mode --> current temperature is between High and fire alarm values
void High_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L)
{
	// Send "High state" message to the user through UART 
	UART_sendString("High State");
	// Send "Enter" to display next message in new line
	UART_Transmit(13);
	// Display high state on LCD
	LCD_displayStringRowColumn(1,0,"High  , T=    ");
	// Turn off normal and low LEDs
	LED_OFF(LED_NORMAL);
	LED_OFF(LED_LOW);
	// Turn on high LED
	LED_ON(LED_HIGH);
	// Turn off BUZZER
	BUZZER_OFF(BUZZER_1);
	// Fan runs at full speed
	timer0_dutyCycle(PWM_PHASE_CORRECT_MODE, 255);
	// Keep the high temperature mode running while current temperature is still in high range
	while (*t_current > temp_H  && *t_current < 70 && stop_flag == 0)
	{
		// Keep reading ADC value and calculate the current temperature
		*ADC_val = ADC_read(ADC_CH0);
		*t_current = ((500*(*ADC_val))/1023);
		// Display the current temperature on the LCD
		LCD_displayIntegerRowColumn(1,12, *t_current);
		// Keep reading the pressed key from the Keypad
		data = KPD_get_key();
		// If user pressed 'on'
		if (data == 'c')
		{
			// Set the stop flag to 1 ---> Control system will stop and will return to home screen
			stop_flag = 1;
		}
	}
}

// Low temperature mode --> current temperature is below low value
void Low_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L)
{
	// Send "Low state" message to the user through UART 
	UART_sendString("Low state");
	// Send "Enter" to display next message in new line
	UART_Transmit(13);
	// Display low state on LCD
	LCD_displayStringRowColumn(1,0,"Low   , T=    ");
	// Turn off normal LED
	LED_OFF(LED_NORMAL);
	// Turn on low LED
	LED_ON(LED_LOW);
	// Turn off high LED
	LED_OFF(LED_HIGH);
	// Turn off BUZZER
	BUZZER_OFF(BUZZER_1);
	// Fan stop
	timer0_dutyCycle(PWM_PHASE_CORRECT_MODE, 0);
	// Keep the low temperature mode running while current temperature is still in low range
	while (*t_current < temp_L && stop_flag == 0)
	{
		// Keep reading ADC value and calculate the current temperature
		*ADC_val = ADC_read(ADC_CH0);
		*t_current = ((500*(*ADC_val))/1023);
		//If current temperature falls from 10 to 9 --> clear it to not show it as 90
		if (*t_current == 9)
		{
			LCD_displayStringRowColumn(1,12, "  ");
		}
		// Display the current temperature on the LCD
		LCD_displayIntegerRowColumn(1,12, *t_current);
		// Keep reading the pressed key from the Keypad
		data = KPD_get_key();
		// If user pressed 'on'
		if (data == 'c')
		{
			// Set the stop flag to 1 ---> Control system will stop and will return to home screen
			stop_flag = 1;
		}
	}
}

// Fire alarm mode --> current temperature is above 70
void Fire_alarm_mode(uint8_t *t_current , uint32_t *ADC_val)
{
	// Send "Fire Alarm!!" message to the user through UART 
	UART_sendString("Fire Alarm!!");
	// Send "Enter" to display next message in new line
	UART_Transmit(13);
	// Display fire alarm on LCD
	LCD_clear_screen();
	LCD_sendString("Fire Alarm!!");
	// Turn on all LEDs
	LED_ON(LED_NORMAL);
	LED_ON(LED_LOW);
	LED_ON(LED_HIGH);
	// Turn on BUZZER
	BUZZER_ON(BUZZER_1);
	// Fan runs at full speed
	timer0_dutyCycle(PWM_PHASE_CORRECT_MODE, 255);
	// Keep the fire alarm  mode running while current temperature is still in fire alarm range
	while (*t_current >= 70 && stop_flag == 0)
	{
		// Keep reading ADC value and calculate the current temperature
		*ADC_val = ADC_read(ADC_CH0);
		*t_current = ((500*(*ADC_val))/1023);
		// Keep reading the pressed key from the Keypad
		data = KPD_get_key();
		// If user pressed 'on'
		if (data == 'c')
		{
			// Set the stop flag to 1 ---> Control system will stop and will return to home screen
			stop_flag = 1;
		}
	}
}

// Mode 2 for Entering the values of High and Low temperature 
// then save it on the EEPROM
// passes temp high and low values by reference to change it 
void mode_2(uint8_t *temp_H , uint8_t *temp_L)
{
	// First set the high and low temp values to zero 
	*temp_H = 0;
	*temp_L = 0;
	// Display T high on LCD to make the user enter it
	LCD_clear_screen();
	LCD_sendString("T High= ");
	// Taking the value from the user through the keypad till he press '='
	while(data != '=')
	{
		data = KPD_get_key();
		if (data >= '0' && data <= '9')
		{
			LCD_sendCharacter(data);
			*temp_H = *temp_H*10 + (data - '0');
			data = KPD_get_key();
			LCD_sendCharacter(data);
		}
	}
	// If user entered high temperature higher than or equal to fire alarm temperature
	// send wrong entry on LCD
	if(*temp_H >= 70)
	{
		LCD_clear_screen();
		LCD_sendString("Wrong entry");
	}
	else
	{
		// Save the entered high temperature value in EEPROM
		EEPROM_write(0x10 , EEPROM_ADRESS, *temp_H);
		// Tell user to press 'x' on keypad to continue and go to low temperature value
		LCD_clear_screen();
		LCD_sendString("Press x to continue");
		// Wait till user press 'x'
		while(data != '*')
		{
			data = KPD_get_key();
		}
		// Display T low on LCD to make the user enter it 
		LCD_clear_screen();
		LCD_sendString("T Low= ");
		// Taking the value from the user through the keypad till he press '='
		while(data != '=')
		{
			data = KPD_get_key();
			if (data >= '0' && data <= '9')
			{
				LCD_sendCharacter(data);
				*temp_L = *temp_L*10 + (data - '0');
				data = KPD_get_key();
				LCD_sendCharacter(data);
			}
		}
		// If user entered low temperature higher than or equal to high temperature
		// send wrong entry on LCD
		if(*temp_L >= *temp_H || *temp_L < 0)
		{
			LCD_clear_screen();
			LCD_sendString("Wrong entry");
		}
		else
		{
			// Save the entered high temperature value in EEPROM
			EEPROM_write(0x20 , EEPROM_ADRESS, *temp_L);
			// Tell user that the values got saved on the EEPROM
			LCD_clear_screen();
			LCD_sendString("Values are saved.");
		}
	}
}

// Mode 3 for displaying the values of T high and T low saved on the EEPROM
void mode_3(uint8_t t_high , uint8_t t_low)
{
	LCD_clear_screen();
	LCD_displayStringRowColumn(0, 1, "T High= ");
	LCD_displayIntegerRowColumn(0, 9, t_high);
	LCD_displayStringRowColumn(1, 1, "T Low= ");
	LCD_displayIntegerRowColumn(1, 9, t_low);
}

// Receive the data sent through UART in the uart_data variable
void func_RXC_ISR()
{
	uart_data = UART_Receive();
}


// External interrupt 0 activates on falling edge
ISR(EXT_INT_0)
{
	// It sets the stop flag to 1 --->> which stops mode 1 and returns to home screen
	stop_flag = 1;
}