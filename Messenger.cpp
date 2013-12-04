#include "Messenger.h"
#include <thread>
#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"
#include <vector>

using namespace std;

Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}

bool Messenger::addDestination(string ip, int port)
{
	Destination x;
	x.ip = ip;
	x.port = port;

	destinations.push_back(x);
	return true;
}


void sendSequencedPackage(string ip, int port, string message)
{
  try
  {
    //colocar IP do sequencer
    ClientSocket client_socket(ip, port);

    try
    {
      cout << "Sending message to " << ip << " | Message " << message << " " << endl;

      //sleep((rand() % 3) + 1);
      client_socket << message;
    }
    catch (SocketException& e)
    {
      cout << "Intern SocketException:" << e.description() << "\n";
    }
  }
  catch (SocketException& e)
  {
    cout << "Extertn SocketException was caught:" << e.description() << "\n";
  }
  
}


bool Messenger::sendForAll(string data)
{
	thread threads[destinations.size()];

	for(int j = 0, i = 0; j < (int)destinations.size(); j++, i++)
	{
      threads[i] = thread(sendSequencedPackage, destinations[j].ip, destinations[j].port, data);
	}
	
	for(int i = 0; i < (int)destinations.size(); i++)
  {
    threads[i].join();
  }
}



