#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "Address.h"

using namespace std;

int ID=0;

string int_to_string(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

Address read_config_file()
{
	FILE *config_file;
	Address address;
	address.ip="";
	address.port=-1;

	config_file = fopen("sender.config","r");
	
	if(config_file== NULL)
	{
		printf("Error reading configuration file.\n");
	}
	
	else
	{
		char char_ip[16];
		int port;
		fscanf(config_file,"id = %d\nsequencer_ip = %s\nsequencer_port = %d",&ID, char_ip,&port);
		fclose(config_file);

		string ip(char_ip);
		address.ip = ip;
		address.port = port;
	}

	return address;
}



int main ( int argc, char* argv[] )
{
  int package = 1;
  string message;

  Address address = read_config_file();
  if(address.port<0)
  {
		printf("Error reading configuration file.\n");
		return 1;
  }

  srand(time(NULL));

  try
  {
	cout << "Connecting to " << address.ip << " at port " << address.port << endl;
    while(true)
    {
      //colocar IP do sequencer
      ClientSocket client_socket(address.ip, address.port);

      try
      {
        cout << "Sending message to " << address.ip << " at port " << address.port << " | Message N." << package << endl;
         
        message = int_to_string(ID) + " " + int_to_string(package);

        client_socket << message;

        sleep((rand() % 3) + 1);

        package++;
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

  return 0;
}
