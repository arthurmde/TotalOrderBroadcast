#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Messenger.h"

using namespace std;

string int_to_string(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


int main(int argc, char* argv[])
{
  int sequence = 1;

  cout << "Sequencer online" << endl;

  try
  {
    // Create the socket
    ServerSocket server(30000);

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

          string ip1 = "10.1.20.21";
          string ip2 = "localhost";
          string ip3 = "localhost";

    		  Messenger courier = Messenger();
    		  courier.addDestination(ip1,30000);
    		  //courier.addDestination(ip2,30000);
    		  //courier.addDestination(ip3,30000);
    		  courier.sendForAll(data);

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
