#include "../include/ObjectsAttributes.h"
#include "../include/Space.h"
#include <fstream>

void ObjectsAttributes::ParseFromString(const std::string& parsing_string) {
    std::string variable_name;
    uint32_t iter = 0;
    while (iter < parsing_string.size()) {
        variable_name = GetStringFromString(parsing_string, iter);
        std::string variable = GetStringFromString(parsing_string, iter);
        SetVariable(variable_name, variable);
    }
    if (!GetString("data_file_path").empty()) {
        ParseFromFile(GetString("data_file_path"));
    }
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
    data.insert(std::make_pair(variable_name, variable));
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
    if (data.find(key) == data.end()) {
        return "";
    }
    return data.find(key)->second;
}

[[maybe_unused]] uint32_t ObjectsAttributes::GetUint32(const std::string& key) const {
    uint32_t x = 0;
    if (data.find(key) == data.end()) {
        return 0;
    }
    std::string str = data.find(key)->second;
    if (!str.empty()) {
        if (str[str.size() - 1] == '%') {
            float hundred_percents_value = GetUint32(key);
            str.erase(str.size() - 1);
            x = static_cast<uint32_t>(std::stof(str) * hundred_percents_value / 100);
        } else {
            x = std::stoi(str);
        }
    }
    return x;
}

float ObjectsAttributes::GetFloat(const std::string& key) const {
    float x = 0;
    if (data.find(key) == data.end()) {
        return 0;
    }
    std::string str = data.find(key)->second;
    if (!str.empty()) {
        if (str[str.size() - 1] == '%') {
            float hundred_percents_value = GetFloatFromParent(key);
            str.erase(str.size() - 1);
            x = std::stof(str) * hundred_percents_value / 100;
        } else {
            x = std::stof(str);
        }
    }
    return x;
}

uint32_t ObjectsAttributes::GetColor(const std::string& key) const {
    return GetColorFromString(GetString(key));
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

float ObjectsAttributes::GetFloatFromParent(const std::string& key) const {
    std::string parent_name = "parent_" + key;
    while (!parent_name.empty() && GetString(parent_name).empty()) { // example parent_pos_x -> parent_pos
        while (!parent_name.empty() && parent_name[parent_name.size() - 1] != '_') {
            parent_name.pop_back();
        }
        if (!parent_name.empty())
            parent_name.pop_back();
    }
    if (parent_name == "")
        if (key.find("_y") != key.npos) {
            return Space::GetObjectById("0")->attrs->GetFloat("size_y");
        } else {
            return Space::GetObjectById("0")->attrs->GetFloat("size_x");
        }
    else {
        return Space::GetObjectById(parent_name)->attrs->GetFloat(key);
    }
}

uint32_t ObjectsAttributes::GetUint32FromParent(const std::string& key) const {
    std::string parent_name = "parent_" + key;
    while (!parent_name.empty() && GetString(parent_name).empty()) { // example parent_pos_x -> parent_pos
        while (parent_name[parent_name.size() - 1] != '_') {
            parent_name.pop_back();
        }
        parent_name.pop_back();
    }
    if (parent_name == "") {
        if (key.find("_y") != key.npos) {
            return Space::GetObjectById("0")->attrs->GetUint32("size_y");
        } else {
            return Space::GetObjectById("0")->attrs->GetUint32("size_x");
        }
    } else {
        return Space::GetObjectById(parent_name)->attrs->GetUint32(key);
    }
}