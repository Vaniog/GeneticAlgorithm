#ifndef GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
#define GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_

#include "../GraphicsManager/Object.h"
#include "../GeneticAlgorithmCore/Evolution.h"
#include <fstream>

struct SceneStats {
    uint32_t generation_number = 0;
    explicit SceneStats(uint32_t generation_number) :
            generation_number(generation_number) {};
    uint32_t life_length = 0;
};

class SceneGraphic : public Object {
    static const int32_t IMAGE_SIZE;
    static const std::string FIELD_PATH;
    static const std::string WALL_PATH;
    static const std::string BEAST_PATH;
    static const std::string FOOD_PATH;
    static const std::string POISON_PATH;
    static const std::string HEALTH_FONT_PATH;
    static const std::string STATS_FONT_PATH;
    static const int32_t FONT_BORDER;
    static const float STATS_FONT_SIZE;

    const int width = 66;
    const int height = 66;

    sf::Texture field_texture;
    sf::Texture wall_texture;
    sf::Texture beast_texture;
    sf::Texture food_texture;
    sf::Texture poison_texture;
    const static std::string OLD_GEN_FILENAME;
    const static std::string NEW_GEN_FILENAME;

    static const int MAX_STATS_SIZE;
    std::vector<SceneStats> scene_stats;
    ~SceneGraphic() = default;
public:

    std::vector<Bot> bots;
    Scene* scene;
    uint32_t bots_left = 0;

    SceneGraphic(float pos_x_percents, float pos_y_percents,
                 float size_x_percents) {
        BotsDownload();
        scene = new Scene(bots);

        pos.x = pos_x_percents * (float)window_width;
        pos.y = pos_y_percents * (float)window_height;
        size = size_x_percents * (float)window_width / (float)width;
        font_border_size = size * (float)(FONT_BORDER) / (float)(IMAGE_SIZE);

        LoadTextures();

        scene_stats.emplace_back(SceneStats(scene_stats.size()));
        FillStats();
    }

    void BotsDownload() {
        std::ifstream file(OLD_GEN_FILENAME, std::ios::in);
        for (int j = 0; j < 64; j++) {
            int arr[64];
            for (int i = 0; i < 64; i++) {
                file >> arr[i];
            }
            bots.emplace_back(Bot(arr));
        }
    }

    void BotsUpload() {
        std::ofstream out_file(NEW_GEN_FILENAME, std::ios::in);
        for (int j = 0; j < 64; j++) {
            for (int i = 0; i < 64; i++) {
                out_file << bots[j].GetDna(i) << " ";
            }
            out_file << "/n";
        }
    }

    void ReloadScene() {
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
        health_font.loadFromFile(HEALTH_FONT_PATH);
        stats_font.loadFromFile(STATS_FONT_PATH);
        beast_health.setFont(health_font);
        stats_text.setFont(stats_font);
        beast_health.setCharacterSize(size - 2 * font_border_size);
        beast_health.setFillColor(sf::Color::White);
    }

    long time_pass = 0;
    long frame_length = 100;
    bool draw_field_on = true;

    void OnFrame() override {
        time_pass += delta_time;
        if (time_pass < frame_length)
            return;
        scene->Iteration();
        if (scene->losers.size() >= 56) {
            ReloadScene();
            scene_stats.emplace_back(scene_stats.back().generation_number + 1);
            if (scene_stats.size() >= MAX_STATS_SIZE)
                scene_stats.erase(scene_stats.begin());
        }
        time_pass = 0;
        FillStats();
    }

    void FillStats() {
        scene_stats.back().life_length++;
        bots_left = 64 - scene->losers.size();
    }

    sf::Vector2<float> pos;
    float size;
    float font_border_size;
    sf::Sprite field_tile;
    sf::Font health_font;
    sf::Font stats_font;
    sf::Text beast_health;
    sf::Text stats_text;

    void PickPixel(const int& x, const int& y) {
        field_tile.setPosition(pos.x + x * size, pos.y + y * size);
        beast_health.setPosition(pos.x + x * size + font_border_size, pos.y + y * size + font_border_size);
    }

    void OnDraw(sf::RenderWindow& window) override {
        if (draw_field_on)
            DrawField(window);
        DrawStats(window);
    }

    void DrawField(sf::RenderWindow& window) {
        field_tile.setTexture(field_texture);
        field_tile.setScale(size / (float)IMAGE_SIZE, size / (float)IMAGE_SIZE);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PickPixel(x, y);
                window.draw(field_tile);
            }
        }

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PickPixel(x, y);
                Objects cur = scene->table[x][y];
                if (cur.GetType() == ObjectsType::Empty) {
                    continue;
                } else if (cur.GetType() == ObjectsType::Wall) {
                    field_tile.setTexture(wall_texture);
                    window.draw(field_tile);
                } else if (cur.GetType() == ObjectsType::Bot) {
                    field_tile.setTexture(beast_texture);
                    beast_health.setString(std::to_string(scene->bots[cur.bot].health));
                    window.draw(field_tile);
                    window.draw(beast_health);
                } else if (cur.GetType() == ObjectsType::Food) {
                    field_tile.setTexture(food_texture);
                    window.draw(field_tile);
                } else if (cur.GetType() == ObjectsType::Poison) {
                    field_tile.setTexture(poison_texture);
                    window.draw(field_tile);
                }
            }
        }
    }

    void DrawStats(sf::RenderWindow& window) {
        std::string stats_string;
        stats_string += "Arrows - change speed\n F - draw off\n";
        stats_string += "Frame length - ";
        stats_string += std::to_string(frame_length) + "ms\n";
        stats_string += "GEN-";
        stats_string += std::to_string(scene_stats.back().generation_number);
        stats_string += " | life: ";
        stats_string += std::to_string(scene_stats.back().life_length);
        stats_string += " | bots alive: ";
        stats_string += std::to_string(bots_left);
        stats_string += "\n";

        for (int32_t i = static_cast<int32_t>(scene_stats.size()) - 2; i >= 0; i--) {
            stats_string += "GEN-";
            stats_string += std::to_string(scene_stats[i].generation_number);
            stats_string += " | life: ";
            stats_string += std::to_string(scene_stats[i].life_length);
            stats_string += "\n";
        }

        stats_text.setString(stats_string);
        stats_text.setPosition(pos.x + (width + 1) * size * draw_field_on, pos.y);
        stats_text.setFont(stats_font);
        stats_text.setCharacterSize(STATS_FONT_SIZE * size);
        window.draw(stats_text);
    }

    void OnEvent(sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                draw_field_on = !draw_field_on;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                frame_length += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                frame_length -= 10;
            }
        }
    }
};
#endif //GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
