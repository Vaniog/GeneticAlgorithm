#include "../include/ButtonNew.h"
#include <cmath>

void ButtonData::ParseFromString(const std::string& parsing_string) {
    std::string variable_name;
    uint32_t iter = 0;
    while (iter != parsing_string.size()) {
        variable_name = GetStringFromString(parsing_string, iter);
        GetVariable(variable_name, parsing_string, iter);
    }
}

void ButtonData::GetVariable(const std::string& variable_name, const std::string& parsing_string, uint32_t& iter) {
    std::string variable = GetStringFromString(parsing_string, iter);
    if (variable_name == "data_file_path") {
        data_file_path = variable;
    } else if (variable_name == "width-%") {
        width_in_percents = StringToFloat(variable);
    } else if (variable_name == "height-%") {
        height_in_percents = StringToFloat(variable);
    } else if (variable_name == "width-p") {
        width_in_pixels = std::stoi(variable);
    } else if (variable_name == "height-p") {
        height_in_pixels = std::stoi(variable);
    } else if (variable_name == "pos_x-%") {
        pos_x_in_percents = StringToFloat(variable);
    } else if (variable_name == "pos_y-%") {
        pos_y_in_percents = StringToFloat(variable);
    } else if (variable_name == "pos_x-p") {
        pos_x_in_pixels = std::stoi(variable);
    } else if (variable_name == "pos_y-p") {
        pos_y_in_pixels = std::stoi(variable);
    } else if (variable_name == "text") {
        text = variable;
    } else if (variable_name == "text_color") {
        text_color = variable;
    } else if (variable_name == "image_path") {
        image_path = variable;
    }
}

std::string ButtonData::GetStringFromString(const std::string& parsing_string, uint32_t& iter) {
    std::string str;
    char c = parsing_string[iter];
    while (c != ' ' && c != '\n' && c != '=') {
        str += c;
        iter++;
        c = parsing_string[iter];
    }
    while (c == ' ' || c == '\n' || c == '=') {
        iter++;
        c = parsing_string[iter];
    }
    return str;
}

float ButtonData::StringToFloat(const std::string& str) {
    float ans = 0;
    uint32_t iter = 0;
    while (str[iter] != '.') {
        ans = ans * 10 + static_cast<float>(str[iter] - '0');
        iter++;
    }
    iter++;
    uint32_t digit_num = 1;
    while (iter < str.size()) {
        ans += static_cast<float>(str[iter] - '0') / static_cast<float>(pow(10, digit_num));
        iter++;
        digit_num++;
    }
    return ans;
}

NewButton::NewButton(const std::string& data_string) {
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

    if (!data.image_path.empty()) {
        image_defined = true;
        texture.loadFromFile(data.image_path);
        float image_width = static_cast<float>(texture.getSize().x);
        float image_height = static_cast<float>(texture.getSize().y);
        size_scale = height / image_height;
        width = height * image_width / image_height;
        sprite.setTexture(texture);
    }

    CorrectSize();
}

void NewButton::CorrectSize() {
    if (image_defined) {
        sprite.setPosition(pos_x - width * scale / 2, pos_y - height * scale / 2);
        sprite.setScale(size_scale * scale, size_scale * scale);
    }
}

void NewButton::OnFrame() {
    CorrectSize();
}

void NewButton::OnDraw(sf::RenderWindow& window) {
    window.draw(sprite);
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