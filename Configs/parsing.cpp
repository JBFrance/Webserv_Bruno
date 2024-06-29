#include "parsing.hpp"

void    parse(std::string str)
{
    //std::array<servData> arr;
    std::ifstream file;
    file.open(str);
    if (!file.is_open())
        throw("Error: file does not exist");
    std::string line;
    while(getline(file, line)) //pseudo below
    {

        // if (line != "Server")
        //     if (line != "\n")
        //         throw (error)
        // else
        // {
        //     while (getline(file, line) != "}")
        //         if (line == "Listen")
        //             arr[i]._ip = line;
        //         if (line == "port")
        //             arr[i]._port = line;
        //         if (line == "root")
        //             arr[i]._root = line;
        //         if (line == "index")
        //             arr[i]._index = line;
        // }

        
        //ignore newlines
        //check for SERVER keyword and no other line data
        //when SERVER, add new servData struct to array


            //check for listen, store in class
            //check for server_name, store in class
            //check for root, store in class
            //same for root, index
            //when finding location/cgi/    store in sub struct
        
        //continue looping until file end, 
        //ignore newlines
        //if new server keyword, perform steps above again (sub loop?)
    }
}