#ifndef GENETICALGORITHM_OBJECTS_SCENEDRAFT_H_
#define GENETICALGORITHM_OBJECTS_SCENEDRAFT_H_
#include <iostream>
#include "../GraphicsManager/Object.h"

class SceneDraft : public Object {
    static const int IMAGE_SIZE;
    static const std::string FIELD_PATH;
    static const std::string WALL_PATH;
    static const std::string BEAST_PATH;
    static const std::string FOOD_PATH;
    static const std::string POISON_PATH;
    static const std::string FONT_PATH;
    static const int FONT_BORDER;

    const int width = 40;
    const int height = 20;
    std::vector<std::vector<int>> field;

    sf::Texture field_texture;
    sf::Texture wall_texture;
    sf::Texture beast_texture;
    sf::Texture food_texture;
    sf::Texture poison_texture;

    ~SceneDraft(){
    }
public:
    SceneDraft(float pos_x_percents, float pos_y_percents,
               float size_x_percents) {
        field.resize(width);
        for (int i = 0; i < width; i++) {
            field[i].resize(height);
        }
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                field[x][y] = rand() % 10;
            }
        }

        pos.x = pos_x_percents * (float)window_width;
        pos.y = pos_y_percents * (float)window_height;
        size = size_x_percents * (float)window_width / (float)width;
        font_border_size = size * (float)(FONT_BORDER) / (float)(IMAGE_SIZE);

        LoadTextures();
    }
private:
    void LoadTextures() {
        sf::Image buff_image;
        buff_image.loadFromFile(FIELD_PATH);
        field_texture.loadFromImage(buff_image);
        buff_image.loadFromFile(WALL_PATH);
        wall_texture.loadFromImage(buff_image);
        buff_image.loadFromFile(POISON_PATH);
        poison_texture.loadFromImage(buff_image);
        buff_image.loadFromFile(FOOD_PATH);
        food_texture.loadFromImage(buff_image);
        buff_image.loadFromFile(BEAST_PATH);
        beast_texture.loadFromImage(buff_image);
        font.loadFromFile(FONT_PATH);
        text.setFont(font);
        text.setCharacterSize(size - 2 * font_border_size);
        text.setFillColor(sf::Color::White);
    }

    long time_pass = 0;
    void OnFrame() override {
        time_pass += delta_time;
        if (time_pass < 1000)
            return;
        time_pass = 0;
    }

    sf::Vector2<float> pos;
    float size;
    float font_border_size;
    sf::Sprite rect;
    sf::Font font;
    sf::Text text;

    void PickPixel(const int &x, const int &y){
        rect.setPosition(pos.x + x * size, pos.y + y * size);
        text.setPosition(pos.x + x * size + font_border_size, pos.y + y * size + font_border_size);
    }

    void OnDraw(sf::RenderWindow& window) override {
        rect.setTexture(field_texture);
        rect.setScale(size / (float)IMAGE_SIZE, size / (float)IMAGE_SIZE);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PickPixel(x, y);
                window.draw(rect);
            }
        }

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PickPixel(x, y);
                if (field[x][y] <= 0) {
                    rect.setTexture(beast_texture);
                    text.setString("69");
                    window.draw(rect);
                    window.draw(text);
                } else if (field[x][y] <= 1) {
                    rect.setTexture(wall_texture);
                    window.draw(rect);
                } else if (field[x][y] <= 2) {
                    rect.setTexture(food_texture);
                    window.draw(rect);
                } else if (field[x][y] <= 3) {
                    rect.setTexture(poison_texture);
                    window.draw(rect);
                } else {
                    continue;
                }
            }
        }
    }

};
#endif //GENETICALGORITHM_OBJECTS_SCENEDRAFT_H_
