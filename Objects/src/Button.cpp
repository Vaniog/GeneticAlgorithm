#include "../include/Button.h"
#include <iostream>

Button::Button(float pos_x_percents, float pos_y_percents, float size_x_percents, const std::string& image_name) {
    image.loadFromFile(image_name);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    pos.x = pos_x_percents * (float)window_width;
    pos.y = pos_y_percents * (float)window_height;
    size.x = size_x_percents * (float)window_width;
    size.y = size.x * (float)image.getSize().y / (float)image.getSize().x;
    CorrectSize();
}

void Button::CorrectSize() {
    float size_scale = size.x / (float)image.getSize().x;
    sprite.setPosition(pos.x - size.x / 2 * scale, pos.y - size.y / 2 * scale);
    sprite.setScale(scale * size_scale, scale * size_scale);
}

void Button::OnFrame() {
    CorrectSize();
}

void Button::OnDraw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Button::OnEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2<int> mouse = sf::Mouse::getPosition();
        std::cout << mouse.x << ":" << mouse.y << " in (" << window_width << "x" << window_height << ")\n";
        if (mouse.x >= pos.x - size.x / 2 && mouse.x <= pos.x + size.x / 2
                && mouse.y >= pos.y - size.y / 2 && mouse.y <= pos.y + size.y / 2) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                scale = 0.85;
                was_pressed = true;
                return;
            } else {
                scale = 0.95;
            }
        } else {
            scale = 1;
        }
        was_pressed = false;
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (was_pressed) {
            OnPress();
            scale = 0.95;
        }
    }
}

ExitButton::ExitButton(float pos_x_percents, float pos_y_percents, float size_x_percents, Space& space)
        : Button(pos_x_percents,
                 pos_y_percents,
                 size_x_percents,
                 IMAGE_PATH) {
    this->space = &space;
}

void ExitButton::OnPress() {
    space->Stop();
}

MenuButton::MenuButton(float pos_x_percents, float pos_y_percents, float size_x_percents, SpaceManager& space_manager)
        : Button(pos_x_percents,
                 pos_y_percents,
                 size_x_percents,
                 IMAGE_PATH) {
    this->space_manager = &space_manager;
}

void MenuButton::OnPress() {
    space_manager->FillByTag(SpaceManager::Mode::MENU);
}

StartButton::StartButton(float pos_x_percents, float pos_y_percents, float size_x_percents, SpaceManager& space_manager)
        : Button(pos_x_percents,
                 pos_y_percents,
                 size_x_percents,
                 IMAGE_PATH) {
    this->space_manager = &space_manager;
}

void StartButton::OnPress() {
    space_manager->FillByTag(SpaceManager::Mode::PLAY);
}