#include "SpaceManager.h"
#include "Objects/Background.h"
#include "Objects/Button.h"
#include "Objects/SceneDraft.h"

void SpaceManager::FillByTag(const SpaceManager::Mode mode){
    modes.push_back(mode);
    space.SaveParams();
    space.Clear();
    switch (mode) {
        case Mode::MENU:
            space << new Background();
            space << new ExitButton(space);
            space << new StartButton(*this);
            break;
        case Mode::PLAY:
            space << new MenuButton(*this);
            space << new SceneDraft(0.1, 0.1, 0.8);
            break;
    }
}