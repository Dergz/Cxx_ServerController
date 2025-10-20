#include "../Header.hxx"
#include <fstream>


// Takes in a file and returns them as "thing1" = "thing2"
std::unordered_map<std::string, std::string> loadKeyValues(const std::string &filename) {
    std::unordered_map<std::string, std::string> map;
    std::ifstream file(filename);
    if (!file.is_open()) return map;
    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        map[key] = value;
    }
    return map;
}

// Zero idea, check if that thing is the sammee?
bool saveKeyValues(const std::string &filename, const std::unordered_map<std::string, std::string> &map) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;  
    for (const auto &pair : map)
        file << pair.first << '=' << pair.second << '\n';
    return true;
}