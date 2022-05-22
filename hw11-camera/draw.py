# draw a 40 x 30 image from serial data
import serial
ser = serial.Serial('/dev/tty.usbmodem143201',timeout=5) # use your port name
#print(ser.name)

import numpy as np # for arrays

# size of the window, each pixel will be 10 x 10
WIDTH = 400
HEIGHT = 300

# arrays to store data
red = np.linspace(0,0,40*30)
green = np.linspace(0,0,40*30)
blue = np.linspace(0,0,40*30)

# send a newline to ask for a new image
ser.write(('\n').encode())

def draw():
    ind = 0
    for y in [7,14,21]:
        ind = ind + 1 # fudge
        for x in range(0,39,1):
            BOX = Rect((x*10, y*10), (10, 10))
            COLOR = red[ind],green[ind],blue[ind]
            screen.draw.filled_rect(BOX, COLOR)
            ind = ind + 1

def update():
    data_read = ser.readline() # read a line into a bytearray
    data_text = str(data_read,'utf-8') # turn the line into a string
    data = list(map(int,data_text.split())) # turn the string into a list of ints

    if(len(data)==4):
        red[data[0]] = data[1]
        green[data[0]] = data[2]
        blue[data[0]] = data[3]
        #print(data[0])
        # after you get an image, ask for another
        if data[0] == 1199:
            ser.write(('\n').encode())
