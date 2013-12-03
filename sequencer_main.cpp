#include "ServerSocket.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include "Messenger.h"

using namespace std;

void send_sequenced_package(string ip, string message)
{
  try
  {
    while(true)
    {
      //colocar IP do sequencer
      ClientSocket client_socket(ip, 30000);

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
          data = "GS " + int_to_string(sequence) + data;
         /* 
          string ip1 = "localhost";
          thread broadcast1(send_sequenced_package, ip1, data);
          string ip2 = "localhost";
          thread broadcast2(send_sequenced_package, ip2, data);
          string ip3 = "localhost";
          thread broadcast3(send_sequenced_package, ip3, data);

          broadcast1.join();
          broadcast2.join();
          broadcast3.join();
		  */

          string ip1 = "localhost";
          string ip2 = "localhost";
          string ip3 = "localhost";

		  Messenger courier();
		  courier.addDestination(ip1,30000);
		  courier.addDestination(ip2,30000);
		  courier.addDestination(ip3,30000);
		  courier.sendForAll();

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
