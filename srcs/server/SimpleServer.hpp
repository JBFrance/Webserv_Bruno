#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include "hdelibc-server.hpp"

class ListeningSocket;

class SimpleServer {
	protected:
		ListeningSocket* socket;
		char buffer[30000];
		int	new_socket;
		void accepter();
		void handler();
		void responder();

	public:
		SimpleServer(int domain, int service, int protocol, int port, std::string ipAddress, int bklg);
		~SimpleServer();
		void launch();
		ListeningSocket* get_socket();
};

#endif