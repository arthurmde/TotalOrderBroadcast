#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Messenger.h"
#include "Address.h"

using namespace std;

string int_to_string(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int read_port_from_config_file()
{
	int port;
	FILE *config_file;
	config_file = fopen("sequencer.config","r");
	
	if(config_file== NULL)
	{
		cout << " Error reading configuration file." << endl;
		return -1;
	}
	else
	{
		fscanf(config_file,"server_port = %d",&port);
		fclose(config_file);
		return port;
	}
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
		char char_ip[16];
		int port;

		fscanf(config_file,"server_port = %d",&port);
		while(fscanf(config_file,"destination_ip = %s",char_ip)!=EOF || fscanf(config_file,"destination_port = %d",&port)!=EOF)
		{
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
  int sequence = 1;

  int port = read_port_from_config_file();
  if(port<=0)
  {
	  return 1;
  }

  cout << "Sequencer online" << endl;

  try
  {
    // Create the socket
    ServerSocket server(port);

    while(true)
    {
      ServerSocket new_sock;
      server.accept(new_sock);

      try
      {
        while(true)
        {
          string data;
          new_sock >> data;
          cout << "Recebido: " << data << endl;
          data = "GS " + int_to_string(sequence) + " " + data;

		  Messenger courier = Messenger();
		  vector<Address> addresses = read_ip_list_from_config_file();
		  for(int i=0;i<addresses.size();i++)
		  {
			  cout << "Adicionando o destino: " << addresses[i].ip << " com porta " << addresses[i].port << endl;
			  courier.addDestination(addresses[i].ip,addresses[i].port);
		  }
          /*new_sock << data;*/
        }
      }
      catch(SocketException& e) {}

      sequence++;

      // thread thread_receiver(receive_messages, ref(new_sock)); 
    }
  }
  catch(SocketException& e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

  return 0;
}
