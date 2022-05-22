import board
from adafruit_ov7670 import (
    OV7670,
    OV7670_SIZE_DIV16,
    OV7670_COLOR_YUV,
    OV7670_TEST_PATTERN_COLOR_BAR,
)

import sys
import time
import digitalio
import busio
from ulab import numpy as np

with digitalio.DigitalInOut(board.GP10) as reset:
    reset.switch_to_output(False)
    time.sleep(0.001)
    bus = busio.I2C(scl=board.GP5, sda=board.GP4)

cam = OV7670(
    bus,
    data_pins=[
        board.GP12,
        board.GP13,
        board.GP14,
        board.GP15,
        board.GP16,
        board.GP17,
        board.GP18,
        board.GP19,
    ],
    clock=board.GP11,
    vsync=board.GP7,
    href=board.GP21,
    mclk=board.GP20,
    shutdown=board.GP22,
    reset=board.GP10,
)

pid = cam.product_id
ver = cam.product_version
#print(f"Detected pid={pid:x} ver={ver:x}")

cam.size = OV7670_SIZE_DIV16
#print(cam.width)
##print(cam.height)

#cam.test_pattern = OV7670_TEST_PATTERN_COLOR_BAR

cam.colorspace = OV7670_COLOR_YUV
cam.flip_y = True

buf = bytearray(2 * cam.width * cam.height) # where all the raw data is stored

# store the converted pixel data
red = np.linspace(1,1,cam.width * cam.height, dtype=np.float)
green = np.linspace(0,0,cam.width * cam.height, dtype=np.float)
blue = np.linspace(0,0,cam.width * cam.height, dtype=np.float)
ind = 0

while True:
    sys.stdin.readline() # wait for a newline before taking an image
    cam.capture(buf) # get the image

    # process the raw data into color pixels
    ind = 0
    for d in range(0,2 * cam.width * cam.height,4):
        u = buf[d+1] - 128
        v = buf[d+3] - 128
        red[ind] = buf[d] + 1.370705 * v
        if red[ind] > 255:
            red[ind] = 255
        if red[ind] < 0:
            red[ind] = 0
        green[ind] = buf[d] - 0.337633 * u - 0.698001 * v
        if green[ind] > 255:
            green[ind] = 255
        if green[ind] < 0:
            green[ind] = 0
        blue[ind] = buf[d] + 1.732446 * u
        if blue[ind] > 255:
            blue[ind] = 255
        if blue[ind] < 0:
            blue[ind] = 0

        ind = ind+1
        red[ind] = buf[d+2] + 1.370705 * v
        if red[ind] > 255:
            red[ind] = 255
        if red[ind] < 0:
            red[ind] = 0
        green[ind] = buf[d+2] - 0.337633 * u - 0.698001 * v
        if green[ind] > 255:
            green[ind] = 255
        if green[ind] < 0:
            green[ind] = 0
        blue[ind] = buf[d+2] + 1.732446 * u
        if blue[ind] > 255:
            blue[ind] = 255
        if blue[ind] < 0:
            blue[ind] = 0
        ind=ind+1

    # send the color data as index red green blue
    for c in range(red.size):
        print(str(c)+" "+str(int(red[c]))+" "+str(int(green[c]))+" "+str(int(blue[c])))
