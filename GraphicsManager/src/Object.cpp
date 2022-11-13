#include "../include/Object.h"

Object* Object::default_object = new Object("id:0");

void Object::Timer() {
    auto cur = std::chrono::steady_clock::now();
    auto diff = cur - old;
    delta_time = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(diff).count())
            / 1000;
    old = cur;
}

Object::Object(const std::string& parse_str) {
    this->parse_str = "parent_size:0 parent_pos:0 ";
    this->parse_str += parse_str;
    attrs->ParseFromString(this->parse_str);
    id = attrs->GetString("id");

    size.x = attrs->GetFloat("size_x");
    size.y = attrs->GetFloat("size_y");
    pos.x = attrs->GetFloat("pos_x");
    pos.y = attrs->GetFloat("pos_y");
}

[[maybe_unused]] const sf::Vector2f Object::GetSize() const {
    return size;
}

[[maybe_unused]] const sf::Vector2f Object::GetPos() const {
    return pos;
}

[[maybe_unused]] const std::string Object::GetID() const {
    return id;
}

[[maybe_unused]] void Object::SetSize(sf::Vector2f new_size) {
    attrs->SetFloat("size_x", new_size.x);
    attrs->SetFloat("size_y", new_size.y);
    size = new_size;
}

[[maybe_unused]] void Object::SetPos(sf::Vector2f new_pos) {
    attrs->SetFloat("pos_x", new_pos.x);
    attrs->SetFloat("pos_y", new_pos.y);
    pos = new_pos;
}
