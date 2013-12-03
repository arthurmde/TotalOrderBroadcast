#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string int_to_string(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


int main(int argc, char* argv[])
{
  cout << "Destinantion waiting for messages" << endl;

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
