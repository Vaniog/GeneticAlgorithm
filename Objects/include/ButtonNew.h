#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "../../GraphicsManager/include/Object.h"

struct ButtonData {
    std::string data_file_path; // data_file_path

    float width_in_percents = 0; // width-%
    float height_in_percents = 0; // height-%
    uint32_t width_in_pixels = 0; // width-p
    uint32_t height_in_pixels = 0; // height-p

    float pos_x_in_percents = 0; // pos_x-%
    float pos_y_in_percents = 0; // pos_y-%
    uint32_t pos_x_in_pixels = 0; // pos_x-p
    uint32_t pos_y_in_pixels = 0; // pos_y-p

    std::string text; // text
    std::string text_color; // text_color

    std::string image_path; // image_path

    void ParseFromString(const std::string& parsing_string);
    void ParseFromFile(const std::string& file_name);

    void SetVariable(const std::string& variable_name, const std::string& variable);

    static std::string GetStringFromString(const std::string& parsing_string, uint32_t& iter);
    static float StringToFloat(const std::string& str);
};

struct NewButton : public Object {
    ButtonData data;

    float width; // in pixels
    float height; // in pixels

    float pos_x; // in pixels
    float pos_y; // in pixels

    float size_scale = 1;
    float scale = 1;

    bool image_defined;
    sf::Texture texture;
    sf::Sprite sprite;

    explicit NewButton(const std::string& data_string);

    void CorrectSize();

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow& window) override;

    virtual void OnPress() {};
};