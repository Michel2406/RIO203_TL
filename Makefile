PROCESSES = trafficLight
OBJS = writeData.o

all: $(PROCESSES)

trafficLight: trafficLight.c writeData.o
	gcc trafficLight.c writeData.o -lwiringPi -o trafficLight

run:
	./trafficLight

clean::
	rm -f $(PROCESSES)
	rm -f $(OBJS)
