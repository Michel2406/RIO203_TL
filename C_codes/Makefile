PROCESSES = trafficLight ultrasonic
OBJS = writeData.o

all: $(PROCESSES)

trafficLight: trafficLight.c writeData.o
	gcc trafficLight.c writeData.o -lwiringPi -o trafficLight

ultrasonic: ultrasonic.c 
	gcc ultrasonic.c -lwiringPi -o ultrasonic

writeData.o: writeData.c writeData.h

run:
	lxterminal --command="./trafficLight" & lxterminal --command="python ../Python_codes/main.py" & lxterminal --command="./ultrasonic" & lxterminal --command="python ../Python_codes/receive.py"

clean::
	rm -f $(PROCESSES)
	rm -f $(OBJS)
