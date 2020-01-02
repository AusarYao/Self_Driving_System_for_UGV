import serial
import time

ser=serial.Serial("/dev/ttyACM0",57600,
                  parity=serial.PARITY_NONE,
                  stopbits=serial.STOPBITS_ONE,
                  bytesize=serial.EIGHTBITS)  #change ACM number as found from ls /dev/tty/ACM


values = bytearray([128, 4, 0, 0, 0, 100])
while(1):
    ser.write(values)
    time.sleep(2)
