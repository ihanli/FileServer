#ifndef CONSUMER_H_
#define CONSUMER_H_

#define DOWNLOAD_FILE_PATH "files"
#define REQUESTED_BUFFER_SIZE 1024

#include "BoundedBuffer.h"
#include <fstream>
#include <boost/filesystem.hpp>

class Consumer
{
public:
	Consumer(BoundedBuffer* connectedSockets);
	void run(void);

private:
	BoundedBuffer* connectedSockets;
};

#endif

