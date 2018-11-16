// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _beer_machine_H_
#define _beer_machine_H_
#include "Arduino.h"
//add your includes for the project beer_machine here
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "OLED_lib/oled.h"
#include "ADS_lib/ADS1110.h"

//#include "Common_function.h"
//end of add your includes here

//constant definitions
#define new_line 			        1
#define Error_DS18B20_singel_T      0x01
#define Error_DS18B20_average  	    0x02
#define Error_DS18B20_initial		0x04
#define Error_Triak_not_conduction  0x08
#define Error_Triak_not_insulation  0x10
#define Error_Motor_not_current     0x20
#define Error_Motor_current_on_stop 0x40
#define Viwe_display_Text_ino		1
#define Viwe_display_Error			2
#define Viwe_display_value			3
#define Viwe_display_logo			4
#define Low_engine_now				2
#define High_engine_now				4
#define Stop_engine_now				8

//macro definitions
#define Low_gear_engine	 	Set_PCF_port(2)
#define High_gear_engine	Set_PCF_port(4)
#define Stop_gear_engine	Set_PCF_port(8)

//add your function definitions for the project beer_machine here
//common_function
template <typename text>
void Printf_Text(text a, bool nl=0)
{
	if(nl) Serial.println(a);
	else   Serial.print(a);
	// Tutaj dopisze Telnet!!!!
}
void UART_begine(void);
String Decode_text_msg(String Text_msg);
void UART_Transmission_Read(void);
//temperature reading
void T_measurement_begin(void);
void T_measurment_do(void);
int Get_T_quantity(void);
String Get_T_addres(int number_Devices);
float Get_T_singel_value(int number_Devices);
float Get_T_average(void);
float Get_T_dTdt(void);
int Get_T_Error_flag(void);
void Clear_T_Error_flag(void);
void Set_T_Debugg_ON(void);
void Set_T_Debugg_OFF(void);
//triak control
void Triak_control_begin(void);
void Triak_error_check(void);
char Get_Triak_Percent_control(void);
void Set_Triak_Percent_control(char procent);
void Set_Triak_control_OFF(void);
void Set_Triak_control_ON(void);
bool Get_Triak_control_ON(void);
int Get_Triak_Error_flag(void);
void Clear_Triak_Error_flag(void);
void Set_Triak_Debugg_ON(void);
void Set_Triak_Debugg_OFF(void);
//HTTP serwer
void HTTP_serwer_begine(void);
void HTTP_serwer_handle(void);
//I2c (PCF and OLED)
void I2C_begine(void);
void Blink_display(const char quantity_blink=0);
void Start_logo_show(void);
void Error_viwe_show(void);
void Automat_info();
bool Set_PCF_port(char nr_out);
void Set_stage_name_display(String name);
String Get_stage_name_display(void);
void Set_viwe_display(char view);
//Motor
void Motor_checking(void);
int Get_motor_gear(void);
unsigned int Get_motor_signal(void);
String Get_motor_state(void);
int Get_motor_Error_flag(void);
void Clear_motor_Error_flag(void);
//Control module
void Control_therm_Timer(void);
void Control_therm(void);
int Get_Control_therm_Timer_t(void);
char Get_Control_therm_Timer_t_procent(void);
int Get_now_Timer_t(void);
bool Get_Control_Flag_Timer(void);
bool Get_Control_therm_ON(void);
float Get_Control_therm(void);
void Start_Control_therm_Timer(void);
void Set_t_Control_therm_Timer(int minutes, int seconds);
void Stop_Control_therm_Timer();
void Set_Control_therm(float T);
void Set_Control_therm_ON();
void Set_Control_therm_OFF();
//Do not add code below this line
#endif /* _beer_machine_H_ */
