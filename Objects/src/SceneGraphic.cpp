#include "../include/SceneGraphic.h"

SceneGraphic::SceneGraphic(float pos_x_percents, float pos_y_percents, float size_x_percents) {
    LoadSizes(pos_x_percents, pos_y_percents, size_x_percents);
    LoadTextures();
    LoadScene();
}

void SceneGraphic::LoadTextures() {
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
    beast_health.setFillColor(sf::Color::White);
}

void SceneGraphic::LoadSizes(float pos_x_percents, float pos_y_percents, float size_x_percents) {
    size = size_x_percents * (float)window_width / (float)width;
    pos.x = pos_x_percents * (float)window_width - size * (float)width / 2;
    pos.y = pos_y_percents * (float)window_height - size * (float)height / 2;
    font_border_size = size * (float)(FONT_BORDER) / (float)(IMAGE_SIZE);
    beast_health.setCharacterSize(static_cast<uint32_t>((size) - 2 * font_border_size));
}

void SceneGraphic::BotsDownload() {
    std::ifstream file(OLD_GEN_FILENAME, std::fstream::in);
    bots.clear();
    for (int j = 0; j < 64; j++) {
        int arr[64];
        for (int& i : arr) {
            file >> i;
        }
        bots.emplace_back(Bot(arr));
    }
}

void SceneGraphic::BotsUpload() {
    std::ofstream out_file(NEW_GEN_FILENAME, std::fstream::out | std::ofstream::trunc);
    out_file.clear();
    for (int j = 0; j < 64; j++) {
        for (int i = 0; i < 64; i++) {
            out_file << bots[j].GetDna(i) << " ";
        }
        out_file << "\n";
    }
}

void SceneGraphic::LoadScene() {
    scene_stats.emplace_back(SceneStats(scene_stats.size()));
    BotsDownload();
    delete scene;
    scene = new Scene(bots);
    FillStats();
};

void SceneGraphic::ReloadScene() {
    bots = scene->GetWinners();
    bots = Mutation(bots);
    BotsUpload();
    delete scene;
    scene = new Scene(bots);
    scene_stats.emplace_back(scene_stats.back().generation_number + 1);
    if (scene_stats.size() >= MAX_STATS_SIZE)
        scene_stats.erase(scene_stats.begin());
    FillStats();
}

void SceneGraphic::RandomFill() {
    std::ofstream out_file(OLD_GEN_FILENAME, std::fstream::out | std::ofstream::trunc);
    out_file.clear();
    for (int j = 0; j < 64; j++) {
        for (int i = 0; i < 64; i++) {
            out_file << rand() % 71 << " ";
        }
        out_file << "\n";
    }
}

void SceneGraphic::OnFrame() {
    time_pass += delta_time;
    if (time_pass < frame_length)
        return;
    scene->Iteration();
    if (scene->losers.size() >= 56) {
        ReloadScene();
    }
    FillStats();
    time_pass = 0;
}

void SceneGraphic::FillStats() {
    scene_stats.back().life_length++;
    bots_left = 64 - scene->losers.size();
}

void SceneGraphic::OnDraw(sf::RenderWindow& window) {
    if (draw_field_on)
        DrawField(window);
    DrawStats(window);
}

void SceneGraphic::PickPixel(const int& x, const int& y) {
    auto xf = static_cast<float>(x);
    auto yf = static_cast<float>(y);
    field_tile.setPosition(pos.x + xf * size, pos.y + yf * size);
    beast_health.setPosition(pos.x + xf * size + font_border_size, pos.y + yf * size + font_border_size);
}

void SceneGraphic::DrawField(sf::RenderWindow& window) {
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

void SceneGraphic::DrawStats(sf::RenderWindow& window) {
    std::string stats_string;
    stats_string += "Arrows - change speed\n F - draw off\n Tilde - new random bots\n\n";
    stats_string += "Frame length - ";
    stats_string += std::to_string(frame_length) + "ms\n\n";
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

void SceneGraphic::OnEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            draw_field_on = !draw_field_on;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            frame_length += 10;
            frame_length = std::min(200l, frame_length);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            frame_length -= 10;
            frame_length = std::max(0l, frame_length);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
            RandomFill();
            scene_stats.clear();
            LoadScene();
        }
    }
}