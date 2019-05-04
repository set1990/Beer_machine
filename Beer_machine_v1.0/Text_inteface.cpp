/*
 * Text_inteface.cpp
 *
 *  Created on: 8 wrz 2018
 *      Author: Szymon
 */
#include "Beer_machine.h"

//-------- define area ----------------//
#define Baud_Rate	115200
//-------------------------------------//

//-------- global variable area -------//
String Text_UART_msg = "";         	   // a string to hold incoming data
//-------------------------------------//

//------- core function area ----------//
void UART_begine(void)
{
	Serial.begin(Baud_Rate);
	Text_UART_msg.reserve(200);
	Serial.println();
}
inline String Call_function(String Function_name, String Arguments[6])
{
    int	temp;
 //Triak control
	if(Function_name.equalsIgnoreCase("Get_Triak_Percent_control"))
	{
		return String(Get_Triak_Percent_control(), DEC);
	}
	else if(Function_name.equalsIgnoreCase("Set_Triak_Percent_control"))
	{
		Set_Triak_Percent_control((char)Arguments[0].toInt());
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Triak_control_OFF"))
	{
		Set_Triak_control_OFF();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Triak_control_ON"))
	{
		Set_Triak_control_ON();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_Triak_Error_flag"))
	{
		temp = Get_Triak_Error_flag();
		if(temp==0) return "OK";
		return  String(temp, HEX);
	}
	else if(Function_name.equalsIgnoreCase("Clear_Triak_Error_flag"))
	{
		Clear_Triak_Error_flag();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Triak_Debugg_ON"))
	{
		Set_Triak_Debugg_ON();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Triak_Debugg_OFF"))
	{
		Set_Triak_Debugg_OFF();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_Triak_control_ON"))
	{
		if(Get_Triak_control_ON()) return "ON";
								   return "OFF";
	}
 //Temperature mesurment
	else if(Function_name.equalsIgnoreCase("Get_T_quantity"))
	{
		return String(Get_T_quantity(), DEC);;
	}
	else if(Function_name.equalsIgnoreCase("Get_T_addres"))
	{
		return Get_T_addres((int)Arguments[0].toInt());
	}
	else if(Function_name.equalsIgnoreCase("Get_T_singel_value"))
	{
		return String(Get_T_singel_value((int)Arguments[0].toInt()), 2);
	}
	else if(Function_name.equalsIgnoreCase("Get_T_average"))
	{
		return String(Get_T_average(), 2);
	}
	else if(Function_name.equalsIgnoreCase("Get_T_dTdt"))
	{
		return String(Get_T_dTdt(), 4);
	}
	else if(Function_name.equalsIgnoreCase("Get_T_Error_flag"))
	{
		temp=Get_T_Error_flag();
		if(temp==0) return "OK";
		return String(temp, HEX);
	}
	else if(Function_name.equalsIgnoreCase("Clear_T_Error_flag"))
	{
		Clear_T_Error_flag();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_T_Debugg_ON"))
	{
		Set_T_Debugg_ON();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_T_Debugg_OFF"))
	{
		Set_T_Debugg_OFF();
		return "OK";
	}
 //LCD control
	else if(Function_name.equalsIgnoreCase("Set_viwe_display"))
	{
		Set_viwe_display((char)Arguments[0].toInt());
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_stage_name_display"))
	{
		Set_stage_name_display(Arguments[0]);
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_stage_name_display"))
	{
		return Get_stage_name_display();
	}
 //Engine control
	else if(Function_name.equalsIgnoreCase("Low_gear_engine"))
	{
		Low_gear_engine;
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("High_gear_engine"))
	{
		High_gear_engine;
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Stop_gear_engine"))
	{
		Stop_gear_engine;
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Clear_motor_Error_flag"))
	{
		Clear_motor_Error_flag();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_motor_Error_flag"))
	{
		temp = Get_motor_Error_flag();
		if(temp==0) return "OK";
		return  String(temp, HEX);
	}
	else if(Function_name.equalsIgnoreCase("Get_motor_gear"))
	{
		switch(Get_motor_gear())
		{
		   case Low_engine_now:
			 return  String("ROZRUCH");
			 break;
		   case High_engine_now:
			 return  String("PRACA");
			 break;
		   case Stop_engine_now:
			 return  String("STOP");
			 break;
		   default:
			 return  String("????");
		     break;
		}
	}
	else if(Function_name.equalsIgnoreCase("Get_motor_state"))
	{
		return Get_motor_state();
	}
	else if(Function_name.equalsIgnoreCase("Get_motor_signal"))
	{
		return  String(Get_motor_signal(), DEC);
	}
 //Control module
	else if(Function_name.equalsIgnoreCase("Get_Control_therm_Timer_t_procent"))
	{
		return String((int)Get_Control_therm_Timer_t_procent());
	}
	else if(Function_name.equalsIgnoreCase("Get_Control_therm"))
	{
		return String(Get_Control_therm(),2);
	}
	else if(Function_name.equalsIgnoreCase("Start_Control_therm_Timer"))
	{
		Start_Control_therm_Timer();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Stop_Control_therm_Timer"))
	{
		Stop_Control_therm_Timer();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_t_Control_therm_Timer"))
	{
		Set_t_Control_therm_Timer((int)Arguments[0].toInt(),(int)Arguments[1].toInt());
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Control_therm"))
	{
		Set_Control_therm((float)Arguments[0].toFloat());
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Control_therm_ON"))
	{
		Set_Control_therm_ON();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Set_Control_therm_OFF"))
	{
		Set_Control_therm_OFF();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_Control_therm_Timer_t"))
	{
		return String(Get_Control_therm_Timer_t());
	}
	else if(Function_name.equalsIgnoreCase("Get_now_Timer_t"))
	{
		return String(Get_now_Timer_t());
	}
	else if(Function_name.equalsIgnoreCase("Get_Control_therm_ON"))
	{
		if(Get_Control_therm_ON()) return "ON";
								   return "OFF";
	}
	else if(Function_name.equalsIgnoreCase("Get_Control_Flag_Timer"))
	{
		if(Get_Control_Flag_Timer()) return "RUN";
									 return "PAUSE";
	}
	else if(Function_name.equalsIgnoreCase("Set_Control_t_and_T"))
	{
		Set_Control_therm((float)Arguments[0].toFloat());
		Set_t_Control_therm_Timer((int)Arguments[1].toInt(),(int)Arguments[2].toInt());
		Set_stage_name_display(Arguments[3]);
		return "OK";
	}
  //Recipe control
	else if(Function_name.equalsIgnoreCase("Set_Repice_ON"))
	{
		Set_Repice_ON();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_Repice_ON"))
	{
		if(Get_Repice_ON()) return "ON";
						    return "OFF";
	}
	else if(Function_name.equalsIgnoreCase("Set_Repice_OFF"))
	{
		Set_Repice_OFF();
		return "OK";
	}
	else if(Function_name.equalsIgnoreCase("Get_Repice_step"))
	{
		return String(Get_Repice_step());
	}
	return "Bledna nazwa";
}
String Decode_text_msg(String Text_msg)
{
	int position_start, position_end;
	String Function, Arguments[6];
	position_start = Text_msg.indexOf(" ");
	Function = Text_msg.substring(0, position_start);
	Function.trim();
	for(int i=0; i<6; i++)
	{
		position_end = Text_msg.indexOf(" ",position_start+1);
		Arguments[i] =  Text_msg.substring(position_start, position_end);
		Arguments[i].trim();
		if(position_end == (-1)) break;
		position_start = position_end;
	}
	return(Call_function(Function, Arguments));
}
void UART_Transmission_Read()
{
	while(Serial.available())
	{
		// get the new byte:
	    char inChar = (char)Serial.read();
	    // add it to the inputString:
	    Text_UART_msg += inChar;
	    // if the incoming character is a newline, set a flag
	    // so the main loop can do something about it:
	    if (inChar == '\n')
	    {
	    	Serial.println(Decode_text_msg(Text_UART_msg));
	    	Text_UART_msg = "";
	    }
	}
}
//-------------------------------------//

