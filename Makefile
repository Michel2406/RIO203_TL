PROCESSES = trafficLight send 
OBJS = writeData.o

all: $(PROCESSES)

trafficLight: trafficLight.c writeData.o
	gcc trafficLight.c writeData.o -lwiringPi -o trafficLight

send: send.c
	gcc send.c -lcurl -o send -lwiringPi

writeData.o: writeData.c writeData.h

run:
	lxterminal --command="./trafficLight" & lxterminal --command="./send" 

clean::
	rm -f $(PROCESSES)
	rm -f $(OBJS)
