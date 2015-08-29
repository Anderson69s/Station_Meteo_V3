#!/usr/bin/env python

import httplib, urllib
from time import localtime, strftime
import time
import serial

ser = serial.Serial('/dev/ttyACM0', baudrate=9600, xonxoff=False, rtscts=False, dsrdtr=False, timeout=None)
time.sleep(20)
ser.flushInput()

def doit():
	pressure = 0
	temperature = 0
	result = 0
	ser.flushInput()
	result = ser.readline()
	pressure, temperature = result.split('/')
	params = urllib.urlencode({'field4': pressure, 'field5': temperature, 'key':'YOUR_KEY_HERE'})
	headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
	conn = httplib.HTTPConnection("api.thingspeak.com:80")
	try:
		conn.request("POST", "/update", params, headers)
		response = conn.getresponse()
		data = response.read()
		conn.close()
	except:
		print "Connection failed"
		pressure = 0
		temperature = 0
		result = 0
		ser.flushInput()
		doit()

#sleep for 40 seconds (api limit of 15 secs)
if __name__ == "__main__":
	while True:
		doit()
		ser.flushInput()
		time.sleep(35)

