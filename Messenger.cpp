#include "Messenger.h"
#include <thread>
#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}

bool 
Messenger::addDestination(string ip, int port)
{
	Destination x;
	x.ip = ip;
	x.port = port;

	destinations.push_back(x);
	return true;
}


bool
Messenger::sendForAll(string data)
{
	vector<thread>threads;
	for(vector<Destination>::iterator it = destinations.begin() ; it!=destinations.end();it++)
	{
          thread broadcast1(this.sendSequencedPackage, it->ip,it->port, data);
		  threads.push_back(broadcast1);
	}
	
	for(vector<threads>::iterator it=threads.begin() ; it!=threads.end() ; it++)
		it->join();
}


void sendSequencedPackage(string ip, int port, string message)
{
  try
  {
    while(true)
    {
      //colocar IP do sequencer
      ClientSocket client_socket(ip, port);

      try
      {
        cout << "Sending message to " << ip << " | Message " << message << endl;

        //sleep((rand() % 3) + 1);
        client_socket << message;
      }
      catch (SocketException& e)
      {
        cout << "Intern SocketException:" << e.description() << "\n";
      }
    }
  }
  catch (SocketException& e)
  {
    cout << "Extertn SocketException was caught:" << e.description() << "\n";
  }
  
}
