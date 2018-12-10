import serial
import time
import time 
import RPi.GPIO as GPIO 
import paho.mqtt.client as mqtt

arduino=serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout = 3.0)
 
param= open('Parametros.txt','r+' )
temp=open('Temperatura.txt','r+')
a=0

def on_connect(client, userdata, flags, rc): 
   print("Connected with result code " + str(rc)) 
   client.subscribe("/leds/pi") 
def on_message(client, userdata, msg): 
   print(str( msg.payload)) 
client = mqtt.Client() 
client.on_connect = on_connect 
client.on_message = on_message 
client.connect('localhost', 1883, 60) 
client.loop_start()

while True:
	param.seek(48)							# Posiciona en la ultima linea del txt
	p=param.read(5)							#Leo la ultima linea
	p=p.split(',')							#Los fermentadores estan separados por coma
	if p[0]=="0":							#si el primero es 0, no hay nada que enviar y solo escucho a la arduino
		while arduino.inWaiting() > 0:
			print "entro al wait"			
			t = arduino.read(1) 			#Leo que fermentador es
			print t
			temp.seek(int(t)*6) 			# Dependiendo el fermentador me posiciono en la linea
			t = arduino.read(5)				# Leo la linea de determinado fermentador
			print t
			temp.write(t)
		a=a+1
   		time.sleep(1)  						# Delay for about 1 sec to debounce. 
   		client.publish('/leds/esp8266', 'TOGGLE'+str(a))	#Recibo la publicacion							# Escribo la temp leida en el txt
	else:
		print "entro al else"
		for x in range(len(p)	):
			if p[x]=="0":
				break
			param.seek((int(p[x])-1)*16)
			c=param.read(15)
			arduino.write(p[x]+","+c+'\n')
			time.sleep(0.1)
		param.seek(48) 						# despues de leer todo posiciono en la ultma linea
		param.write("0,0,0") 				# y borro lo que estaba antes 
	
arduino.close()
param.close()
temp.close()
