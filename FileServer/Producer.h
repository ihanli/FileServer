#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "BoundedBuffer.h"

class Producer
{
public:
	Producer(BoundedBuffer* connectedSockets);

	void run(void);

private:
	const unsigned int PORT;
	boost::asio::io_service ioService;
	tcp::acceptor acceptor;
	BoundedBuffer* connectedSockets;
};

#endif

