#ifndef GENETICALGORITHM_GRAPHICS_SPACE_H_
#define GENETICALGORITHM_GRAPHICS_SPACE_H_
#include "Object.h"
#include "SpaceManager.h"

#include <vector>
#include <set>

class Space {
    std::map<std::string, Object*> objects; // objects and their id
    bool is_running = true;
private:
    Space(); // singleton private constructor
    Space(const Space&) {}; // singleton private copy constructor
    static Space instance; // singleton
    SpaceManager *space_manager = new SpaceManager();
public:
    static Space& GetInstance();
    Space& operator=(const Space&) = delete;

    ~Space();

    Space& operator<<(Object* object);
    void AddSpaceManager(SpaceManager* space_manager);
    static Object* GetObjectById(const std::string& id);

    bool need_to_refill_by_tag = false;
    std::string current_tag;
    void FillByTag(const std::string& tag);

    void Start();
    void Stop();
    void Clear();
    sf::RenderWindow* window;

private:
    void OnFrame();
    void OnDraw(sf::RenderWindow& window);
    void OnEvent(sf::Event& event, sf::RenderWindow& window);
};

#endif //GENETICALGORITHM_GRAPHICS_SPACE_H_