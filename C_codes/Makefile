PROCESSES = trafficLight send ultrasonic
OBJS = writeData.o

all: $(PROCESSES)

trafficLight: trafficLight.c writeData.o
	gcc trafficLight.c writeData.o -lwiringPi -o trafficLight

send: send.c
	gcc send.c -lcurl -o send -lwiringPi

ultrasonic: ultrasonic.c 
	gcc ultrasonic.c -lwiringPi -o ultrasonic

writeData.o: writeData.c writeData.h

run:
	lxterminal --command="./trafficLight" & lxterminal --command="./send" & lxterminal --command="./ultrasonic" 

clean::
	rm -f $(PROCESSES)
	rm -f $(OBJS)
