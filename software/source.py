import struct
import socket
import serial

SOCK_IP = "127.0.0.1"
SOCK_PORT = 4242
SERIAL_PORT = 'COM9'
SERIAL_SPEED = 115200

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
arduino = serial.Serial(SERIAL_PORT, SERIAL_SPEED)

def read_serial():
    line = arduino.readline().decode('utf-8').strip()
    return [float(x) for x in line.split()]

while True:
    # Read data from Arduino, 3 floats
    data = read_serial()
    if data and len(data) == 3:
        sock.sendto(
            struct.pack('@6d',
                0, 0, 0, # xyz
                data[0],data[1],data[2]), # rpy
            (SOCK_IP, SOCK_PORT))