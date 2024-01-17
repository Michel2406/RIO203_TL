PROCESSES = trafficLight

all: $(PROCESSES)

trafficLight: trafficLight.c writeData.o
	gcc trafficLight.c writeData.o -lwiringPi -o trafficLight

run:
	./trafficLight

clean::
	rm -f $(PROCESSES)
