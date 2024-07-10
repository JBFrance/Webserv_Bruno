#include "Server.hpp"

void	Server::setServerName(t_str &value)
{
	char	*token;

	token = std::strtok(&value[0], " \t\v\r\n\f");
	if (token == NULL)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of server_name is empty.");
	while (token != NULL)
	{
		this->_serverName.push_back(token);
		token = std::strtok(NULL, " \t\v\r\n\f");
	}
}

void	Server::setLocation(t_str &value)
{
	std::string::size_type	pos;
	std::string::size_type	pos2;
	std::string				name;
	std::string				inner;

	pos = value.find_first_of("{");
	name = value.substr(0, pos);
	pos2 = name.find_last_not_of(" \t\v\r\n\f");
	if (pos2 == std::string::npos)
		throw std::runtime_error("Error: Location is not valid.");
	++pos2;
	name = name.substr(0, pos2);
	++pos;
	inner = value.substr(pos, value.length() - 1 - pos);
	if (name[0] != '/')
		throw std::runtime_error("Error: Location must start with '/' symbol.");
	if (name[name.length() - 1] != '/')
		name += "/";
	this->_location.insert(std::make_pair(name, Location(inner)));
}

void	Server::setListen(t_str &addr, t_str &port)
{
	this->_serverName.push_back(addr);
	addr = "*";
	std::multimap<t_str, t_str>::iterator	it1 = _listen.lower_bound(addr);
	std::multimap<t_str, t_str>::iterator	it2 = _listen.upper_bound(addr);
	while (it1 != it2)
	{
		if (it1->first == addr && it1->second == port)
			throw std::runtime_error("Error: duplicate listen values.");
		++it1;
	}
	this->_listen.insert(std::make_pair(addr, port));
}

void	Server::setRoot(t_str &value)
{
	std::string::size_type	pos;
	std::string				path;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: root value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value.find_first_of(" \t\v\r\n\f") != std::string::npos)
		throw std::runtime_error("Error: root isn't valid "
								 "(there are whitespaces).");
	if (value.compare(0, 4, "www/") != 0)
		throw std::runtime_error("Error: root must start with 'www/' path.");
	// if (access(value.c_str(), F_OK) != 0)
	// 	throw std::runtime_error("Error: root directory not found.");
	this->_root = value;
}

void	Server::setIndex(t_str &value)
{
	char	*token;

	token = std::strtok(&value[0], " \t\v\r\n\f");
	if (token == NULL)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of index is empty.");
	while (token != NULL)
	{
		this->_index.push_back(token);
		token = std::strtok(NULL, " \t\v\r\n\f");
	}
}

void	Server::setAutoindex(t_str &value)
{
	std::string::size_type	pos;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: autoindex value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value == "on")
		this->_autoindex = true;
	else if (value == "off")
		this->_autoindex = false;
	else
		throw std::runtime_error("Error: autoindex value can only be "
								 "'on' or 'off'.");
}

void	Server::setErrorPage(t_str &value)
{
	t_str::size_type	pos;
	char				*token;
	t_str				page;
	int					error_number;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of error_page is empty.");
	value = value.substr(0, ++pos);
	pos = value.find_last_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: Config file: Directive value of "
								 "error_page must contain an error number"
								 "and after that an error page uri.");
	++pos;
	page = value.substr(pos, value.length() - pos);
	value = value.substr(0, pos - 1);
	token = std::strtok(&value[0], " \t\v\r\n\f");
	while (token != NULL)
	{
		error_number = std::atoi(token);
		if (!(error_number >= 300 && error_number <= 599))
			throw std::runtime_error("Error: Config file: Directive "
									 "value of error_page must be between "
									 "'300' and '599' range.");
		this->_errorPage.insert(std::make_pair(error_number, page));
		token = std::strtok(NULL, " \t\v\r\n\f");
	}
}

void	Server::setClientMaxBodySize(t_str &value)
{
	std::string::size_type	pos;
	int						coefficient;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: client_max_body_size value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value.back() == 'k' || value.back() == 'K')
	{
		coefficient = 1024;
		value.pop_back();
	}
	else if (value.back() == 'm' || value.back() == 'M')
	{
		coefficient = 1024 * 1024;
		value.pop_back();
	}
	else if (value.back() >= '0' && value.back() <= '9')
		coefficient = 1;
	else
		throw std::runtime_error("Error: client_max_body_size is not valid.");
	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: client_max_body_size value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value == "")
		throw std::runtime_error("Error: client_max_body_size is not valid.");
	for (std::string::iterator it = value.begin(); it != value.end(); ++it)
	{
		if (!(*it >= '0' && *it <= '9'))
			throw std::runtime_error("Error: client_max_body_size is not valid.");
	}
	this->_clientMaxBodySize = coefficient * std::atol(value.c_str());
}

