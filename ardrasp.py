import serial """ para comunicarse por el puerto serie """
import time """ dejar tiempo de respuesta """

arduino = serial.Serial('/dev/ttyUSB0',baudrate=9600) """ crear la variable arduino """
arduino.open() """ abrir arduino """

texto='' """ arduino nos devuelve unos valores que guardamos en texto """

while True:

	comando = raw_input("Introduzca datos:") """ pedir que se introduzcan datos """
	arduino.write(comando) 
	time.sleep(0.1) """ tiempo de respuesta """
	while arduino.inWaiting() > 0 : """ mientras tengamos que leer algo de arduino """ 
		texto += arduino.read(1) """ texto igual a lo que estamos leyendo """
	print texto """ imprimir el texto """
	texto = '' """ vaciar la variabl texto """
arduino.close()
