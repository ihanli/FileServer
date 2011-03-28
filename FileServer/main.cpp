#include "BoundedBuffer.h"
#include "Consumer.h"
#include "Producer.h"

int main() {
	
	cout << "Initialize bounded buffer for the sockets." << endl;
	BoundedBuffer *boundedBuffer = new BoundedBuffer(50);

	cout << "Initialize producer." << endl;
	Producer producer(boundedBuffer);

	cout << "Initialize consumers." << endl;
	for(int i = 0; i < 20; i++)
	{
		Consumer consumer(boundedBuffer);
		boost::thread consumerThread(boost::bind(&Consumer::run, &consumer));
	}
	
	producer.run();

	system("PAUSE");
	return 0;
}