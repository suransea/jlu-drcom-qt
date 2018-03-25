#ifndef CONFIGUREREADER_H
#define CONFIGUREREADER_H
#include <string>
#include <iostream>
#include <fstream>
#include <map>

class ConfigureReader
{
    std::map<std::string,std::string>cfg;
    std::string fileName;
public:
    ConfigureReader(std::string fileName);
    std::map<std::string,std::string> getCfg();
    void setCfg(std::string key,std::string value);
    void fresh();
};

#endif // CONFIGUREREADER_H
