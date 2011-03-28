#include "Consumer.h"

Consumer::Consumer(BoundedBuffer* connectedSockets) {
	this->connectedSockets = connectedSockets;
}

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
		
		stringstream httpResponse, payload;
		string singleLine;

		boost::filesystem::path path(DOWNLOAD_FILE_PATH + filename);
		if(boost::filesystem::is_regular_file(path)){
		
			ifstream requestedFile(DOWNLOAD_FILE_PATH + filename, ios::binary);

			while(getline(requestedFile, singleLine))
			{
				payload << singleLine << endl;
			}

			httpResponse << "HTTP/1.0 200 OK\n";
			httpResponse << "Server: FileServer/0.0.1\n";
			httpResponse << "Content-Type: application/octet-stream\n";

			requestedFile.close();
		}
		else {
			payload << "<html><head><title>404 Not Found</title><body><h1>404 Not Found</h1><p>The requested file was not found.</p></body></html>";
			httpResponse << "HTTP/1.0 404 Not Found\n";
			httpResponse << "Server: FileServer/0.0.1\n";
			httpResponse << "Content-Type: text/html\n";
		}

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