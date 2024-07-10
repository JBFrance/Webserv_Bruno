#include "Server.hpp"

const std::vector<std::string>	&Server::getServerName() const
{
	return (this->_serverName);
}

const std::multimap<std::string, std::string>	&Server::getListen() const
{
	return (this->_listen);
}

const std::string	&Server::getRoot() const
{
	return (this->_root);
}

const std::map<std::string, Location>	&Server::getLocation() const
{
	return (this->_location);
}

const std::vector<std::string>	&Server::getIndex() const
{
	return (this->_index);
}

bool	Server::getAutoindex() const
{
	return (this->_autoindex);
}

const std::map<int, std::string>	&Server::getErrorPage() const
{
	return (this->_errorPage);
}

unsigned long int	Server::getClientMaxBodySize() const
{
	return (this->_clientMaxBodySize);
}

const std::vector<std::string>	&Server::getAllowedMethods() const
{
	return (this->_allowedMethods);
}

const std::map<std::string, std::string>	&Server::getCgi() const
{
	return (this->_cgi);
}

const std::string	&Server::getUploadDir() const
{
	return (this->_uploadDir);
}

const std::string	&Server::getReturn() const
{
	return (this->_return);
}