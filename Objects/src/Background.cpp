#include "../include/Background.h"
Background::Background() {
    field.resize(amount_x * amount_y);
    Refill();
}

void Background::OnFrame() {
    time_pass += delta_time;
    if (time_pass >= 100) {
        time_pass = 0;
        Refill();
        step++;
    }
}

void Background::Refill() {
    float size_x = (float)window_width / amount_x + 1;
    float size_y = (float)window_height / amount_y + 1;
    for (int x = 0; x < amount_x; x++) {
        for (int y = 0; y < amount_y; y++) {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(size_x, size_y));
            rect.setPosition(size_x * x, size_y * y);
            int num = 128 + 127 * cos(3.15 * 2 * (double)(x + y + step) / (amount_x + amount_y));
            sf::Color color((num + x * 3 - y * 2) % 255, (num + x * 10) % 255, (num - y * 5) % 255);
            rect.setFillColor(color);
            field[y * amount_x + x] = rect;
        }
    }
}

void ::Background::OnDraw(sf::RenderWindow& window) {
    for (auto& rect : field)
        window.draw(rect);
}