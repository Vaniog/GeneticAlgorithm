#ifndef GENETICALGORITHM_SPACEMANAGER_H_
#define GENETICALGORITHM_SPACEMANAGER_H_

#include "GraphicsManager/Space.h"
#include "Objects/Button.h"
#define EXIT_BUTTON_PATH "../Resources/ExitButton.png"
#define MENU_BUTTON_PATH "../Resources/MenuButton.png"
#define START_BUTTON_PATH "../Resources/PlayButton.png"


class SpaceManager {
public:
    enum Mode{
        MENU, PLAY
    };
    std::vector<Mode> modes;
    Space& space;
    explicit SpaceManager(Space& space) : space(space) {
    }
    void FillByTag(const Mode mode);
};

class ExitButton : public Button {
public:
    Space* space;
    explicit ExitButton(Space& space) : Button(0.05, 0.05, 0.07, EXIT_BUTTON_PATH) {
        this->space = &space;
    }
    void OnPress() override {
        space->Stop();
    }
};
class SpaceManager;

class MenuButton : public Button {
public:
    SpaceManager *space_manager;
    explicit MenuButton(SpaceManager &space_manager) : Button(0.05, 0.05, 0.07, MENU_BUTTON_PATH) {
        this->space_manager = &space_manager;
    }
    void OnPress() override {
        space_manager->FillByTag(SpaceManager::Mode::MENU);
    }
};

class StartButton : public Button {
public:
    SpaceManager *space_manager;
    explicit StartButton(SpaceManager &space_manager) : Button(0.5, 0.5, 0.3, START_BUTTON_PATH) {
        this->space_manager = &space_manager;
    }
    void OnPress() override {
        space_manager->FillByTag(SpaceManager::Mode::PLAY);
    }
};


#endif //GENETICALGORITHM_SPACEMANAGER_H_
