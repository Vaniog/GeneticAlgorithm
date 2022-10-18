#ifndef GENETICALGORITHM_OBJECTS_BUTTON_H_
#define GENETICALGORITHM_OBJECTS_BUTTON_H_
#include "../../GraphicsManager/include/Object.h"

#include "../../SpaceManager.h"

class Button : public Object {
    sf::Vector2<float> pos;
    sf::Vector2<float> size;
    float scale = 1;
    std::string image_name;
    sf::Sprite sprite;
    sf::Image image;
    sf::Texture texture;
public:
    Button(float pos_x_percents, float pos_y_percents,
           float size_x_percents,
           const std::string& image_name);

    void CorrectSize();

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow &window) override;

    virtual void OnPress() {};
};

class ExitButton : public Button {
    static const std::string IMAGE_PATH;
public:
    Space* space;

    ExitButton(float pos_x_percents, float pos_y_percents,
               float size_x_percents, Space& space);

    void OnPress() override;
};

class MenuButton : public Button {
    static const std::string IMAGE_PATH;
public:
    SpaceManager* space_manager;

    MenuButton(float pos_x_percents, float pos_y_percents,
               float size_x_percents, SpaceManager& space_manager);

    void OnPress() override;
};

class StartButton : public Button {
    static const std::string IMAGE_PATH;
public:
    SpaceManager* space_manager;

    StartButton(float pos_x_percents, float pos_y_percents,
                float size_x_percents, SpaceManager& space_manager);

    void OnPress() override;
};

#endif //GENETICALGORITHM_OBJECTS_BUTTON_H_
