#include "Server.hpp"

void Server::start() {
	while (!_done) {
		if (_selector.wait())
			connectClient();
		else
			sharePacket();
	}
}

void Server::connectClient() {
	TcpSocket* socket = new TcpSocket();
	_listener.accept(*socket);
	_selector.add(*socket);
	_clients.push_back(socket);

	Packet receivePacket;

	if (socket->receive(receivePacket) == Socket::Done) {
		string pseudo;
		receivePacket >> pseudo;
		cout << pseudo << " just connected" << endl;
	}
}

void Server::sharePacket() {
	for (auto&& client : _clients)
		if (_selector.isReady(*client)) {
			Packet receivePacket;
			if (client->receive(receivePacket) == Socket::Done) {
				string pseudo;
				int x, y;
				receivePacket >> pseudo >> x >> y;
				cout << "Got from the client " << pseudo << " x: " << x << " y: " << y << endl;
				cout << "Remote Adress : " << client->getRemoteAddress().toString() << endl;

				Packet sendPacket;

				sendPacket << pseudo << x << y;
				for (auto&& others : _clients) {
					if (client != others) {
						others->send(sendPacket);
					}
				}
			}
		}
}