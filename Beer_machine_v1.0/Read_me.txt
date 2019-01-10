It is software for 
beer mash machine. As main controller was used Wifi Witty ESP-12F Board. 
Program written on arduino system in Sloeber IDE.
ADS_lib is modificated original library for my need. Every delay must be between called function getData()
In OLED_lib was modificated scaling the chars, and functions i2c_start, i2c_stop, i2c_send. This caused conflict with other modules using I2c. Now is using wire lib
