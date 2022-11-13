#include "../include/ObjectsAttributes.h"
#include "../include/Space.h"
#include <fstream>

void ObjectsAttributes::ParseFromString(const std::string& parsing_string) {
    uint32_t iter = 0;

    while (iter < parsing_string.size()) {
        std::string variable_name = GetStringFromString(parsing_string, iter);
        std::string variable = GetStringFromString(parsing_string, iter);
        SetVariable(variable_name, variable);
    }
    if (!GetString("data_file_path").empty()) {
        ParseFromFile(GetString("data_file_path"));
    }

    for (auto member : data) {
        std::string variable_name = member.first;
        if (variable_name.find("parent_") != variable_name.npos) { // parent_size
            std::string parent_id = member.second;
            variable_name.erase(0, 7);
            Object* parent = Space::GetObjectById(parent_id);
            if (parent == nullptr)
                continue;
            for (auto attr : parent->attrs->data) {
                if (attr.first.find(variable_name) == 0) {
                    SetVariable("100%_" + attr.first, attr.second);
                }
            }
        }
    }

    for (auto member : data) {
        std::string variable_name = member.first;
        std::string variable = member.second;
        if (variable[variable.size() - 1] == '%') {
            if (data.find("100%_" + variable_name) == data.end()) {
                if (variable_name.find("_y") != variable_name.npos) {
                    SetVariable("100%_" + variable_name, data.find("100%_size_y")->second);
                } else {
                    SetVariable("100%_" + variable_name, data.find("100%_size_x")->second);
                }
            }
            float hundred_percents_value = std::stof(GetString("100%_" + variable_name));
            variable.erase(variable.size() - 1);
            variable = std::to_string(std::stof(variable) * hundred_percents_value / 100);
            SetVariable(variable_name, variable);
        }
    }

    for (auto member : data) {
        std::cout << member.first << " " << member.second << "\n";
    }
    std::cout << "==========\n";
}


void ObjectsAttributes::ParseFromFile(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string variable_name;
    std::string variable;
    while (file >> variable_name) {
        file >> variable;
        SetVariable(variable_name, variable);
    }
}

void ObjectsAttributes::SetVariable(const std::string& variable_name, const std::string& variable) {
    if (data.find(variable_name) == data.end()) {
        data.insert(std::make_pair(variable_name, variable));
    } else {
        data[variable_name] = variable;
    }
}

bool IsSkipChar(const char& c) {
    return c == ' ' || c == '\n' || c == '=' || c == ':' || c == ';';
}

uint32_t ObjectsAttributes::GetColorFromString(const std::string& str) {
    std::string str_copy = str;
    if (str[0] == '0' || str[0] == '#') {
        if (str[0] == '#') { // #fafafa -> 0xfafafa
            str_copy[0] = 'x';
            str_copy = '0' + str_copy;
        }
        if (str_copy.size() == 8) { // 0xfafafa -> 0xfafafaff (alpha canal added)
            str_copy += "FF";
        }
        return static_cast<uint32_t>(std::stoul(str_copy, nullptr, 16));
    }
    if (str == "white") {
        return 0xFFFFFFFF;
    } else if (str == "black") {
        return 0x000000FF;
    } else if (str == "red") {
        return 0xFF0000FF;
    } else if (str == "green") {
        return 0x00FF00FF;
    } else if (str == "blue") {
        return 0x0000FFFF;
    } else if (str == "yellow") {
        return 0xFFFF00FF;
    } else if (str == "magenta") {
        return 0xFF00FFFF;
    } else if (str == "cyan") {
        return 0x00FFFFFF;
    } else if (str == "transparent")
        return 0x00000000;
    return 0xFFFFFFFF;
}

std::string ObjectsAttributes::GetStringFromString(const std::string& parsing_string, uint32_t& iter) {
    std::string str;
    char c = parsing_string[iter];

    if (c == '\"' || c == '\'') {
        c = parsing_string[++iter];
        while (c != '\'' && c != '\"') {
            str += c;
            c = parsing_string[++iter];
        }
        c = parsing_string[++iter];
    } else {
        while (!IsSkipChar(c) && iter < parsing_string.size()) {
            str += c;
            c = parsing_string[++iter];
        }
    }

    while (IsSkipChar(c)) {
        c = parsing_string[++iter];
    }

    return str;
}

const std::string ObjectsAttributes::GetString(const std::string& key) const {
    if (data.find("100%_" + key) != data.end()) {
        return data.find("100%_" + key)->second;
    }
    if (data.find(key) != data.end()) {
        return data.find(key)->second;
    }
    return "";
}

[[maybe_unused]] uint32_t ObjectsAttributes::GetUint32(const std::string& key) {
    uint32_t x = 0;
    if (data.find(key) == data.end()) {
        return 0;
    }
    std::string str = data.find(key)->second;
    if (!str.empty()) {
        if (str[str.size() - 1] == '%') {
            float hundred_percents_value = std::stof(GetString("100%_" + key));
            str.erase(str.size() - 1);
            x = static_cast<uint32_t>(std::stof(str) * hundred_percents_value / 100);
            SetUint32(key, x);
        } else {
            x = std::stoi(str);
        }
    }
    return x;
}

float ObjectsAttributes::GetFloat(const std::string& key) {
    float x = 0;
    if (data.find(key) == data.end()) {
        return 0;
    }
    std::string str = data.find(key)->second;
    if (!str.empty()) {
        if (str[str.size() - 1] == '%') {
            float hundred_percents_value = std::stof(GetString("100%_" + key));
            str.erase(str.size() - 1);
            x = std::stof(str) * hundred_percents_value / 100;
            SetFloat(key, x);
        } else {
            x = std::stof(str);
        }
    }
    return x;
}

uint32_t ObjectsAttributes::GetColor(const std::string& key) {
    uint32_t color = GetColorFromString(GetString(key));
    return color;
}

void ObjectsAttributes::SetString(const std::string& key, const std::string& x) {
    data[key] = x;
}
[[maybe_unused]] void ObjectsAttributes::SetUint32(const std::string& key, const uint32_t& x) {
    data[key] = std::to_string(x);
}
[[maybe_unused]] void ObjectsAttributes::SetFloat(const std::string& key, const float& x) {
    data[key] = std::to_string(x);
}
[[maybe_unused]] void ObjectsAttributes::SetColor(const std::string& key, const std::string& x) {
    data[key] = x;
}