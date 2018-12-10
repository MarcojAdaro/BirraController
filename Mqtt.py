# RPi
import time 
import RPi.GPIO as GPIO 
import paho.mqtt.client as mqtt
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
print('Script is running, press Ctrl-C to quit...') 
while True:
   a=a+1
   time.sleep(1)  # Delay for about 20 milliseconds to debounce. 
   client.publish('/leds/esp8266', 'TOGGLE'+str(a))
