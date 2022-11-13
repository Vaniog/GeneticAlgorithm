#pragma once
#include <iostream>
#include <map>

class ObjectsAttributes {
public:
    void ParseFromString(const std::string& parsing_string);
    void ParseFromFile(const std::string& file_name);
public:
    [[maybe_unused]] const std::string GetString(const std::string& key) const;
    [[maybe_unused]] uint32_t GetUint32(const std::string& key) const;
    [[maybe_unused]] float GetFloat(const std::string& key) const;
    [[maybe_unused]] uint32_t GetColor(const std::string& key) const;

    [[maybe_unused]] void SetString(const std::string& key, const std::string& x);
    [[maybe_unused]] void SetUint32(const std::string& key, const uint32_t& x);
    [[maybe_unused]] void SetFloat(const std::string& key, const float& x);
    [[maybe_unused]] void SetColor(const std::string& key, const std::string& x);
private:
    void SetVariable(const std::string& variable_name, const std::string& variable);

    static std::string GetStringFromString(const std::string& parsing_string, uint32_t& iter);
    static uint32_t GetColorFromString(const std::string& str);
    float GetFloatFromParent(const std::string& key) const;
    uint32_t GetUint32FromParent(const std::string& key) const;
private:
    std::map<std::string, std::string> data;
};