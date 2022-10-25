#pragma once
#include <iostream>
#include <map>

class ObjectsAttributes {
    /*
     * ButtonOld attrs:
     * data_file_path
     *
     * width
     * height
     * pos_x
     * pos_y
     *
     * text_string
     * text_color
     * font_path
     * char_size
     *
     * fill_color
     * out_thickness
     * out_color
     *
     * image_path
    */
public:
    void ParseFromString(const std::string& parsing_string);
    void ParseFromFile(const std::string& file_name);

private:
    void SetVariable(const std::string& variable_name, const std::string& variable);

    static std::string GetStringFromString(const std::string& parsing_string, uint32_t& iter);
    static uint32_t GetColorFromString(const std::string& str);

public:
    float hundred_percents_value; // to use, for example: width=50%

    const std::string& GetString(const std::string& key);
    uint32_t GetUint32(const std::string& key);
    float GetFloat(const std::string& key);
    uint32_t GetColor(const std::string& key);

    void SetString(const std::string& key, const std::string& x);
    void SetUint32(const std::string& key, const uint32_t& x);
    void SetFloat(const std::string& key, const float& x);
    void SetColor(const std::string& key, const std::string& x);

private:
    std::map<std::string, std::string> data;
};