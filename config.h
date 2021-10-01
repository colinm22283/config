#include <string>
#include <fstream>
#include <map>
#include <regex>

#define CONFIG_MAJOR_VERSION 1
#define CONFIG_MINOR_VERSION 1

enum cfgType { BOOL, INT, FLOAT };
union cfgVal { bool b; int i; float f; };
struct cfgStruct { cfgVal v; cfgType type; };

class Config
{
public:
    Config();
    Config(std::string path);

    void writeFile(std::string path);

    void set(std::string key, bool value);
    void set(std::string key, int value);
    void set(std::string key, float value);
    cfgVal get(std::string key);
    cfgType getType(std::string key);
private:
    std::map<std::string, cfgStruct> map;
};

inline Config::Config() { };

inline Config::Config(std::string path)
{
    std::ifstream file;
    file.open(path);

    std::string key;
    std::string value;
    while (!file.eof())
    {
        file >> key >> value;

        if (std::regex_match(value, std::regex("^(?:(?:true)|(?:false))$", std::regex_constants::icase)))
        { set(key, std::regex_match(value, std::regex("^true$", std::regex_constants::icase))); }
        if (std::regex_match(value, std::regex("^[0-9]*\\.[0-9]*$")))
        { set(key, std::stof(value)); }
        if (std::regex_match(value, std::regex("^[0-9]*$")))
        { set(key, std::stoi(value)); }
    }
}

inline void Config::writeFile(std::string path)
{
    std::ofstream file;
    file.open(path);

    for(std::map<std::string, cfgStruct>::iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        std::string k = iter->first;

        file << k << "          ";

        switch (map[k].type)
        {
        case BOOL:
            file << map[k].v.b ? "True" : "False";
            break;
        case INT:
            file << std::to_string(map[k].v.i);
            break;
        case FLOAT:
            file << std::to_string(map[k].v.f);
            break;
        }

        file << "\n";
    }
}

inline void Config::set(std::string key, bool value)
{
    cfgStruct val;
    val.type = cfgType::BOOL;
    val.v.b = value;
    map[key] = val;
}
inline void Config::set(std::string key, int value)
{
    cfgStruct val;
    val.type = cfgType::INT;
    val.v.i = value;
    map[key] = val;
}
inline void Config::set(std::string key, float value)
{
    cfgStruct val;
    val.type = cfgType::FLOAT;
    val.v.f = value;
    map[key] = val;
}

inline cfgVal Config::get(std::string key)
{
    return map[key].v;
}

inline cfgType Config::getType(std::string key)
{
    return map[key].type;
}