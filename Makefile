# Makefile for the socket programming example
#
STD_FLAGS = -W -Wall -ansi -pedantic

HEARDERS = $(wildcard *.cpp)

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o
sender_objects = ClientSocket.o Socket.o sender_main.o
sequencer_objects = ServerSocket.o Socket.o ClientSocket.o
destination_objects = ServerSocket.o Socket.o
messenger_objects = Socket.o ClientSocket.o

all : simple_server simple_client sender sequencer destination

simple_server: $(simple_server_objects)
	g++ -o simple_server $(simple_server_objects)

simple_client: $(simple_client_objects)
	g++ -o simple_client $(simple_client_objects)

sender: $(sender_objects)
	g++ -o sender $(sender_objects)

sequencer: $(sequencer_objects)
	g++  -pthread -std=gnu++0x -o sequencer $(sequencer_objects) sequencer_main.cpp Messenger.cpp

destination: $(destination_objects)
	g++ -o destination $(destination_objects) destination_main.cpp

messenger: $(messenger_objects)
	g++  -pthread -std=gnu++0x -c -o $(messenger_objects) Messenger.cpp

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp
sender_main: sender_main.cpp

clean:
	rm -f *.o simple_server simple_client sender sequencer destination