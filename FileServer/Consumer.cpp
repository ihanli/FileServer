#include "Consumer.h"

void Consumer::run(void)
{
	while(true)
	{
		tcp::socket socket = connectedSockets->get();
		string method, filename;
		char requestBuffer[requestBufferSize];
		int requestSize = socket.receive(boost::asio::buffer(requestBuffer, requestBufferSize));
		stringstream httpRequest(string(requestBuffer, requestSize));

		httpRequest >> method >> filename;

		//TODO: continue if method is get

		//TODO: open file and determine size

		std::stringstream httpResponse;
		httpResponse << "HTTP/1.0 200 OK\n";
		httpResponse << "Server: FileServer/0.0.1\n";
		httpResponse << "Content-Type: application/octet-stream\n";
		httpResponse << "Content-Length: " << payloadSize << "\n\n";
		// send the http-response header
		socket.send(boost::asio::buffer(httpResponse.str().c_str(), httpResponse.str().length()));

		// send the http-response payload
		socket.send(boost::asio::buffer(payload.c_str(), payloadSize));
		socket.shutdown(tcp::socket::shutdown_both);
		socket.close();
	}
}