#include "../include/Space.h"

Space Space::instance = Space();

Space& Space::GetInstance() {
    return instance;
}

Space::Space() {
    if (!sf::VideoMode::getFullscreenModes().empty()) {
        window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "");
    }
    Object::default_object->SetSize(sf::Vector2f(window->getSize()));
    Object::default_object->SetPos(sf::Vector2f(window->getSize()));
};

Space::~Space() {
    Clear();
}

Space& Space::operator<<(Object* object) {
    if (object->attrs->GetString("id").empty()) {
        object->attrs->SetString("id", "default_id_" + std::to_string(objects.size()));
    }
    objects.insert(std::make_pair(object->attrs->GetString("id"), object));
    return *this;
}

Object* Space::GetObjectById(const std::string& id) {
    if (id == "0") {
        return Object::default_object;
    }
    return GetInstance().objects.find(id)->second;
}

void Space::AddSpaceManager(SpaceManager* new_space_manager) {
    space_manager = new_space_manager;
}

void Space::FillByTag(const std::string& tag) {
    current_tag = tag;
    need_to_refill_by_tag = true;
}

void Space::Start() {
    while (window->isOpen() && is_running) {
        if (need_to_refill_by_tag) {
            space_manager->FillByTag(current_tag);
            need_to_refill_by_tag = false;
        }

        sf::Event event{};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
        }

        window->pollEvent(event);
        window->clear();

        OnEvent(event, *window);
        OnFrame();
        OnDraw(*window);
        window->display();
    }
}

void Space::Stop() {
    is_running = false;
}

void Space::Clear() {
    for (const auto& object : objects)
        delete object.second;
    objects.clear();
}

void Space::OnFrame() {
    for (const auto& object : objects) {
        object.second->Timer();
        object.second->OnFrame();
    }
}

void Space::OnDraw(sf::RenderWindow& window) {
    for (const auto& object : objects) {
        object.second->OnDraw(window);
    }
}

void Space::OnEvent(sf::Event& event, sf::RenderWindow& window) {
    for (const auto& object : objects) {
        object.second->OnEvent(event, window);
    }
}

