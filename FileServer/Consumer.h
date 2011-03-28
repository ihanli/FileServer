#ifndef CONSUMER_H_
#define CONSUMER_H_

#define DOWNLOAD_FILE_PATH "files"

#include "BoundedBuffer.h"
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;

class Consumer
{
public:
	Consumer(BoundedBuffer* connectedSockets);
	void run(void);

private:
	BoundedBuffer* connectedSockets;
};

#endif

