#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "BoundedBuffer.h"
#include <fstream>

using namespace std;

class Consumer
{
public:
	Consumer(BoundedBuffer* connectedSockets) : FILE_PATH("files/") { this->connectedSockets = connectedSockets; }
	~Consumer(void);
	void run(void);

private:
	BoundedBuffer* connectedSockets;
	ifstream requestedFile;
	//const int REQUEST_BUFFER_SIZE;
	const string FILE_PATH;
};

#endif

