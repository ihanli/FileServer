#include "BoundedBuffer.h"

BoundedBuffer::~BoundedBuffer(void)
{
}

void BoundedBuffer::put(tcp::socket* element) {
	freeElements.wait();
	{
		boost::mutex::scoped_lock lock(queueMutex);
		queue.push_back(element);
	}
	availableElements.post();
}

tcp::socket* BoundedBuffer::get(void) {
	tcp::socket* element;

	availableElements.wait();
	{
		boost::mutex::scoped_lock lock(queueMutex);
		element = queue.front();
		queue.pop_front();
	}
	freeElements.post();

	return element;
}