#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "../../GraphicsManager/include/Object.h"

class ButtonBest : public Object {
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
    float char_size; // in pixels
    float out_thick; // in pixels
    sf::Font* font;
public:
    explicit ButtonBest(const std::string& parse_str);

    void CorrectSize() const;

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow& window) override;
    virtual void OnPress() {};
};