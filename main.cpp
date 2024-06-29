#include "webserv.hpp"

void	start(std::string config)
{
	std::vector <Server> *servset;
	servset = parsing(config);
	// try
	// {
	// 	vatche server stuff
	// }
	// catch (const std::exception &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
	delete servset;
}

int	main(int argc, char **argv)
{
	std::string	config;

	try
	{
		if (argc == 1)
			file_open_read(CONFIG_DEFAULT, config);
		else if (argc == 2)
			file_open_read(argv[1], config);
		else
			throw std::runtime_error("Error: Argumets count must be 1 or 0.");
		start(config);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() <<  std::endl;
	}
	return (0);
}