void	Server::setAllowedMethods(t_str &value)
{
	char	*token;

	token = std::strtok(&value[0], " \t\v\r\n\f");
	if (token == NULL)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of allow_methods is empty.");
	while (token != NULL)
	{
		if (std::strncmp(token, "GET", std::strlen(token)) != 0 && \
			std::strncmp(token, "POST", std::strlen(token)) != 0 && \
			std::strncmp(token, "DELETE", std::strlen(token)) != 0)
			throw std::runtime_error("Error: The values of allow_methods must" \
									 " be one of these 'GET' 'POST' 'DELETE'.");
		this->_allowedMethods.push_back(token);
		token = std::strtok(NULL, " \t\v\r\n\f");
	}
}

void	Server::setCgi(t_str &value)
{
	t_str::size_type	pos;
	t_str				uri;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of cgi is empty.");
	value = value.substr(0, ++pos);
	pos = value.find_last_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: Config file: Directive value of "
								 "cgi must contain a cgi extension"
								 "and after that the cgi uri.");
	++pos;
	uri = value.substr(pos, value.length() - pos);
	value = value.substr(0, pos - 1);
	pos = value.find_last_not_of(" \t\v\r\n\f");
	value = value.substr(0, ++pos);
	if (value.find(" \t\v\r\n\f") != std::string::npos)
		throw std::runtime_error("Error: Config file: Directive "
								 "value of cgi is not valid.");
	// if (access(uri.c_str(), F_OK) != 0)
	// 	throw std::runtime_error("Error: cgi file not found.");
	this->_cgi.insert(std::make_pair(value, uri));
}

void	Server::setUploadDir(t_str &value)
{
	std::string::size_type	pos;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: upload_dir value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value.find_first_of(" \t\v\r\n\f") != std::string::npos)
		throw std::runtime_error("Error: upload_dir isn't valid "
								 "(there are whitespaces).");
	if (value.compare(0, 4, "www/") != 0)
		throw std::runtime_error("Error: upload_dir must start with 'www/' path.");
	if (access(value.c_str(), F_OK) != 0)
		throw std::runtime_error("Error: upload_dir value does not exist.");
	this->_uploadDir = value;
}

void	Server::setReturn(t_str &value)
{
	std::string::size_type	pos;

	pos = value.find_last_not_of(" \t\v\r\n\f");
	if (pos == std::string::npos)
		throw std::runtime_error("Error: return directive value is empty.");
	++pos;
	value = value.substr(0, pos);
	if (value.find_first_of(" \t\v\r\n\f") != std::string::npos)
		throw std::runtime_error("Error: return directive isn't valid "
								 "(there are whitespaces).");
	if (value[0] != '/' && value.compare(0, 7, "http://") != 0 && \
			value.compare(0, 8, "https://") != 0)
		throw std::runtime_error("Error: return directive must start with " \
								"one of this 'http://', 'https://', '/'.");
	this->_return = value;
}

void	Server::setFildes(const t_str &name, t_str &value)
{
	if (name.compare("server_name") == 0)
		this->setServerName(value);
	else if (name.compare("listen") == 0)
		this->parsingListen(value);
	else if (name.compare("root") == 0)
		this->setRoot(value);
	else if (name.compare("location") == 0)
		this->setLocation(value);
	else if (name.compare("index") == 0)
		this->setIndex(value);
	else if (name.compare("autoindex") == 0)
		this->setAutoindex(value);
	else if (name.compare("error_page") == 0)
		this->setErrorPage(value);
	else if (name.compare("client_max_body_size") == 0)
		this->setClientMaxBodySize(value);
	else if (name.compare("allow_methods") == 0)
		this->setAllowedMethods(value);
	else if (name.compare("cgi") == 0)
		this->setCgi(value);
	else if (name.compare("upload_dir") == 0)
		this->setUploadDir(value);
	else if (name.compare("return") == 0)
		this->setReturn(value);
}

void	Server::setDefaults()
{
	std::string::size_type	pos;
	std::string				path;
	std::string				value("www/");
	char					*isPathOk;

	if (this->_root == "")
	{
		isPathOk = std::getenv("_");
		if (isPathOk == nullptr)
			throw std::runtime_error("Error: env variable '$_' does not found.");
		path = static_cast<std::string>(isPathOk);
		pos = path.find_last_of("/") + 1;
		if (pos == std::string::npos)
			throw std::runtime_error("Error: not found '/' in env variable '$_'");
		path = path.substr(0, pos);
		value = path + value;
		// if (access(value.c_str(), F_OK) != 0)
		// 	throw std::runtime_error("Error: root directory not found.");
		this->_root = value;
	}
	if (this->_allowedMethods.size() == 0)
	{
		this->_allowedMethods.push_back("GET");
		this->_allowedMethods.push_back("POST");
		this->_allowedMethods.push_back("DELETE");
	}
}