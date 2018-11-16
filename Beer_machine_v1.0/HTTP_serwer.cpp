/*
 * HTTP_serwer.cpp
 *
 *  Created on: 5 wrz 2018
 *      Author: Szymon
 */
//-------- include area ---------------//
#include "Beer_machine.h"
//-------------------------------------//

//-------- global variable area -------//
const char *ssid = "Beer_machine";
ESP8266WebServer server(80);
IPAddress IP_AP_state(10, 1, 1, 1);
IPAddress IP_gateway_state(10, 1, 1, 1);
IPAddress IP_mask_state(255, 255, 255, 0);
//-------------------------------------//
String Text =
		"<html>"
		"  <head>"
		"	<meta http-equiv='content-type' content='text/html; charset=ISO-8859-2'>"
		"    <meta charset='iso-8859-2'>"
		"    <title>BEER MACHIN</title>"
		"	<style>"
		"		body{"
		"			overflow-x: scroll;"
		"		}	"
		"		.navigation {"
		"			float: left;"
		"			margin-right: 10px;"
		"		}	"
		"		.fieldset_navi {"
		"			min-width: 190px;"
		"			max-width: none;"
		"		}"
		"	</style>"
		"	<script>"
		"		var reload_watch_T;"
		"		function reload_watch() {"
		"			clearTimeout(reload_watch_T);"
		"			document.getElementById('msr_test').contentWindow.location.reload(true);"
		"		}"
		"		function frameload(){"
		"			reload_watch_T = setInterval(reload_watch, 20000);"
		"		}"
		"		function make_control(order){"
		"			clearTimeout(reload_watch_T);"
		"			alert(order);"
		"			var xhttp = new XMLHttpRequest();"
		"			xhttp.open('GET', order, false);"
		"			xhttp.send();"
		"			alert(xhttp.responseText);"
		"			reload_watch_T = setInterval(reload_watch, 5000);"
		"		}"
		"	</script>"
		"  </head>"
		"  <body>"
		"	<header style='text-align: center;'>"
		"		<b>"
		"			<font size='7'>Borsuk Berr</font><br>"
		"			<font size='5'>Web remote control</font>"
		"		</b>"
		"		<p></p>"
		"		<hr>"
		"	</header>"
		"	<nav>"
		"		<ul>"
		"		<button onclick='window.location.href=`/`'>Strona Główna</button>"
		"		</ul>"
		"		<p></p>"
		"		<hr>"
		"		<p>&nbsp;</p>	"
		"		"
		"	</nav>"
		"	<div class='navigation'>	"
		"		 <fieldset style='border-style: dotted;' class='fieldset_navi' >"
		"			<legend>Control panel </legend>"
		"			<fieldset class='fieldset_navi'>"
		"			<hr>"
		"			Sterowanie Grzałki : &ensp;<button onclick='make_control(`/Set_Triak_control_ON`)'>ON</button> "
		"								 &ensp;<button onclick='make_control(`/Set_Triak_control_OFF`)'>OFF</button>"
		"			<hr>"
		"			Moc Grzałki : &ensp;<input type='number' id='P_grzalka' max='100' min='0' value='90'/><span style='font-size:90%;'> %</span> "
		"						  &ensp;<button onclick='make_control(`/Set_Triak_Percent_control-` + document.getElementById(`P_grzalka`).value)'> Ustaw </button> "
		"			<hr> "
		"			&ensp;<button onclick='make_control(`/Clear_Triak_Error_flag`)'>Kasowanie Błędu</button>  "
		"			<hr>"
		"			</fieldset>"
		"			<br>"
		"			<fieldset class='fieldset_navi'>"
		"			<hr>"
		"			Sterowanie silnika : "
		"			<button onclick='make_control(`/Low_gear_engine`)'>&ensp;LO&ensp;</button> "
		"			<button onclick='make_control(`/High_gear_engine`)'>&ensp;HI&ensp;</button> "
		"			<button onclick='make_control(`/Stop_gear_engine`)'>STOP</button> "
		"			<hr>"
		"			&ensp;<button onclick='make_control(`/Clear_motor_Error_flag`)'>Kasowanie Błędu</button> "
		"			<hr>"
		"			</fieldset>"
		"		    <br>"
		"			<fieldset class='fieldset_navi'>"
		"			<hr>"
		"			Sterowanie Licznika : &ensp;<button onclick='make_control(`/Start_Control_therm_Timer`)'>START</button> "
		"								  &ensp;<button onclick='make_control(`/Stop_Control_therm_Timer`)'>STOP</button> "
		"			<hr>"
		"			<button onclick='make_control(`/Set_t_Control_therm_Timer-` + document.getElementById(`l_se_val_mm`).value + `-` + document.getElementById(`l_se_val_ss`).value)'>Ustaw licznik</button> "
		"			&ensp;<input type='number' id='l_se_val_mm' max='60' min='0' value='00'/><span style='font-size:90%;'> [m]</span> "
		"			&ensp;<input type='number' id='l_se_val_ss'  max='60' min='0' value='00'/><span style='font-size:90%;'> [s]</span>"
		"			<hr>"
		"			</fieldset>"
		"			<br>"
		"			<fieldset class='fieldset_navi'>"
		"			<hr>"
		"			Termostat : &ensp;<button onclick='make_control(`/Set_Control_therm_ON`)'>ON</button> "
		"						&ensp;<button onclick='make_control(`/Set_Control_therm_OFF`)'>OFF</button>"
		"			<hr>"
		"			Parametry &#8629;"
		"			<br>"
		"			Nazwa : <input type='text' id='etap' value='Oczekiwanie'/>"
		"			<br>"
		"			Zadana T : &ensp;<input type='number' id='lz_se_val_T' step='0.1' max='100' min='0' value='00.00'/> &#8451;"
		"			<br>"
		"			Zadany czas	: &ensp;<input type='number' id='lz_se_val_mm' max='60' min='0' value='00'/><span style='font-size:90%;'> [m]</span> "
		"						  &ensp;<input type='number' id='lz_se_val_ss'  max='60' min='0' value='00'/><span style='font-size:90%;'> [s]</span>	"
		"			<br>"
		"			&ensp;<button onclick='make_control(`/Set_Control_t_and_T-` + document.getElementById(`lz_se_val_T`).value + `-` + document.getElementById(`lz_se_val_mm`).value + `-` + document.getElementById(`lz_se_val_ss`).value + `-` + document.getElementById(`etap`).value) '>Ustaw parametry</button> "
		"			<hr>"
		"			</fieldset>"
		"			<br>"
		"			<fieldset class='fieldset_navi'>"
		"			<hr>"
		"			Pomiar Temp. : &ensp;<button onclick='function reload_watch()'>Odśwież</button>"
		"			<hr>"
		"			&ensp;<button onclick='make_control(`/Clear_T_Error_flag`)'>Kasowanie Błędu</button> "
		"			<hr>"
		"			</fieldset>"
		"		</fieldset>"
		"    </div>"
		"	<fieldset style='border-style: dotted; max-width: none; min-width: 240px;' class='fieldset_navi' >"
		"		<legend>State panel </legend>"
		"		<iframe onload='frameload()' id='msr_test' src='/msg' width='100%' height='200%'  frameborder='0'>:( Wyjebało?</iframe>"
		"	</fieldset>"
		" </body>"
		"</html>";

