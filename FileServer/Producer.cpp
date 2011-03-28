#include "Producer.h"

Producer::Producer(BoundedBuffer* connectedSockets) : PORT(80), acceptor(ioService, tcp::endpoint(tcp::v4(), PORT))
{
	this->connectedSockets = connectedSockets;
	cout << "File server listening on port " << PORT << endl;
}

void Producer::run(void)
{
	while(true)
	{
		tcp::socket *socket = new tcp::socket(ioService);
		acceptor.accept(*socket);
		connectedSockets->put(socket);

		cout << "Connection accepted from " << socket->remote_endpoint() << endl;
	}
}
