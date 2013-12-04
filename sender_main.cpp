#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "Address.h"
#include "Messenger.h"

using namespace std;

int ID;

string int_to_string(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

vector<Address> read_ip_list_from_config_file()
{
	FILE *config_file;
	config_file = fopen("sender.config","r");
	vector<Address>ips;
	
	if(config_file== NULL)
	{
		cout << "Error reading configuration file." << endl;;
	}
	else
	{
		char temp;
		int port,qtd;

		fscanf(config_file,"%d",&ID);
		fscanf(config_file,"%d",&qtd);
		fscanf(config_file,"%c",&temp);
		
		for(int i=0;i<qtd;i++)
		{
			char char_ip[16];
			fscanf(config_file,"%s",char_ip);
			fscanf(config_file,"%d",&port);
			fscanf(config_file,"%c",&temp);
			string ip(char_ip);
			Address address;
			address.ip = ip;
			address.port = port;
			ips.push_back(address);
		}

		fclose(config_file);
	}

	return ips;
}


int main(int argc, char* argv[])
{
  int package = 1;
  string message;

  cout << "Sequencer online" << endl;

  try
  {
    // Create the socket
	  Messenger courier = Messenger();
	  vector<Address> addresses = read_ip_list_from_config_file();

	  for(int i=0;i<addresses.size();i++)
	  {
		  courier.addDestination(addresses[i].ip,addresses[i].port);
	  }

    while(true)
    {
	  
        message = int_to_string(ID) + " " + int_to_string(package);

	    courier.sendForAll(message);

        sleep((rand() % 3) + 1);

        package++;


      // thread thread_receiver(receive_messages, ref(new_sock)); 
    }
  }
  catch(SocketException& e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

  return 0;
}


