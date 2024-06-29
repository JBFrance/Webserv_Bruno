#include "serverheaders.hpp"

int main() {

    int port = 8082;
    std::string ipAddress = "127.0.0.1";

    SimpleServer *t = new SimpleServer(AF_INET, SOCK_STREAM, 0, port, ipAddress , 5);

    
    delete t;
    // (void) t;

// 	int port = 7777;
// 	// const char *ipAddr = "127.0.0.1";

// 	std::cout << "Starting..." << std::endl;

// 	// std::cout << "Binding socket..." << std::endl;
// 	// BindingSocket bs = BindingSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);
// 	// std::cout << bs.get_sock() << " = socket " << bs.get_connection() << std::endl;

// 	std::cout << "Listening socket..." << INADDR_ANY  << std::endl;
// 	ListeningSocket ls = ListeningSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10);
// 	std::cout << ls.get_sock() << "= socket " << ls.get_connection() << std::endl;


// 	std::cout << "Success" << std::endl;
	
}