String nespepe =
		"<html>"
		"  <head>"
		"    <meta http-equiv='content-type' content='text/html; charset=ISO-8859-2'>"
		"    <meta charset='iso-8859-2'>"
		"    <title>Measurment</title>"
		"	<style>"
		"		body{"
		"			overflow-x: scroll;"
		"		}"
		"		.newspaper1 {"
		"			-webkit-columns: 260px  2; /* Chrome, Safari, Opera */"
		"			-moz-columns: 260px  2; /* Firefox */"
		"			columns: 260px 2;"
		"			max-width: 600px;"
		"		}	"
		"		fieldset {"
		"			min-width: 240px;"
		"			max-width: 300px;"
		"			break-inside: avoid-column;"
		"		}"
		"	</style>"
		"	<script>"
		"		var myVar = setInterval(myTimer, 1000); "
		"		function checkTime(i) {"
		"			if (i < 10) { "
		"				i = '0' + i;"
		"			}"
		"			return i;"
		"		}"
		"		function myTimer() {"
		"			var temp_t;"
		"			var s;"
		"			var cunter = parseInt(document.getElementById('t_sec').innerHTML) + (parseInt(document.getElementById('t_min').innerHTML)*60) ;"
		"			if(document.getElementById('t_ON').innerHTML == 'RUN'){"
		"				if(cunter>0) cunter -= 1;"
		"				s = cunter%60;"
		"				s = checkTime(s); "
		"				document.getElementById('t_sec').innerHTML = s; "
		"				s = parseInt((cunter/60)%60);"
		"				s = checkTime(s); "
		"				document.getElementById('t_min').innerHTML = s; "
		"			}"
		"		}"
		"	</script>  "
		"  </head>"
		"  <body>"
		"	<div class='newspaper1'>"
		"		<fieldset>"
		"			<legend> Temperatura Zacieru </legend>"
		"			<hr>"
		"			Pomiar : &emsp; <b><span style='font-size:160%;'>therm_val</span> &#8451;</b>"
		"			<hr>"
		"			Status : &emsp; <b><span>therm_stat</span></b> 	"
		"			<hr>"
		"		</fieldset>"
		"		<br>"
		"		<fieldset>"
		"			<legend> Stan Grzałki </legend>"
		"			<hr>"
		"			Aktywność : &emsp; <b><span style='font-size:140%;'>G_ON</span></b>"
		"			<hr>"
		"			Wysterownie : &emsp; <b><span style='-size:140%;'>G_P</span>  &#37;</b>"
		"			<hr>"
		"			Status : &emsp; <b><span>G_stat</span></b> 	"
		"			<hr>"
		"		</fieldset>"
		"		<br>"
		"		<fieldset>"
		"			<legend> Stan Silnika </legend>"
		"			<hr>"
		"			Zadany Bieg : &emsp; <b><span style='font-size:140%;'>Motor_ON</span></b>"
		"			<hr>"
		"			Sygnał : &emsp; <b><span style='-size:140%;'>Motor_P</span></b>"
		"			<hr>"
		"			Status : &emsp; <b><span>Motor_stat</span></b> 	"
		"			<hr>"
		"		</fieldset>"
		"		<br>"
		"		<fieldset>"
		"			<legend> Stan Termostatu </legend>"
		"			<hr>"
		"			Aktywność : &emsp; <b><span style='font-size:140%;'>Tt_ON</span></b>"
		"			<hr>"
		"			Etap : &emsp; <b><span>Tt_stat</span></b>"
		"			<hr>"
		"			Zadana Temp. : &emsp; <b><span style='font-size:140%;'>Tt_T</span>  &#8451;</b>"
		"			<hr>"
		"			Zadana Czas : &emsp; <b><span style='font-size:140%;'>Tt_tm</span> [m] "
		"									<span style='font-size:140%;'>Tt_ts</span> [s]</b>"
		"			<hr>"
		"		</fieldset>	"
		"		<br>		"
		"		<fieldset>"
		"			<legend> Licznik </legend>"
		"			<hr>"
		"			Aktywność : &emsp; <b><span id='t_ON' style='font-size:140%;'>c_therm_cont</span></b>"
		"			<hr>"
		"			Wartość licznika : &emsp; <b><span id='t_min' style='font-size:140%;'>t_min_val</span> [m] "
		"	 									 <span id='t_sec' style='font-size:140%;'>t_sec_val</span> [s]</b>"
		"			<hr>"
		"		</fieldset>"
		"		<br>"
		"	</div>"
		"	</body>"
		"</html>";

