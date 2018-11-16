/*
 * Triak_control.cpp
 *
 *  Created on: 3 wrz 2018
 *      Author: Szymon
 */
//-------- include area ---------------//
#include "Beer_machine.h"
//-------------------------------------//

//-------- define area ----------------//
#define Output_triak       12
#define Input_triak	       4
#define Max_procent_value  99		   // max 90% (2ms)
#define Min_procent_value  1		   // min 10% (18ms)
#define Max_timer_value    6188 	   // max 10% (18ms)
#define Min_timer_value    62 		   // min 90% (2ms)
#define Error_ms_timeout   500
//-------------------------------------//

//-------- new typ area ---------------//
struct Triak_control
{
	bool Control_ON = 0;
	bool Debugg_Flag = 0;
	char Percent_control = 10;		   // max 90 min 10
	int Start_Timer_value = 625;	   // Default 2ms
	int Error_Triak_flag = 0;
	unsigned long time_milis;		   // ms time from last change input
};
//-------------------------------------//

//-------- global variable area -------//
Triak_control Temp_module;
//-------------------------------------//

//------- core function area ----------//
template <typename text>
void Triak_terminal_print(text a, bool nl=0)
{
	if(Temp_module.Debugg_Flag) Printf_Text(a, nl);
}
void Triak_terminal_print()
{
	if(Temp_module.Debugg_Flag) Printf_Text("", 1);
}
void ICACHE_RAM_ATTR onTimerISR()	   // Interrupt Timer1
{
	Triak_terminal_print("Timer zadzia³a³", new_line);
	timer1_disable();
	if(Temp_module.Control_ON == 0)
	{
		digitalWrite(Output_triak, LOW);
		return;
	}
	digitalWrite(Output_triak, HIGH);
}
void Triak_change_conduction()		   // Interrupt INPUT
{
	int pin_state;
	if(Temp_module.Control_ON == 0)
	{
		timer1_disable();
		digitalWrite(Output_triak, LOW);
		return;
	}
	Temp_module.time_milis = millis();
    pin_state = digitalRead(Input_triak);
    Triak_terminal_print("Stan pinu: ");
    Triak_terminal_print(pin_state, new_line);
    if(pin_state)
    {
    	Triak_terminal_print("Timer start", new_line);
    	timer1_enable(TIM_DIV265, TIM_EDGE, TIM_SINGLE);
        timer1_write(Temp_module.Start_Timer_value); 	//312.5Khz (1 tick = 3.2us - 26843542.4 us max)
    }
    else
    {
    	timer1_disable();
    	Triak_terminal_print("Wyjœcie 0", new_line);
    	digitalWrite(Output_triak, LOW);
    }
}
void Triak_control_begin()
{
	Triak_terminal_print("Inicjacja modu³u Triaka", new_line);
	Triak_terminal_print("Deklaracja pinów: ");
	pinMode(Output_triak, OUTPUT);
	pinMode(Input_triak, INPUT);
	Triak_terminal_print("OK", new_line);
	Triak_terminal_print("Alokacja przerwañ: ");
    timer1_attachInterrupt(onTimerISR);
	attachInterrupt(digitalPinToInterrupt(Input_triak), Triak_change_conduction, CHANGE);
	Triak_terminal_print("OK", new_line);
	Triak_terminal_print("---------------------", new_line);
}
void Triak_error_check()
{
	if(Temp_module.Control_ON==0) return;
	if((Temp_module.time_milis + Error_ms_timeout) > millis())
		return;
	Temp_module.Control_ON = 0;
	digitalWrite(Output_triak, LOW);
	switch(digitalRead(Input_triak))
	{
		case 0:
			Temp_module.Error_Triak_flag = Error_Triak_not_conduction;
			break;
		case 1:
			Temp_module.Error_Triak_flag = Error_Triak_not_insulation;
			break;
		default:
			Temp_module.Error_Triak_flag = Error_Triak_not_conduction | Error_Triak_not_insulation;
			break;
	}
}
//-------------------------------------//

//-------- interface function area ----//
char Get_Triak_Percent_control()
{
	return(Temp_module.Percent_control);
}
void Set_Triak_Percent_control(char procent)
{
	Triak_terminal_print("Zadany procent: ");
	Triak_terminal_print(procent, new_line);
	if(procent>=Max_procent_value)
	{
		Temp_module.Percent_control = Max_procent_value;
		Temp_module.Start_Timer_value = Min_timer_value;
	}
	else if(procent<=Min_procent_value)
	{
		Temp_module.Percent_control = Min_procent_value;
		Temp_module.Start_Timer_value = Max_timer_value;
	}
	else
	{
		Temp_module.Percent_control = procent;
		Temp_module.Start_Timer_value = (625*(100-Temp_module.Percent_control))/10;
	}
	Triak_terminal_print("Obliczona iloœæ Ticków: ");
	Triak_terminal_print(Temp_module.Start_Timer_value, new_line);
}
void Set_Triak_control_OFF()
{
	Temp_module.Control_ON = 0;
}
void Set_Triak_control_ON()
{
	if(Temp_module.Error_Triak_flag) return;
	Temp_module.Control_ON = 1;
	Triak_change_conduction();
}
bool Get_Triak_control_ON()
{
	return(Temp_module.Control_ON);
}
int Get_Triak_Error_flag()
{
	return(Temp_module.Error_Triak_flag);
}
void Clear_Triak_Error_flag()
{
	Temp_module.Error_Triak_flag = 0;
}
void Set_Triak_Debugg_ON()
{
	Temp_module.Debugg_Flag = 1;
}
void Set_Triak_Debugg_OFF()
{
	Temp_module.Debugg_Flag = 0;
}
//-------------------------------------//
