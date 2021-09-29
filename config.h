#include <string>
#include <fstream>
#include <map>

class Config
{
public:
    Config(std::fstream* _file);

    static Config loadFile(std::string path);

    void* operator [] (std::string key);
private:
    std::fstream* file;
    std::map<std::string, int> intMap;
    std::map<std::string, std::string> stringMap;
};

#ifndef JSON_FUNCTIONS_DEFINED
#define JSON_FUNCTIONS_DEFINED

Config::Config(std::fstream* _file)
{
    file = _file;

    intMap["test"] = 4;
}

Config Config::loadFile(std::string path)
{
    std::fstream _file;
    _file.open(path);

    Config proto(&_file);

    return proto;
}

void* Config::operator [] (std::string key)
{
    return (void*)(&intMap[key]);
}

#endif