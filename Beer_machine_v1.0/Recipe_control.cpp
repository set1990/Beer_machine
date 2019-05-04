/*
 * Recipe_creator.cpp
 *
 *  Created on: 17 mar 2019
 *      Author: Szymon
 */

//-------- include area ---------------//
#include "Beer_machine.h"
//-------------------------------------//

//-------- define area ----------------//

//-------------------------------------//

//-------- new typ area ---------------//
struct repice_step
{
	float Therm_set;			       // [C]
	int Time_set_m;					   // [min]
	int Time_set_s;					   // [s]
	String stage_name;
};
struct repise
{
	char quantity;
	repice_step* step;
	repise(char q)
	{
		quantity = q;
		step = new repice_step[q];
	};
	~repise()
	{
		delete[] step;
	}
};
//-------------------------------------//

//-------- global variable area -------//
repise* This_beer;
bool Repice_ON;
int step_cunter = 0;
//-------------------------------------//

//------- core function area ----------//
void Repice_handle()
{
	/*
	if(step_cunter>=This_beer->quantity)
	{
		Repice_ON = 0;
		step_cunter=0;
	}
	if(Repice_ON==0) return;
	if(Get_Control_therm_ON()==0)
	{
		Set_Control_therm(This_beer->step[step_cunter].Therm_set);
		Set_t_Control_therm_Timer(This_beer->step[step_cunter].Time_set_m, This_beer->step[step_cunter].Time_set_s);
		Set_stage_name_display(This_beer->step[step_cunter].stage_name);
		Set_Control_therm_ON();
		step_cunter++;
	}
	*/
	if(Repice_ON)
	{
		for(int i=0;i<This_beer->quantity;i++)
		{
			Serial.println(This_beer->step[i].stage_name);
			Serial.println(This_beer->step[i].Therm_set);
			Serial.println(This_beer->step[i].Time_set_m);
			Serial.println(This_beer->step[i].Time_set_s);
		}
		Repice_ON=0;
	}
}
//-------------------------------------//

//-------- interface function area ----//
void Repice_create(char step_quantity, float* step_therm, int* step_time_m, int* step_time_s, String* step_name)
{
     static struct repise beer(step_quantity);
     for(int i=0;i<beer.quantity;i++)
     {
    	 beer.step[i].Therm_set  = step_therm[i];
    	 beer.step[i].Time_set_m = step_time_m[i];
    	 beer.step[i].Time_set_s = step_time_s[i];
    	 beer.step[i].stage_name = step_name[i];
     }
     This_beer = &beer;
}
void Set_Repice_ON()
{
	Repice_ON = 1;
}
void Set_Repice_OFF()
{
	Repice_ON = 0;
}
bool Get_Repice_ON()
{
	return(Repice_ON);
}
int Get_Repice_step()
{
	return(step_cunter+1);
}
//-------------------------------------//



