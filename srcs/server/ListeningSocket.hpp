#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include "hdelibc-server.hpp"

class BindingSocket;

class ListeningSocket: public BindingSocket {
	private:
		int backlog;
		int listening;


	public:
		ListeningSocket(int domain, int service, int protocol, int port, std::string ipAddress, int bklog);
		void start_listening();
};


#endif