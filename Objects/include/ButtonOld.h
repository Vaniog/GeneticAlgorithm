#pragma once
#include "../../GraphicsManager/include/Object.h"

#include "../../SpaceManager.h"

class ButtonOld : public Object {
    sf::Vector2<float> pos;
    sf::Vector2<float> size;
    float scale = 1;
    std::string image_name;
    sf::Sprite sprite;
    sf::Image image;
    sf::Texture texture;
public:
    ButtonOld(float pos_x_percents, float pos_y_percents,
              float size_x_percents,
              const std::string& image_name);

    void CorrectSize();

    void OnFrame() override;

    void OnDraw(sf::RenderWindow& window) override;

    bool was_pressed = false;
    void OnEvent(sf::Event& event, sf::RenderWindow &window) override;

    virtual void OnPress() {};
};

class ExitButtonOld : public ButtonOld {
    static const std::string IMAGE_PATH;
public:
    Space* space;

    ExitButtonOld(float pos_x_percents, float pos_y_percents,
                  float size_x_percents, Space& space);

    void OnPress() override;
};

class MenuButtonOld : public ButtonOld {
    static const std::string IMAGE_PATH;
public:
    SpaceManager* space_manager;

    MenuButtonOld(float pos_x_percents, float pos_y_percents,
                  float size_x_percents, SpaceManager& space_manager);

    void OnPress() override;
};

class StartButtonOld : public ButtonOld {
    static const std::string IMAGE_PATH;
public:
    SpaceManager* space_manager;

    StartButtonOld(float pos_x_percents, float pos_y_percents,
                   float size_x_percents, SpaceManager& space_manager);

    void OnPress() override;
};
