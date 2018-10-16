import serial
import time

arduino=serial.Serial('/dev/ttyACM0',baudrate=9600, timeout = 3.0)
arduino.open()
 
param= open('Parametros.txt','r+' )
temp=open('Temperatura.txt','r+')

while True:
	param.seek(48)
	p=param.read(1)
	if p=="0":
		while arduino.inWaiting() > 0:
			t = arduino.readline()
	else:
	
	
queda leer el numero correspondiente a la linea del fermentador a cambiar pueden ser varios entonces hay que parsear y mandarle a la arudino
ej "123" cambiar los 3 fermendaroes 			
      	
     # arduino.write(var)
      #time.sleep(0.1)
      #while arduino.inWaiting() > 0:
         #   txt += arduino.read(1)
            #print txt
            #txt = ''
#arduino.close()


param.close()
temp.close()
