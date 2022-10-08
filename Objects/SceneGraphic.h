#ifndef GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
#define GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_

#include "../GraphicsManager/Object.h"
#include "../GeneticAlgorithmCore/Evolution.h"
#include <fstream>

class SceneGraphic : public Object {
    static const int IMAGE_SIZE;
    static const std::string FIELD_PATH;
    static const std::string WALL_PATH;
    static const std::string BEAST_PATH;
    static const std::string FOOD_PATH;
    static const std::string POISON_PATH;
    static const std::string FONT_PATH;
    static const int FONT_BORDER;

    const int width = 66;
    const int height = 66;

    sf::Texture field_texture;
    sf::Texture wall_texture;
    sf::Texture beast_texture;
    sf::Texture food_texture;
    sf::Texture poison_texture;

    ~SceneGraphic() {
    }
public:
    std::vector<Bot> bots;
    Scene* scene;
    const static std::string OLD_GEN_FILENAME;
    const static std::string NEW_GEN_FILENAME;
    SceneGraphic(float pos_x_percents, float pos_y_percents,
                 float size_x_percents) {
        BotsDownload();
        scene = new Scene(bots);

        pos.x = pos_x_percents * (float)window_width;
        pos.y = pos_y_percents * (float)window_height;
        size = size_x_percents * (float)window_width / (float)width;
        font_border_size = size * (float)(FONT_BORDER) / (float)(IMAGE_SIZE);

        LoadTextures();
    }

    void BotsDownload(){
        std::ifstream file(OLD_GEN_FILENAME, std::ios::in);
        for (int j = 0; j < 64; j++) {
            int arr[64];
            for (int i = 0; i < 64; i++) {
                file >> arr[i];
            }
            bots.push_back(Bot(arr));
        }
    }

    void BotsUpload(){
        std::ofstream out_file(NEW_GEN_FILENAME, std::ios::in);
        for (int j = 0; j < 64; j++)
        {
            for (int i = 0; i < 64; i++)
            {
                out_file << bots[j].GetDna(i) << " ";
            }
            out_file << "/n";
        }
    }

    void ReloadScene(){
        BotsUpload();
        bots = scene->GetWinners();
        bots = Mutation(bots);
        delete scene;
        scene = new Scene(bots);
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
        if (time_pass < 100)
            return;
        scene->Iteration();
        if (scene->losers.size() >= 56)
            ReloadScene();
        time_pass = 0;
    }

    sf::Vector2<float> pos;
    float size;
    float font_border_size;
    sf::Sprite rect;
    sf::Font font;
    sf::Text text;

    void PickPixel(const int& x, const int& y) {
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
                Objects cur = scene->table[x][y];
                if (cur.GetType() == ObjectsType::Empty) {
                    continue;
                } else if (cur.GetType() == ObjectsType::Wall) {
                    rect.setTexture(wall_texture);
                    window.draw(rect);
                } else if (cur.GetType() == ObjectsType::Bot) {
                    rect.setTexture(beast_texture);
                    text.setString(std::to_string(scene->bots[cur.bot].health));
                    window.draw(rect);
                    window.draw(text);
                } else if (cur.GetType() == ObjectsType::Food) {
                    rect.setTexture(food_texture);
                    window.draw(rect);
                } else if (cur.GetType() == ObjectsType::Poison) {
                    rect.setTexture(poison_texture);
                    window.draw(rect);
                }
            }
        }
    }

};
#endif //GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
