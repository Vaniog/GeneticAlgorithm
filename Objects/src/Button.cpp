#include "../include/Button.h"

Button::Button(const std::string& parse_str) {
    attrs = new ObjectsAttributes;
    attrs->hundred_percents_value = static_cast<float>(window_width);
    attrs->ParseFromString(parse_str);

    width = attrs->GetFloat("width");
    height = attrs->GetFloat("height");

    pos_x = attrs->GetFloat("pos_x");
    pos_y = attrs->GetFloat("pos_y");

    char_size = attrs->GetFloat("char_size");
    out_thick = attrs->GetFloat("out_thick");

    if (!attrs->GetString("image_path").empty()) {
        sprite = new sf::Sprite;
        texture = new sf::Texture;
        image_defined = true;
        texture->loadFromFile(attrs->GetString("image_path"));
        float image_width = static_cast<float>(texture->getSize().x);
        float image_height = static_cast<float>(texture->getSize().y);
        size_scale = width / image_width;
        height = width * image_height / image_width;
        sprite->setTexture(*texture);
    } else {
        rectangle = new sf::RectangleShape(sf::Vector2f(width - 2 * out_thick, height - 2 * out_thick));
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
        //width = text->getGlobalBounds().width;
        //height = text->getGlobalBounds().height;
        //rectangle->setSize(sf::Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height));
    }

    CorrectSize();
}

void Button::CorrectSize() const {
    if (image_defined) {
        sprite->setScale(size_scale * scale, size_scale * scale);
        sprite->setPosition(pos_x - width * scale / 2, pos_y - height * scale / 2);
    } else {
        rectangle->setScale(scale, scale);
        rectangle->setPosition(pos_x - width * scale / 2,
                               pos_y - height * scale / 2);
    }
    if (text_defined) {
        text->setScale(scale, scale);
        float padding_y = char_size * scale - text->getGlobalBounds().height;
        text->setPosition(pos_x - text->getGlobalBounds().width / 2,
                          pos_y - text->getGlobalBounds().height / 2 - padding_y);
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
        if (mouse.x >= pos_x - width / 2
                && mouse.x <= pos_x + width / 2
                && mouse.y >= pos_y - height / 2
                && mouse.y <= pos_y + height / 2) {
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

ExitButton::ExitButton(const std::string& parse_str, Space& space) : Button(parse_str), space(space) {};

void ExitButton::OnPress() {
    space.Stop();
}

MenuButton::MenuButton(const std::string& parse_str, SpaceManager& space_manager)
        : Button(parse_str), space_manager(space_manager) {}
void MenuButton::OnPress() {
    space_manager.FillByTag(SpaceManager::Mode::MENU);
}

StartButton::StartButton(const std::string& parse_str, SpaceManager& space_manager)
        : Button(parse_str), space_manager(space_manager) {}
void StartButton::OnPress() {
    space_manager.FillByTag(SpaceManager::Mode::PLAY);
}