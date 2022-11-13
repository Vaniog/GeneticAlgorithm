#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "../../GraphicsManager/include/Object.h"
#include "../../GraphicsManager/include/SpaceManager.h"
#include "../../GraphicsManager/include/Space.h"

class Button : public Object {
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

    float size_scale = 1; // for sprite
    float scale = 1;

    bool image_defined = false;
    sf::Texture* texture;
    sf::Sprite* sprite;

    sf::RectangleShape* rectangle;

    bool text_defined = false;
    sf::Text* text;
    float char_size; // in pixels
    uint32_t lines_in_text{};
    float out_thick; // in pixels
    sf::Font* font;
public:
    explicit Button(const std::string& parse_str);

    void CorrectSize() const;

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow& window) override;
    virtual void OnPress() {};
};

class ExitButton : public Button {
public:
    Space& space;
    explicit ExitButton(const std::string& parse_str, Space& space);

    void OnPress() override;
};

class MenuButton : public Button {
    SpaceManager& space_manager;

public:
    explicit MenuButton(const std::string& parse_str, SpaceManager& space_manager);

    void OnPress() override;
};

class StartButton : public Button {
    SpaceManager& space_manager;

public:
    explicit StartButton(const std::string& parse_str, SpaceManager& space_manager);

    void OnPress() override;
};