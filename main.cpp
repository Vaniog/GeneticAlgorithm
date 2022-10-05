#include <iostream>
#include <cmath>
#include "GraphicsManager/Space.h"

class Circle : public Object {
    void OnDraw(sf::RenderWindow& window) override {
        sf::CircleShape circle_shape;
        circle_shape.setRadius(150);
        circle_shape.setPosition(window_width / 2 + 200 * cos((double)time / 10000),
                                 window_height / 2 + 200 * sin((double)time / 10000));
        window.draw(circle_shape);
    }
};

int main() {
    Space space;
    space << new Circle;
    space.Start();
    evolution("a.txt","b.txt");
}
