import serial
import time
ser = serial.Serial('/dev/ttyUSB0',115200)


file = open ("/var/www/html/Pantalla/php/Archivo.txt",'r+')

#file.write ("   ")
while 1:
	file.seek(0)
	read_serial=ser.readline(5)
	file.write (read_serial)
	time.sleep(1)
file.close()
