import serial
import time
import time 
import RPi.GPIO as GPIO 
import paho.mqtt.client as mqtt

arduino=serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout = 3.0)
 

temp=open('/var/www/html/php/Temperatura.txt','r+')
a=0
t=""
param= open('/var/www/html/php/Parametros.txt','r+' )
param.seek(64)                                          # despues de leer tod$
param.write("1,2,3,4")                          # y borro lo que estaba antes
param.close()

while arduino.inWaiting()>0:
	arduino.readline()
'''def on_connect(client, userdata, flags, rc): 
   print("Connected with result code " + str(rc)) 
   client.subscribe("/leds/pi") 
def on_message(client, userdata, msg): 
   print(str( msg.payload)) 
client = mqtt.Client() 
client.on_connect = on_connect 
client.on_message = on_message 
client.connect('localhost', 1883, 60) 
client.loop_start()'''

while True:
	param= open('/var/www/html/php/Parametros.txt','r+' )
	param.seek(64)							# Posiciona en la ultima linea del txt
	p=param.read(5)							#Leo la ultima linea
	p=p.split(',')							#Los fermentadores estan separados por coma
	if p[0]=="0":							#si el primero es 0, no hay nada que enviar y solo escucho a la arduino
		while arduino.inWaiting() > 0:
			print "entro al wait"			
			tempe=""
			val=0
			while t=="" or t!='l':
				t=arduino.read(1)
			print t
			time.sleep(1)
			if t=='l':
				t=arduino.read(1)
				temp.seek(int(t)*6)
				t=arduino.read(1)
				while t!='l':
					val=val+1
					tempe=tempe+t
					time.sleep(1)
					t=arduino.read(1)
					print tempe
				if val<5:
					tempe="0"+tempe
				temp.write(tempe)
			break
		#a=a+1
   		#time.sleep(1)  						# Delay for about 1 sec to debounce. 
   		#client.publish('/leds/esp8266', 'TOGGLE'+str(a))	#Recibo la publicacion							# Escribo la temp leida en el txt
	else:
		print "entro al else"
		for x in range(len(p)	):
			if p[x]=="0":
				break
			param.seek((int(p[x])-1)*16)
			c=param.read(15)
			arduino.write(p[x]+","+c+'\n')
			time.sleep(0.1)
		param.seek(64) 						# despues de leer todo posiciono en la ultma linea
		param.write("0,0,0,0") 				# y borro lo que estaba antes 
		param.close()
	
arduino.close()
temp.close()
