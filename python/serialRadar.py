import time
import serial
import turtle

clock = [1,2,4,8]
anticlock = [8,4,2,1]

direction = 0
ticks = 0
m = 0
pos=0.0;
centerX = -120
centerY = 0
radius = 140

textx = 240
texty = 0

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM3',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    rtscts = False,
    dsrdtr  = False,
    xonxoff = True
)


def printCordinates(my):
    print("x : {} , y: {}".format(my.xcor(), my.ycor()))


def showLine(my):
    my.penup()
    my.pencolor("green")
    my.setposition(centerX, centerY+140)
    my.pendown()
    my.forward(radius-3)
    printCordinates(my)


def hideLine(my):
    my.pencolor("white")
    my.setposition(centerX, centerY+140)
    my.pendown()
    my.forward(radius-3)
    my.pencolor("green")

turtle.setup(600, 600)
wn = turtle.Screen()
wn.title("Program Controlled Radar System")
myTurtle = turtle.Turtle()

myTurtle.pensize(3)
myTurtle.pencolor("green")
myTurtle.hideturtle()
myTurtle.penup()
myTurtle.goto(centerX,centerY)
myTurtle.pendown()
myTurtle.circle(radius)
ser.write(bytes(0))
while 1:
    while ser.inWaiting() > 0:
        out = ser.read(1)
        #print "Data: {}".format(out)
        if bytes(out) == bytes(3):
            showLine(myTurtle)
            #time.sleep(0.5)
    if direction == 0:
        showLine(myTurtle)
        myTurtle.right(7.5)
        m = ticks%4
        ser.write(bytes(clock[m]))
        time.sleep(0.5)
        hideLine(myTurtle)
    else:
        showLine(myTurtle)
        myTurtle.left(7.5)
        m = ticks%4
        ser.write(bytes(anticlock[m]))
        time.sleep(0.5)
        hideLine(myTurtle)
    ticks += 1
    if ticks == 48:
        ticks = 0
        direction = 1
