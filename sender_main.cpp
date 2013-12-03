#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#define HOST 1

string string_to_int(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int main ( int argc, char* argv[] )
{
  int package = 1;
  string message;
  string sequencer_ip = "localhost";

  srand(time(NULL));

  try
  {
    while(true)
    {
      //colocar IP do sequencer
      ClientSocket client_socket(sequencer_ip, 30000);

      try
      {
        cout << "Sending message to " << sequencer_ip << " | Message N." << package << endl;
         
        message = string_to_int(HOST) + " " + string_to_int(package);

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
