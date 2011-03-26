#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "BoundedBuffer.h"

class Consumer
{
public:
	Consumer(BoundedBuffer* connectedSockets) { this->connectedSockets = connectedSockets; }
	~Consumer(void);
	void run(void);

private:
	BoundedBuffer* connectedSockets;
	const unsigned int requestBufferSize = 1024;
};

#endif

