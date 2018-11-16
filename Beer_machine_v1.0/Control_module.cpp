/*
 * Control_module.cpp
 *
 *  Created on: 21 wrz 2018
 *      Author: Szymon
 */
//-------- include area ---------------//
#include "Beer_machine.h"
//-------------------------------------//

//-------- define area ----------------//
#define Therm_reserve_OFF		  0.5  //[C]
#define Therm_reserve_Half_power  0.5  //[C]
#define	Half_power				  50   //[%]
#define	Max_power				  99   //[%]
//-------------------------------------//

//-------- global variable area -------//
float Therm_set = 0;				   //[C]
int   Time_set = 0;				       //[s]
int	  Time_timer_now = 0;			   //[s]
bool  Timer_start_flag = 0;
bool  Control_therm_ON = 0;
//-------------------------------------//

//------- core function area ----------//
void Control_therm_Timer()
{
	static unsigned long  last_millis;
	unsigned long time_differ;
	if(Time_timer_now<=0)
	{
		Timer_start_flag=0;
		Time_timer_now=Time_set+1;
		Control_therm_ON=0;
		Set_Triak_control_OFF();
	}
	if(Timer_start_flag)
	{
		time_differ =(millis() - last_millis)/1000;
		Time_timer_now -= time_differ;
		if(time_differ) last_millis = millis();
	}
	else  last_millis = millis();
}
void Control_therm()
{
	float therm = Get_T_average();
	if(Control_therm_ON==0) return;
	if(therm>=(Therm_set+Therm_reserve_OFF))
	{
		Set_Triak_control_OFF();
		Start_Control_therm_Timer();
	}
	else if(therm>=(Therm_set-Therm_reserve_Half_power))
	{
		if(Get_Triak_Percent_control()!=Half_power) Set_Triak_Percent_control(Half_power);
		if(Get_Triak_control_ON()==0) 				Set_Triak_control_ON();
	}
	else
	{
		if(Get_Triak_Percent_control()!=Max_power) Set_Triak_Percent_control(Max_power);
		if(Get_Triak_control_ON()==0)			   Set_Triak_control_ON();
	}
}
//-------------------------------------//

//-------- interface function area ----//
void  Start_Control_therm_Timer()
{
	Timer_start_flag = 1;
}
void  Set_t_Control_therm_Timer(int minutes, int seconds)
{
	Time_set = (minutes*60) + seconds;
	Time_timer_now = Time_set;
}
void  Stop_Control_therm_Timer()
{
	Timer_start_flag=0;
}
bool  Get_Control_Flag_Timer()
{
	return Timer_start_flag;
}
int Get_now_Timer_t()
{
	return Time_timer_now;
}
int Get_Control_therm_Timer_t()
{
	return Time_set;
}
char  Get_Control_therm_Timer_t_procent()
{
	if(Time_set<=0) return(99);
	char procent = (char)(((Time_set*100)-(Time_timer_now*100))/Time_set);
	procent = (procent > 100) ? 99 : procent;
	return(procent);
}
float Get_Control_therm(void)
{
	return Therm_set;
}
void  Set_Control_therm(float T)
{
	Therm_set = T;
}
void  Set_Control_therm_ON()
{
	Control_therm_ON = 1;
}
bool  Get_Control_therm_ON()
{
	return(Control_therm_ON);
}
void  Set_Control_therm_OFF()
{
	Control_therm_ON = 0;
	Stop_Control_therm_Timer();
	Set_Triak_control_OFF();
}
//-------------------------------------//
