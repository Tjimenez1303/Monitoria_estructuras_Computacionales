import time
import pip

pip.main(['install', 'pyserial'])

import serial
import telnetlib 

serialPort = serial.Serial(
    port="COM10", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)

tn = telnetlib.Telnet("192.168.203.55", 23)

serialString = ""  # Used to hold data coming over UART
telnetString = ""  # Used to hold data coming over telnet


print("Sending data")
tn.write(b"\nEnvio este string al ESP8266\n") 
serialPort.write(b"\nEnvio este string al VCOM\n")

while 1:
    # Wait until there is data waiting in the serial buffer
    time.sleep(0.01)
    if serialPort.in_waiting > 0:
        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()

        # Print the contents of the serial data
        try:
            print(serialString.decode("Ascii"))
        except:
            pass


# TODO: Close connections

