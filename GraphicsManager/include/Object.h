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
    const sf::Vector2f GetSize() const;
    const sf::Vector2f GetPos() const;
    const std::string GetID() const;
    void SetSize(sf::Vector2f new_size);
    void SetPos(sf::Vector2f new_pos);

private:
    friend class Space;
    static Object* default_object;
protected:
    std::string id;
    sf::Vector2f pos{};
    sf::Vector2f size{};
public:
    ObjectsAttributes* attrs = new ObjectsAttributes();
    explicit Object() = default;
    explicit Object(const std::string& parse_str);
    std::string parse_str;
    void RecountDefaults();
    virtual void OnFrame() {}
    virtual void OnDraw(sf::RenderWindow& window) {}
    virtual void OnEvent(sf::Event& event, sf::RenderWindow& window) {}

    std::chrono::steady_clock::time_point old = std::chrono::steady_clock::now();
    long delta_time = 0;
    void Timer();
};

#endif //GENETICALGORITHM_GRAPHICS_OBJECT_H_