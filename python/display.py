from pyfiglet import *
import serial
import os

ser = serial.Serial('COM3', 115200)
while True:
	speed = ord(ser.read())
	os.system('cls||clear')
	print(figlet_format(" ",font="clb8x10"))
	print(figlet_format(" ",font="clb8x10"))
	print(figlet_format(str(speed)+" km/h",font="clb8x10"))
	print(figlet_format(" ",font="clb8x10"))