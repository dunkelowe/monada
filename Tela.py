#!/usr/bin/python
import os
from time import sleep
from Adafruit_CharLCDPlate import Adafruit_CharLCDPlate
from subprocess import Popen,PIPE,STDOUT,call
# Initialize the LCD plate.  Should auto-detect correct I2C bus.  If not,
# pass '0' for early 256 MB Model B boards or '1' for all later versions


lcd = Adafruit_CharLCDPlate()

proc1=Popen('./sht21 T',shell=True,stdout=PIPE, )
output1=proc1.communicate()[0]
#p=os.system("./sht21 S")

proc2=Popen('./sht21 H',shell=True,stdout=PIPE, )
output2=proc2.communicate()[0]

lcd.message('Temperatura:'+str(output1)+'\nHumedad:'+str(output2))
	
# Clear display and show greeting, pause 1 sec

#lcd.message(p)
#print(p)
#sleep(5)

# Cycle through backlight colors
#col = (lcd.RED , lcd.YELLOW, lcd.GREEN, lcd.TEAL,
 #      lcd.BLUE, lcd.VIOLET, lcd.ON   , lcd.OFF)
#for c in col:
 #   lcd.backlight(c)
  #  sleep(.5)

# Poll buttons, display message & set backlight accordingly
#btn = ((lcd.LEFT  , 'Izquierda'              , lcd.BLUE),
#       (lcd.UP    , 'Arriba'     , lcd.BLUE),
#       (lcd.DOWN  , 'Abajo'    , lcd.BLUE),
#       (lcd.RIGHT , 'Derecho', lcd.BLUE),
#       (lcd.SELECT, ''                          , lcd.ON))
#prev = -1
#while True:
#    for b in btn:
#        if lcd.buttonPressed(b[0]):
#            if b is not prev:

#                lcd.message(b[1])
#                lcd.backlight(b[2])
#                prev = b
#            break

