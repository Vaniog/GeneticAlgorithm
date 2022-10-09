#ifndef GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
#define GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_

#include "../../GraphicsManager/Object.h"
#include "../../GeneticAlgorithmCore/Evolution.h"
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

    const static std::string OLD_GEN_FILENAME;
    const static std::string NEW_GEN_FILENAME;

public:

    std::vector<Bot> bots;
    Scene* scene = nullptr;
    uint32_t bots_left = 0;
    static const int MAX_STATS_SIZE;
    std::vector<SceneStats> scene_stats;

    SceneGraphic(float pos_x_percents, float pos_y_percents,
                 float size_x_percents);

    sf::Texture field_texture;
    sf::Texture wall_texture;
    sf::Texture beast_texture;
    sf::Texture food_texture;
    sf::Texture poison_texture;

    void LoadTextures();

    sf::Vector2<float> pos;
    float size{}; // of tile
    float font_border_size{};

    void LoadSizes(float pos_x_percents, float pos_y_percents,
                   float size_x_percents);

    void BotsDownload();
    void BotsUpload();

    void LoadScene();
    void ReloadScene();

    static void RandomFill();

private:
    long time_pass = 0;
    long frame_length = 100;
    bool draw_field_on = true;

    void OnFrame() override;

    void FillStats();

    sf::Sprite field_tile;
    sf::Font health_font;
    sf::Font stats_font;
    sf::Text beast_health;
    sf::Text stats_text;

    void OnDraw(sf::RenderWindow& window) override;

    void PickPixel(const int& x, const int& y);

    void DrawField(sf::RenderWindow& window);

    void DrawStats(sf::RenderWindow& window);

    void OnEvent(sf::Event& event) override;
};
#endif //GENETICALGORITHM_OBJECTS_SCENEGRAPHIC_H_
