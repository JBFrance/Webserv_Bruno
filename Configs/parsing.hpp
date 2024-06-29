#ifndef PARSING_HPP
# define PARSING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

struct Location
{
    std::string _cgi;
    std::string _error_page;
    std::string _root;
    std::string upload_dir;
    int _maxbodysize;
};

class servData
{
    private:
        std::string _ip;
        unsigned int _port;
        std::string _index;
        std::string _root;
        std::string _errorPage;
        std::string _serverName;
        bool _autoIndex;
        std::vector<std::pair<int, std::string> > _errorPath;
        std::vector<std::string> _methods;
        int clMaxBody;
        Location sub;

};

void    parse(std::string str);

#endif