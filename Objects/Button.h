#ifndef GENETICALGORITHM_OBJECTS_BUTTON_H_
#define GENETICALGORITHM_OBJECTS_BUTTON_H_
#include "../GraphicsManager/Object.h"

#include "../SpaceManager.h"

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
           const std::string& image_name) {
        image.loadFromFile(image_name);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        pos.x = pos_x_percents * (float)window_width;
        pos.y = pos_y_percents * (float)window_height;
        size.x = size_x_percents * (float)window_width;
        size.y = size.x * (float)image.getSize().y / (float)image.getSize().x;
        CorrectSize();
    }

    void CorrectSize() {
        float size_scale = size.x / (float)image.getSize().x;
        sprite.setPosition(pos.x - size.x / 2 * scale, pos.y - size.y / 2 * scale);
        sprite.setScale(scale * size_scale, scale * size_scale);
    }

    void OnFrame() override {
        CorrectSize();
    }

    void OnDraw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    bool was_pressed = false;
    void OnEvent(sf::Event& event) override {
        if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2<int> mouse = sf::Mouse::getPosition();
            if (mouse.x >= pos.x - size.x / 2 && mouse.x <= pos.x + size.x / 2
                    && mouse.y >= pos.y - size.y / 2 && mouse.y <= pos.y + size.y / 2) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    scale = 0.85;
                    was_pressed = true;
                    return;
                } else {
                    scale = 0.95;
                }
            } else {
                scale = 1;
            }
            was_pressed = false;
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (was_pressed) {
                OnPress();
                scale = 0.95;
            }
        }
    }
    virtual void OnPress() {

    }
};

class ExitButton : public Button {
    static const std::string IMAGE_PATH;
public:
    Space* space;
    explicit ExitButton(Space& space) : Button(0.05, 0.05, 0.07, IMAGE_PATH) {
        this->space = &space;
    }
    void OnPress() override {
        space->Stop();
    }
};

class MenuButton : public Button {
    static const std::string IMAGE_PATH;
public:
    SpaceManager *space_manager;
    explicit MenuButton(SpaceManager &space_manager) : Button(0.03, 0.03, 0.05, IMAGE_PATH) {
        this->space_manager = &space_manager;
    }
    void OnPress() override {
        space_manager->FillByTag(SpaceManager::Mode::MENU);
    }
};

class StartButton : public Button {
    static const std::string IMAGE_PATH;
public:
    SpaceManager *space_manager;
    explicit StartButton(SpaceManager &space_manager) : Button(0.5, 0.5, 0.3, IMAGE_PATH) {
        this->space_manager = &space_manager;
    }
    void OnPress() override {
        space_manager->FillByTag(SpaceManager::Mode::PLAY);
    }
};

#endif //GENETICALGORITHM_OBJECTS_BUTTON_H_
