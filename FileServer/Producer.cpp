#include "Producer.h"

void Producer::run(void)
{
	while(true)
	{
		tcp::socket socket(ioService);
		acceptor.accept(socket);
		connectedSockets->put(&socket);

		cout << "Connection accepted from " << socket.remote_endpoint() << endl;
	}
}
