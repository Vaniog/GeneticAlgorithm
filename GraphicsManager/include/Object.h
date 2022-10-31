#ifndef GENETICALGORITHM_GRAPHICS_OBJECT_H_
#define GENETICALGORITHM_GRAPHICS_OBJECT_H_
#include "SFML/Graphics.hpp"

#include <ctime>
#include <chrono>
#include "ObjectsAttributes.h"

class Object {
public:
    static const unsigned int window_width;
    static const unsigned int window_height;
public:
    ObjectsAttributes *attrs = new ObjectsAttributes();
    virtual void OnFrame() {}
    virtual void OnDraw(sf::RenderWindow& window) {}
    virtual void OnEvent(sf::Event& event, sf::RenderWindow& window) {}

    std::chrono::steady_clock::time_point old = std::chrono::steady_clock::now();
    long delta_time = 0;
    void Timer();

    virtual void SaveParams() {}
};

#endif //GENETICALGORITHM_GRAPHICS_OBJECT_H_