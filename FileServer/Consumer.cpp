#include "Consumer.h"

void Consumer::run(void)
{
	while(true)
	{
		tcp::socket* socket = connectedSockets->get();
		string method, filename;
		char requestBuffer[1024];
		int requestSize = socket->receive(boost::asio::buffer(requestBuffer, 1024));
		stringstream httpRequest(string(requestBuffer, requestSize));

		httpRequest >> method >> filename;

		//TODO: continue if method is get

		stringstream payload;
		string singleLine;
		requestedFile.open(FILE_PATH + filename);
		
		while(getline(requestedFile, singleLine))
		{
			payload << singleLine;
		}

		requestedFile.close();

		std::stringstream httpResponse;
		httpResponse << "HTTP/1.0 200 OK\n";
		httpResponse << "Server: FileServer/0.0.1\n";
		httpResponse << "Content-Type: application/octet-stream\n";
		httpResponse << "Content-Length: " << payload.str().length() << "\n\n";
		// send the http-response header
		socket->send(boost::asio::buffer(httpResponse.str().c_str(), httpResponse.str().length()));

		// send the http-response payload
		socket->send(boost::asio::buffer(payload.str().c_str(), payload.str().length()));
		socket->shutdown(tcp::socket::shutdown_both);
		socket->close();
	}
}