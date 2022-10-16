#include "../include/Object.h"

const unsigned int Object::window_width = sf::VideoMode::getDesktopMode().width;
const unsigned int Object::window_height = sf::VideoMode::getDesktopMode().height;

void Object::Timer() {
    auto cur = std::chrono::steady_clock::now();
    auto diff = cur - old;
    delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    old = cur;
}