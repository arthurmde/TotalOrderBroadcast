#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>

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
	config_file = fopen("destination.config","r");
	
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



int main(int argc, char* argv[])
{
  int port = read_port_from_config_file();
  if(port<=0)
  {
	  return 1;
  }
  
  try
  {
    // Create the socket
    ServerSocket server(port);

	cout << "Destination waiting for messages at port " << port << endl;

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
          cout << "Processing: " << data << endl;
         
          /*new_sock << data;*/
        }
      }
      catch(SocketException& e) {}

      // thread thread_receiver(receive_messages, ref(new_sock)); 
    }
  }
  catch(SocketException& e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

  return 0;
}
