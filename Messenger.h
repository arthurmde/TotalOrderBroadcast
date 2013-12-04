#include <vector>
#include <string>

using namespace std;

typedef struct _Destination
{
	string ip;
	int port;
}Destination;

class Messenger{

	public:
		Messenger();
		virtual ~Messenger();
		bool addDestination(string ip, int port);
		//bool sendSequencedPackage(string data);
		bool sendForAll(string data);

	private:
		vector<Destination> destinations;
};
