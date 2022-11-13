#include "../include/Button.h"

Button::Button(const std::string& parse_str) : Object(parse_str) {
    char_size = attrs->GetFloat("char_size");
    out_thick = attrs->GetFloat("out_thick");

    if (!attrs->GetString("image_path").empty()) {
        sprite = new sf::Sprite;
        texture = new sf::Texture;
        image_defined = true;
        texture->loadFromFile(attrs->GetString("image_path"));
        float image_width = static_cast<float>(texture->getSize().x);
        float image_height = static_cast<float>(texture->getSize().y);
        size_scale = size.x / image_width;
        size.y = size.x * image_height / image_width;
        sprite->setTexture(*texture);
    } else {
        rectangle = new sf::RectangleShape(sf::Vector2f(size.x - 2 * out_thick, size.y - 2 * out_thick));
        rectangle->setOutlineColor(sf::Color(attrs->GetColor("out_color")));
        rectangle->setFillColor(sf::Color(attrs->GetColor("fill_color")));
        rectangle->setOutlineThickness(out_thick);
        rectangle->setOrigin(-out_thick, -out_thick);
    }

    if (!attrs->GetString("font_path").empty()) {
        text = new sf::Text;
        font = new sf::Font;
        text_defined = true;
        font->loadFromFile(attrs->GetString("font_path"));
        text->setString(attrs->GetString("text_string"));
        text->setFont(*font);
        text->setFillColor(sf::Color(attrs->GetColor("text_color")));
        text->setCharacterSize(static_cast<uint32_t>(char_size));
        lines_in_text = 1;
        for (uint32_t c : text->getString()) {
            lines_in_text += (c == '\n');
        }
        //size_of_tile.x = text->getGlobalBounds().width;
        //size_of_tile.y = text->getGlobalBounds().height;
        //rectangle->setSize(sf::Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height));
    }

    CorrectSize();
}

void Button::CorrectSize() const {
    if (image_defined) {
        sprite->setScale(size_scale * scale, size_scale * scale);
        sprite->setPosition(pos.x - size.x * scale / 2, pos.y - size.y * scale / 2);
    } else {
        rectangle->setScale(scale, scale);
        rectangle->setPosition(pos.x - size.x * scale / 2,
                               pos.y - size.y * scale / 2);
    }
    if (text_defined) {
        text->setScale(scale, scale);
        float padding_y = static_cast<float>(lines_in_text) * char_size * scale - text->getGlobalBounds().height;
        text->setPosition(pos.x - text->getGlobalBounds().width / 2,
                          pos.y - text->getGlobalBounds().height / 2 - padding_y);
    }
}

void Button::OnFrame() {
    CorrectSize();
}

void Button::OnDraw(sf::RenderWindow& window) {
    if (image_defined) {
        window.draw(*sprite);
    } else {
        window.draw(*rectangle);
    }

    if (text_defined) {
        window.draw(*text);
    }
}

void Button::OnEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2<float> mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (mouse.x >= pos.x - size.x / 2
                && mouse.x <= pos.x + size.x / 2
                && mouse.y >= pos.y - size.y / 2
                && mouse.y <= pos.y + size.y / 2) {
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

ExitButton::ExitButton(const std::string& parse_str, Space& space) : Button(parse_str), space(space) {}

void ExitButton::OnPress() {
    space.Stop();
}

MenuButton::MenuButton(const std::string& parse_str, SpaceManager& space_manager)
        : Button(parse_str), space_manager(space_manager) {}
void MenuButton::OnPress() {
    Space::GetInstance().FillByTag("MENU");
}

StartButton::StartButton(const std::string& parse_str, SpaceManager& space_manager)
        : Button(parse_str), space_manager(space_manager) {}
void StartButton::OnPress() {
    Space::GetInstance().FillByTag("PLAY");
}