#ifndef PRODUCER_H_
#define PRODUCER_H_

#define PORT 80

#include "BoundedBuffer.h"

class Producer
{
public:
	Producer(BoundedBuffer* connectedSockets);
	void run(void);

private:
	boost::asio::io_service ioService;
	tcp::acceptor acceptor;
	BoundedBuffer* connectedSockets;
};

#endif

