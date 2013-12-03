#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;

void receive_messages(ServerSocket& new_sock)
{
  try
  {
    while(true)
    {
      string data;
      new_sock >> data;
      cout << "Recebido: " << data << endl;
      new_sock << data;
    }
  }
  catch(SocketException& e)
  {
    cout << "Thread SocketException : " << e.description() << endl;
  }
  
}

int main(int argc, char* argv[])
{
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
          new_sock << data;
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
