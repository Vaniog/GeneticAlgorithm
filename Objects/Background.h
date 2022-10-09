#ifndef GENETICALGORITHM_OBJECTS_BACKGROUND_H_
#define GENETICALGORITHM_OBJECTS_BACKGROUND_H_

#include "../GraphicsManager/Object.h"
#include <cmath>

class Background : public Object {
    const int amount_x = 40;
    const int amount_y = 20;
    std::vector<sf::RectangleShape> field;
public:
    Background();

    long time_pass = 0;
    int step = 0;

    void OnFrame() override;

    void Refill(); // new colors

    void OnDraw(sf::RenderWindow& window) override;
};

#endif //GENETICALGORITHM_OBJECTS_BACKGROUND_H_
