#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "BoundedBuffer.h"

class Producer
{
public:
	Producer(BoundedBuffer* connectedSockets) : PORT(80), acceptor(ioService, tcp::endpoint(tcp::v4(), PORT))
	{
		this->connectedSockets = connectedSockets;
		cout << "File server listening on port " << PORT << endl;
	}
	~Producer(void);
	void run(void);

private:
	const unsigned int PORT;
	boost::asio::io_service ioService;
	tcp::acceptor acceptor;
	BoundedBuffer* connectedSockets;
};

#endif

