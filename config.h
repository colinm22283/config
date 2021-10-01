#include <string>
#include <fstream>
#include <map>
#include <regex>

#define CONFIG_MAJOR_VERSION 1
#define CONFIG_MINOR_VERSION 1

union cfgVal
{
    bool b;
    int i;
    float f;
};

class Config
{
public:
    Config();
    Config(std::fstream* _file);
    ~Config();

    static Config loadFile(std::string path);

    void set(std::string key, bool value);
    void set(std::string key, int value);
    void set(std::string key, float value);
    cfgVal get(std::string key);
private:
    std::fstream* file;
    std::map<std::string, cfgVal> map;
};

inline Config::Config()
{
    file = NULL;
}
inline Config::Config(std::fstream* _file)
{
    file = _file;

    std::string key;
    std::string value;
    while (!file->eof())
    {
        *file >> key >> value;

        std::cout << "Value: " << value << "\n";
        if (std::regex_match(value, std::regex("^(?:(?:true)|(?:false))$", std::regex_constants::icase)))
        {
            set(key, std::regex_match(value, std::regex("^true$", std::regex_constants::icase)));
        }
        if (std::regex_match(value, std::regex("^[0-9]*\\.[0-9]*$")))
        {
            set(key, std::stof(value));
        }
        if (std::regex_match(value, std::regex("^[0-9]*$")))
        {
            set(key, std::stoi(value));
        }
    }
}

inline Config Config::loadFile(std::string path)
{
    std::fstream _file;
    _file.open(path);

    Config proto(&_file);

    return proto;
}

inline void Config::set(std::string key, bool value)
{
    cfgVal val;
    val.b = value;
    map[key] = val;
}
inline void Config::set(std::string key, int value)
{
    cfgVal val;
    val.i = value;
    map[key] = val;
}
inline void Config::set(std::string key, float value)
{
    cfgVal val;
    val.f = value;
    map[key] = val;
}

inline cfgVal Config::get(std::string key)
{
    return map[key];
}