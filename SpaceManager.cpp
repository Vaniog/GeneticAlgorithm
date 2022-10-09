#include "SpaceManager.h"
#include "Objects/include/Background.h"
#include "Objects/include/Button.h"
#include "Objects/include/SceneGraphic.h"

void SpaceManager::FillByTag(const SpaceManager::Mode mode){
    modes.push_back(mode);
    space.SaveParams();
    space.Clear();
    switch (mode) {
        case Mode::MENU:
            space << new Background();
            space << new ExitButton(0.05, 0.05, 0.07, space);
            space << new StartButton(0.5, 0.5, 0.25, *this);
            break;
        case Mode::PLAY:
            space << new MenuButton(0.05, 0.05, 0.07, *this);
            space << new SceneGraphic(0.5, 0.5, 0.5);
            break;
    }
}