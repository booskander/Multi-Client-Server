#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;
class Server {
private:
	short int _port;
	TcpListener _listener;
	SocketSelector _selector;
	bool _done = false;
	vector<TcpSocket*> _clients;

private:
	bool isPortAvailable() {
		return _listener.listen(_port) == Socket::Done;
	}
public :
	Server(short int port) : _port(port) {
		_selector.add(_listener);
	}

	Server() : Server(2000) {};
	void listen() {
		if (!isPortAvailable()) {
			cout << "This port is currently unavailable, choose a new one" << endl;
			exit(0);
		}
		else {
			cout << "Listening on port " << _port << endl;
			start();
		}
	}

public:
	void start();
	void sharePacket();
	void connectClient();
	
};