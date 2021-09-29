#include <string>
#include <fstream>

class Config
{
public:
    Config(std::fstream* _file);

    static Config loadFile(std::string path);

    void* operator [] (std::string key);
private:
    std::fstream* file;
};

#ifndef JSON_FUNCTIONS_DEFINED
#define JSON_FUNCTIONS_DEFINED

Config::Config(std::fstream* _file)
{
    file = _file;
}

Config Config::loadFile(std::string path)
{
    std::fstream _file;
    _file.open(path);

    Config proto(&_file);
}

void* Config::operator [] (std::string key)
{

}

#endif