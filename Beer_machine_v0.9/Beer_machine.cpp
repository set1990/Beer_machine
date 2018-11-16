// Do not remove the include below
#include "Beer_machine.h"

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	UART_begine();
	I2C_begine();
	T_measurement_begin();
	HTTP_serwer_begine();
	Triak_control_begin();
	Start_logo_show();
	Set_viwe_display(Viwe_display_Text_ino);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	T_measurment_do();
	Motor_checking();
	Triak_error_check();
	HTTP_serwer_handle();
	UART_Transmission_Read();
	Blink_display();
	Automat_info();
	Control_therm();
	Control_therm_Timer();
	delay(10);
}

