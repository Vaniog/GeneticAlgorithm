#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "../../GraphicsManager/include/Object.h"

struct ButtonDataOld {
    std::string data_file_path; // data_file_path

    float width_in_percents = 0; // width-%
    float height_in_percents = 0; // height-%
    float width_in_pixels = 0; // width-p
    float height_in_pixels = 0; // height-p

    float pos_x_in_percents = 0; // pos_x-%
    float pos_y_in_percents = 0; // pos_y-%
    float pos_x_in_pixels = 0; // pos_x-p
    float pos_y_in_pixels = 0; // pos_y-p

    std::string text; // text
    std::string font_path;
    uint32_t text_color = 0xFFFFFFFF; // text_color
    float character_size_in_percents = 0; // char_size-%
    float character_size_in_pixels = 0; // char_size-p

    uint32_t fill_color = 0xFFFFFFFF; // color
    float outline_thickness_in_percents = 0; // out_thickness-%
    float outline_thickness_in_pixels = 0; // out_thickness-p
    uint32_t outline_color = 0xFFFFFFFF; // out_color

    std::string image_path; // image_path

    void ParseFromString(const std::string& parsing_string);
    void ParseFromFile(const std::string& file_name);

    void SetVariable(const std::string& variable_name, const std::string& variable);

    static std::string GetStringFromString(const std::string& parsing_string, uint32_t& iter);
    static uint32_t GetColorFromString(const std::string& str);
};

struct NewButton : public Object {
    ButtonDataOld data;

    float width; // in pixels
    float height; // in pixels
    float rect_width; // in pixels
    float rect_height; // in pixels

    float pos_x; // in pixels
    float pos_y; // in pixels

    float size_scale = 1; // for sprite
    float scale = 1;

    bool image_defined = false;
    sf::Texture* texture;
    sf::Sprite* sprite;

    sf::RectangleShape* rectangle;

    bool text_defined = false;
    sf::Text* text;
    sf::Font* font;

    explicit NewButton(const std::string& data_string);

    void CorrectSize() const;

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow& window) override;

    virtual void OnPress() {};
};