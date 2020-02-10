C++ 			= 		g++
MAIN   		=			main
MAINEXE		=			vehical
FLAG			=			-std=c++11 -Wall -fopenmp -lpthread
WIFICOMM  =     WifiComm
.DEFAULT_GOAL := all

clean:
	rm -f $(MAINEXE)

all:
	$(C++) *.cpp $(FLAG) -o $(MAINEXE)

upload-eth:
	tar -czf PiCode.tar.gz .
	scp ./PiCode.tar.gz ausar@10.42.0.1:~/Work/projects/Self_Driving_System_for_UGV/vehicle/RaspberryPi/
	rm PiCode.tar.gz

upload-wifi:
	tar -czf PiCode.tar.gz .
	scp ./PiCode.tar.gz ausar@192.168.4.165:~/Work/projects/Self_Driving_System_for_UGV/vehicle/RaspberryPi/
	rm PiCode.tar.gz