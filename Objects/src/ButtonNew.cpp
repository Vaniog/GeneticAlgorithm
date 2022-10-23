#include "../include/ButtonNew.h"
#include <fstream>

void ButtonData::ParseFromString(const std::string& parsing_string) {
    std::string variable_name;
    uint32_t iter = 0;
    while (iter < parsing_string.size()) {
        variable_name = GetStringFromString(parsing_string, iter);
        std::string variable = GetStringFromString(parsing_string, iter);
        SetVariable(variable_name, variable);
    }
    if (!data_file_path.empty()) {
        ParseFromFile(data_file_path);
    }
}

void ButtonData::ParseFromFile(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string variable_name;
    std::string variable;
    while (file >> variable_name) {
        file >> variable;
        SetVariable(variable_name, variable);
    }
}

void ButtonData::SetVariable(const std::string& variable_name, const std::string& variable) {
    if (variable_name == "data_file_path") {
        data_file_path = variable;
    } else if (variable_name == "width-%") {
        width_in_percents = std::stof(variable);
    } else if (variable_name == "height-%") {
        height_in_percents = std::stof(variable);
    } else if (variable_name == "width-p") {
        width_in_pixels = std::stof(variable);
    } else if (variable_name == "height-p") {
        height_in_pixels = std::stof(variable);
    } else if (variable_name == "pos_x-%") {
        pos_x_in_percents = std::stof(variable);
    } else if (variable_name == "pos_y-%") {
        pos_y_in_percents = std::stof(variable);
    } else if (variable_name == "pos_x-p") {
        pos_x_in_pixels = std::stof(variable);
    } else if (variable_name == "pos_y-p") {
        pos_y_in_pixels = std::stof(variable);
    } else if (variable_name == "text") {
        text = variable;
    } else if (variable_name == "text_color") {
        text_color = GetColorFromString(variable);
    } else if (variable_name == "font_path") {
        font_path = variable;
    } else if (variable_name == "char_size-%") {
        character_size_in_percents = std::stof(variable);
    } else if (variable_name == "char_size-p") {
        character_size_in_pixels = std::stof(variable);
    } else if (variable_name == "color") {
        fill_color = GetColorFromString(variable);
    } else if (variable_name == "out_color") {
        outline_color = GetColorFromString(variable);
    } else if (variable_name == "out_thickness-%") {
        outline_thickness_in_percents = std::stof(variable);
    } else if (variable_name == "out_thickness-p") {
        outline_thickness_in_pixels = std::stof(variable);
    } else if (variable_name == "image_path") {
        image_path = variable;
    }
}

bool IsSkipChar(const char& c) {
    return c == ' ' || c == '\n' || c == '=' || c == ':' || c == ';';
}

uint32_t ButtonData::GetColorFromString(const std::string& str) {
    if (str[0] == '0') {
        if (str.size() == 8) // if alpha not set
            return static_cast<uint32_t>(std::stold(str + "FF"));
        return static_cast<uint32_t>(std::stold(str));
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
    }
    return 0xFFFFFFFF;
}

std::string ButtonData::GetStringFromString(const std::string& parsing_string, uint32_t& iter) {
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

NewButton::NewButton(
        const std::string& data_string) {
    data.ParseFromString(data_string);

    if (data.width_in_pixels != 0) {
        width = static_cast<float>(data.width_in_pixels);
        height = static_cast<float>(data.height_in_pixels);
    } else {
        width = static_cast<float>(window_width) * data.width_in_percents;
        height = static_cast<float >(window_height) * data.height_in_percents;
    }

    if (data.pos_x_in_pixels != 0) {
        pos_x = static_cast<float>(data.pos_x_in_pixels);
        pos_y = static_cast<float>(data.pos_y_in_pixels);
    } else {
        pos_x = static_cast<float>(window_width) * data.pos_x_in_percents;
        pos_y = static_cast<float>(window_height) * data.pos_y_in_percents;
    }

    if (data.outline_thickness_in_percents != 0) {
        data.outline_thickness_in_pixels = static_cast<float>(window_width) * data.outline_thickness_in_percents;
    }

    if (data.character_size_in_percents != 0) {
        data.character_size_in_pixels = static_cast<float>(window_width) * data.character_size_in_percents;
    }

    if (!data.image_path.empty()) {
        sprite = new sf::Sprite;
        texture = new sf::Texture;
        image_defined = true;
        texture->loadFromFile(data.image_path);
        float image_width = static_cast<float>(texture->getSize().x);
        float image_height = static_cast<float>(texture->getSize().y);
        size_scale = width / image_width;
        height = width * image_height / image_width;
        sprite->setTexture(*texture);
    } else {
        rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
        rectangle->setOutlineColor(sf::Color(data.outline_color));
        rectangle->setFillColor(sf::Color(data.fill_color));
        rectangle->setOutlineThickness(data.outline_thickness_in_pixels);
    }

    if (!data.font_path.empty()) {
        text = new sf::Text;
        font = new sf::Font;
        text_defined = true;
        font->loadFromFile(data.font_path);
        text->setString(data.text);
        text->setFont(*font);
        text->setFillColor(sf::Color(data.text_color));
        text->setCharacterSize(static_cast<uint32_t>(data.character_size_in_pixels));
        //width = text->getGlobalBounds().width;
        //height = text->getGlobalBounds().height;
        //rectangle->setSize(sf::Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height));
    }

    CorrectSize();
}

void NewButton::CorrectSize() const {
    if (image_defined) {
        sprite->setPosition(pos_x - width * scale / 2, pos_y - height * scale / 2);
        sprite->setScale(size_scale * scale, size_scale * scale);
    } else {
        rectangle->setPosition(pos_x - width * scale / 2, pos_y - height * scale / 2);
        rectangle->setScale(scale, scale);
    }
    if (text_defined) {
        text->setPosition(pos_x - text->getLocalBounds().width * scale / 2,
                          pos_y - text->getLocalBounds().height * scale / 2);
        text->setScale(scale, scale);
    }
}

void NewButton::OnFrame() {
    CorrectSize();
}

void NewButton::OnDraw(sf::RenderWindow& window) {
    if (image_defined) {
        window.draw(*sprite);
    } else {
        window.draw(*rectangle);
    }

    if (text_defined) {
        window.draw(*text);
    }
}

void NewButton::OnEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2<float> mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (mouse.x >= pos_x - width / 2 && mouse.x <= pos_x + width / 2
                && mouse.y >= pos_y - height / 2 && mouse.y <= pos_y + height / 2) {
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