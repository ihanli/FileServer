#include "Producer.h"

Producer::Producer(BoundedBuffer* connectedSockets) : acceptor(ioService, tcp::endpoint(tcp::v4(), PORT))
{
	this->connectedSockets = connectedSockets;
	std::cout << "File server listening on port " << PORT << std::endl;
}

void Producer::run(void)
{
	while(true)
	{
		tcp::socket *socket = new tcp::socket(ioService);
		acceptor.accept(*socket);
		connectedSockets->put(socket);

		std::cout << "Connection accepted from " << socket->remote_endpoint() << std::endl;
	}
}