//------- core function area ----------//
void handleRoot()
{
	server.send(200, "text/html", Text);
}
void handleMeasurment()
{
	String msg_to_www = nespepe;
	int	temp, temp2;
	msg_to_www.replace("therm_val", String(Get_T_average(), 2));
	temp = Get_T_Error_flag();
	if(temp) msg_to_www.replace("therm_stat", String(temp, HEX));
	else     msg_to_www.replace("therm_stat", "OK");
	if(Get_Triak_control_ON()) msg_to_www.replace("G_ON", "ON");
	else    				   msg_to_www.replace("G_ON", "OFF");
	msg_to_www.replace("G_P", String(Get_Triak_Percent_control(), DEC));
	temp = Get_Triak_Error_flag();
	if(temp) msg_to_www.replace("G_stat", String(temp, HEX));
	else     msg_to_www.replace("G_stat", "OK");
	switch(Get_motor_gear())
	{
	   case Low_engine_now:
		 msg_to_www.replace("Motor_ON", "ROZRUCH");
	     break;
	   case High_engine_now:
		 msg_to_www.replace("Motor_ON", "PRACA");
		 break;
	   case Stop_engine_now:
		 msg_to_www.replace("Motor_ON", "STOP");
		 break;
	   default:
		   msg_to_www.replace("Motor_ON", "????");
	     break;
	}
	msg_to_www.replace("Motor_P", String(Get_motor_signal(), DEC));
	msg_to_www.replace("Motor_stat", Get_motor_state());
	if(Get_Control_therm_ON()) msg_to_www.replace("Tt_ON", "ON");
	else    				   msg_to_www.replace("Tt_ON", "OFF");
	msg_to_www.replace("Tt_stat", Get_stage_name_display());
	msg_to_www.replace("Tt_T", String(Get_Control_therm(),2));
	temp = Get_Control_therm_Timer_t();
	msg_to_www.replace("Tt_ts", String(temp%60, DEC));
	msg_to_www.replace("Tt_tm", String(temp/60, DEC));
	if(Get_Control_Flag_Timer()) msg_to_www.replace("c_therm_cont", "RUN");
	else 						 msg_to_www.replace("c_therm_cont", "PAUSE");
	temp = Get_now_Timer_t();
	temp2 = temp%60;
	if(temp2>9) msg_to_www.replace("t_sec_val", String(temp2, DEC));
	else        msg_to_www.replace("t_sec_val", (String("0")+String(temp2, DEC)));
	temp2 = temp/60;
	if(temp2>9) msg_to_www.replace("t_min_val", String(temp2, DEC));
	else 		msg_to_www.replace("t_min_val", (String("0")+String(temp2, DEC)));
	server.send(200, "text/html", msg_to_www);
}
void handleNotFound()
{
	String msg_on_http = server.uri();
	String decode_msg;
	msg_on_http.remove(0, 1);
	msg_on_http.replace("-", " ");
	decode_msg = Decode_text_msg(msg_on_http);
	server.send(200, "text/html", decode_msg);
}

void HTTP_serwer_begine()
{
	WiFi.softAP(ssid);
	WiFi.softAPConfig(IP_AP_state, IP_gateway_state, IP_mask_state);
	server.on("/", handleRoot);
	server.on("/msg", handleMeasurment);
	server.onNotFound(handleNotFound);
	server.begin();
}
void HTTP_serwer_handle()
{
	server.handleClient();
}
//-------------------------------------//
