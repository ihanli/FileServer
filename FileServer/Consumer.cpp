#include "Consumer.h"

Consumer::Consumer(BoundedBuffer* connectedSockets) 
{
	this->connectedSockets = connectedSockets;
}

void Consumer::run(void)
{
	while(true)
	{
		tcp::socket* socket;
		std::string method, filename, singleLine;
		std::stringstream httpRequest, httpResponse, payload;
		std::ifstream requestedFile;
		int requestSize;
		char requestBuffer[REQUESTED_BUFFER_SIZE];

		socket = connectedSockets->get();
		requestSize = socket->receive(boost::asio::buffer(requestBuffer, REQUESTED_BUFFER_SIZE));
		httpRequest << std::string(requestBuffer, requestSize);

		httpRequest >> method >> filename;

		requestedFile.open(DOWNLOAD_FILE_PATH + filename, std::ios::binary);

		if(requestedFile.is_open())
		{
			while(getline(requestedFile, singleLine))
			{
				payload << singleLine << std::endl;
			}

			httpResponse << "HTTP/1.0 200 OK\n";
			httpResponse << "Content-Type: application/octet-stream\n";

			requestedFile.close();
		}
		else
		{
			payload << "<html><head><title>404 Not Found</title><body><h1>404 Not Found</h1><p>The requested file was not found.</p></body></html>";
			httpResponse << "HTTP/1.0 404 Not Found\n";
			httpResponse << "Content-Type: text/html\n";
		}

		httpResponse << "Server: FileServer/0.0.1\n";
		httpResponse << "Content-Length: " << payload.str().length() << "\n\n";

		// send the http-response header
		socket->send(boost::asio::buffer(httpResponse.str().c_str(), httpResponse.str().length()));
		
		// send the http-response payload
		socket->send(boost::asio::buffer(payload.str().c_str(), payload.str().length()));
		socket->shutdown(tcp::socket::shutdown_both);
		socket->close();

		delete socket;
	}
}