/*
 * Temperature_mesurment.cpp
 *
 *  Created on: 26 sie 2018
 *      Author: Szymon
 */
//-------- include area ---------------//
#include "Beer_machine.h"
//-------------------------------------//

//-------- define area ----------------//
#define ONE_WIRE_BUS           0 	   // Data wire is plugged into port 2 on the Arduino
#define TEMPERATURE_PRECISION  10 	   // Lower resolution
#define Min_delta_milis		   200
//-------------------------------------//

//-------- new typ area ---------------//
struct Temperature_measurement
{
	DeviceAddress *Adress;
	float *singel_T;
	float average_T;
	int numberOfDevices; 			   // Number of temperature devices found
	unsigned long time_milis;
	bool Debugg_Flag = 0;
	int Error_Temperature_flag = 0;
};
struct Temperature_average
{
	float average_T[3];
	unsigned long time_milis[3];
	float dTdt;
};
//-------------------------------------//

//-------- global variable area -------//
OneWire oneWire(ONE_WIRE_BUS);		   // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);   // Pass our oneWire reference to Dallas Temperature.
Temperature_measurement Temp_DS18B20;
Temperature_average average_DS18B20;
//-------------------------------------//

//------- core function area ----------//
template <typename text>
void T_terminal_print(text a, bool nl=0)
{
	if(Temp_DS18B20.Debugg_Flag) Printf_Text(a, nl);
}
void T_terminal_print()
{
	if(Temp_DS18B20.Debugg_Flag) Printf_Text("", 1);
}
String get_Address_T(DeviceAddress deviceAddress)
{
  String out_addres;
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) out_addres += 0;
    out_addres += String(deviceAddress[i], HEX);
  }
  return out_addres;
}
char averaging_singel_T(Temperature_measurement* measurement, float last_average)
{
   char Error=0;
   float counter_singel_T_OK=0;
   float temp_average=0;
   for(int i=0; i<(measurement->numberOfDevices); i++)
   {
	   T_terminal_print("Sprawdzenie pomiaru: ");
	   T_terminal_print(get_Address_T(measurement->Adress[i]), new_line);
	   T_terminal_print("badany pomiar: ");
	   T_terminal_print(measurement->singel_T[i], new_line);
	   if( (((measurement->singel_T[i])-(last_average/2))<0) ||
		   (((measurement->singel_T[i])-(last_average/2))>last_average) )
	   {
		   T_terminal_print("B³êdna wartoœæ pomiaru z adresu: ", new_line);
		   T_terminal_print(get_Address_T(measurement->Adress[i]), new_line);
		   measurement->singel_T[i] = 0;
		   Error = Error_DS18B20_singel_T;
	   }
	   else
	   {
		   counter_singel_T_OK++;
		   temp_average += measurement->singel_T[i];
	   }
   }
   if(counter_singel_T_OK>0) measurement->average_T = temp_average/counter_singel_T_OK;
   else Error = Error_DS18B20_average;
   T_terminal_print("Obliczona œrednia: ");
   T_terminal_print(measurement->average_T, new_line);
   T_terminal_print("---------------------", new_line);
   return(Error);
}
void T_measurement_begin()
{
	String a;
	T_terminal_print("Inicjacja DS18B20: ", new_line);
	sensors.begin();
	Temp_DS18B20.numberOfDevices = sensors.getDeviceCount();
	if(Temp_DS18B20.numberOfDevices==0)
	{
		Temp_DS18B20.Error_Temperature_flag=Error_DS18B20_initial;
		T_terminal_print("Wyst¹pi³ b³¹d inicjalizacji", new_line);
		return;
	}
	Temp_DS18B20.Adress   = new DeviceAddress[Temp_DS18B20.numberOfDevices];
	Temp_DS18B20.singel_T = new float[Temp_DS18B20.numberOfDevices];
	T_terminal_print("Parasite power is: ");
	if (sensors.isParasitePowerMode()) T_terminal_print("ON", new_line);
	else 							   T_terminal_print("OFF", new_line);
	// Loop through each device, print out address
	for(int i=0;i<Temp_DS18B20.numberOfDevices; i++)
	{
		// Search the wire for address
		if(sensors.getAddress(Temp_DS18B20.Adress[i], i))
		{
			T_terminal_print("Znaleziono DS18B20 o adresie: ");
			T_terminal_print(get_Address_T(Temp_DS18B20.Adress[i]), new_line);
			// set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
			sensors.setResolution(Temp_DS18B20.Adress[i], TEMPERATURE_PRECISION);
			T_terminal_print("Ustawiono precyzjê dzia³ania: ");
			T_terminal_print(sensors.getResolution(Temp_DS18B20.Adress[i]), 1);
			T_terminal_print("Pomiar testwy: ");
			sensors.requestTemperatures(); // Send the command to get temperatures
			Temp_DS18B20.singel_T[i]= sensors.getTempC(Temp_DS18B20.Adress[i]);
			T_terminal_print(Temp_DS18B20.singel_T[i], new_line);
		}
	}
	Temp_DS18B20.time_milis = millis();
	Temp_DS18B20.Error_Temperature_flag = averaging_singel_T(&Temp_DS18B20,Temp_DS18B20.singel_T[0]);
	if(Temp_DS18B20.Error_Temperature_flag)
	{
		T_terminal_print("Wyst¹pi³ b³¹d inicjalizacji", new_line);
		return;
	}
	else T_terminal_print("Zakoñczono sukcesem", new_line);
	for(int i=0; i<3; i++)
	{
		average_DS18B20.average_T[i]  = Temp_DS18B20.average_T;
		average_DS18B20.time_milis[i] = Temp_DS18B20.time_milis;
	}
	average_DS18B20.dTdt = 0;
	T_terminal_print("---------------------", new_line);
}
void T_measurment_do()
{
	if((Temp_DS18B20.time_milis+Min_delta_milis)>millis()) return;
	sensors.requestTemperatures(); // Send the command to get temperatures
	for(int i=0;i<Temp_DS18B20.numberOfDevices; i++)
	{
		Temp_DS18B20.singel_T[i]= sensors.getTempC(Temp_DS18B20.Adress[i]);
	}
	Temp_DS18B20.time_milis = millis();
	Temp_DS18B20.Error_Temperature_flag = averaging_singel_T(&Temp_DS18B20, average_DS18B20.average_T[1]);
	if(Temp_DS18B20.Error_Temperature_flag==Error_DS18B20_average) return;
	if(average_DS18B20.average_T[1] != Temp_DS18B20.average_T)
	{
		average_DS18B20.average_T[0]  = average_DS18B20.average_T[1];
		average_DS18B20.time_milis[0] = average_DS18B20.time_milis[1];
		average_DS18B20.average_T[1]  = Temp_DS18B20.average_T;
		average_DS18B20.time_milis[1] = Temp_DS18B20.time_milis;
	}
	average_DS18B20.average_T[2]  = Temp_DS18B20.average_T;
	average_DS18B20.time_milis[2] = Temp_DS18B20.time_milis;
	average_DS18B20.dTdt = (average_DS18B20.average_T[2]-average_DS18B20.average_T[0])/((((float)average_DS18B20.time_milis[2])-((float)average_DS18B20.time_milis[0]))/1000);
}
//-------------------------------------//

//-------- interface function area ----//
int Get_T_quantity()
{
	return(Temp_DS18B20.numberOfDevices);
}
String Get_T_addres(int number_Devices)
{
	return(get_Address_T(Temp_DS18B20.Adress[number_Devices]));
}
float Get_T_singel_value(int number_Devices)
{
	return(Temp_DS18B20.singel_T[number_Devices]);
}
float Get_T_average()
{
	return(average_DS18B20.average_T[2]);
}
float Get_T_dTdt()
{
	return(average_DS18B20.dTdt);
}
int Get_T_Error_flag()
{
	return(Temp_DS18B20.Error_Temperature_flag);
}
void Clear_T_Error_flag()
{
	Temp_DS18B20.Error_Temperature_flag = 0;
}
void Set_T_Debugg_ON()
{
	Temp_DS18B20.Debugg_Flag = 1;
}
void Set_T_Debugg_OFF()
{
	Temp_DS18B20.Debugg_Flag = 0;
}
//-------------------------------------//
