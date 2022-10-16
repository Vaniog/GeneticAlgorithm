#ifndef GENETICALGORITHM_GRAPHICS_SPACE_H_
#define GENETICALGORITHM_GRAPHICS_SPACE_H_
#include "Object.h"

#include <vector>

class Space {
    std::vector<Object*> objects;
    bool running = true;
    const unsigned int window_height = sf::VideoMode::getDesktopMode().height;
    const unsigned int window_width = sf::VideoMode::getDesktopMode().width;
public:
    Space() = default;
    ~Space();

    Space& operator<<(Object* object);
    void Start();
    void Stop();
    void Clear();
    void SaveParams();
private:

    void OnFrame();
    void OnDraw(sf::RenderWindow& window);
    void OnEvent(sf::Event& event, sf::RenderWindow &window);
};

#endif //GENETICALGORITHM_GRAPHICS_SPACE_H_